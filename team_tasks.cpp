#include <tuple>
#include <map>
#include <iostream>

using namespace std;

// // Перечислимый тип для статуса задачи
// enum class TaskStatus
// {
//     NEW,          // новая
//     IN_PROGRESS,  // в разработке
//     TESTING,      // на тестировании
//     DONE          // завершена
// };

// // Объявляем тип-синоним для map<TaskStatus, int>,
// // позволяющего хранить количество задач каждого статуса
// using TasksInfo = map<TaskStatus, int>;

void clearNullStatuses(TasksInfo &tasks)
{
    if (!tasks[TaskStatus::NEW])
    {
        tasks.erase(TaskStatus::NEW);
    }

    if (!tasks[TaskStatus::IN_PROGRESS])
    {
        tasks.erase(TaskStatus::IN_PROGRESS);
    }

    if (!tasks[TaskStatus::TESTING])
    {
        tasks.erase(TaskStatus::TESTING);
    }

    if (!tasks[TaskStatus::DONE])
    {
        tasks.erase(TaskStatus::DONE);
    }
}


int taskInStatus(const TasksInfo &tasks, TaskStatus status)
{
    try
    {
        return tasks.at(status);
    }
    catch (...)
    {
        return 0;
    }
}

TasksInfo operator+(const TasksInfo &lhs, const TasksInfo &rhs)
{
    TasksInfo result = lhs;

    result[TaskStatus::NEW] += taskInStatus(rhs, TaskStatus::NEW);
    result[TaskStatus::IN_PROGRESS] += taskInStatus(rhs, TaskStatus::IN_PROGRESS);
    result[TaskStatus::TESTING] += taskInStatus(rhs, TaskStatus::TESTING);
    result[TaskStatus::DONE] += taskInStatus(rhs, TaskStatus::DONE);
    clearNullStatuses(result);
    return result;
}

class TeamTasks
{
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const
    {
        static const TasksInfo emptyTasks;
        try
        {
            return _teamTasks.at(person);
        }
        catch (...)
        {
            return emptyTasks;
        }
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person)
    {
        ++_teamTasks[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count)
    {
        TasksInfo oldTasks, newTasks;

        try
        {
            oldTasks = _teamTasks.at(person);
        }
        catch (...)
        {
            return make_tuple(newTasks, oldTasks); // разработчика нет
        }

        while (task_count--)
        {
            if (oldTasks[TaskStatus::NEW])
            {
                ++newTasks[TaskStatus::IN_PROGRESS];
                --oldTasks[TaskStatus::NEW];
            }
            else if (oldTasks[TaskStatus::IN_PROGRESS])
            {
                ++newTasks[TaskStatus::TESTING];
                --oldTasks[TaskStatus::IN_PROGRESS];
            }
            else if (oldTasks[TaskStatus::TESTING])
            {
                ++newTasks[TaskStatus::DONE];
                --oldTasks[TaskStatus::TESTING];
            }
            else
            {
                break;
            }
        }

        clearNullStatuses(oldTasks);
        clearNullStatuses(newTasks);
        _teamTasks[person] = oldTasks + newTasks;
        oldTasks.erase(TaskStatus::DONE);
        return make_tuple(newTasks, oldTasks);
    }
private:
    map<string, TasksInfo> _teamTasks;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info)
{
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main()
{
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i)
    {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}