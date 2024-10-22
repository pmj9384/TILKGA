#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "Task.h"

int main()
{
    std::list<Task> tasks;
    std::string taskName;
    int taskPriority;

    for (int i = 0; i < 5; ++i)
    {
        std::cout << "�۾� �̸��� �Է��ϼ��� (���� �Է� �� ����): ";
        std::getline(std::cin, taskName);

        if (taskName == "����")
        {
            break;
        }

        std::cout << "�۾� �켱������ �Է��ϼ���: ";
        std::cin >> taskPriority;
     

        tasks.push_back(Task(taskName, taskPriority));
    }

    std::string FtaskName;
    int FtaskPriority;
    std::cout << "���ʿ� �߰��� �۾��� �̸��� �켱������ �Է��ϼ���: ";
    std::getline(std::cin, FtaskName);
    std::cin >> FtaskPriority;
    tasks.push_front(Task(FtaskName, FtaskPriority));

    std::string EtaskName;
    int EtaskPriority;
    std::cout << "���ʿ� �߰��� �۾��� �̸��� �켱������ �Է��ϼ���: ";
    std::cin.ignore();
    std::getline(std::cin, EtaskName);
    std::cin >> EtaskPriority;
    tasks.push_back(Task(EtaskName, EtaskPriority));

    std::string XtaskName;
    std::cout << "������ �۾��� �̸��� �Է��ϼ���: ";
    std::cin.ignore();
    std::getline(std::cin, XtaskName);

    for (auto it = tasks.begin(); it != tasks.end(); ) 
    {
        if (it->getName() == XtaskName) 
        {
            it = tasks.erase(it);
            std::cout << "'" << XtaskName << "' �۾��� �����Ͽ����ϴ�." << std::endl;
        }
        else
        {
            ++it;
        }
    }

    if (!tasks.empty()) 
    {
        tasks.erase(--tasks.end());
        std::cout << "������ �۾��� �����Ͽ����ϴ�." << std::endl;
    }

    std::cout << "\n���� �����ִ� �۾���:\n";
    for (const auto& task : tasks) 
    {
        std::cout << task.getName() << " (�켱����: " << task.getPriority() << ")" << std::endl;
    }

    std::cout << "�۾��� �� ����: " << tasks.size() << std::endl;

    return 0;
}
