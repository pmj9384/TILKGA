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
        std::cout << "작업 이름을 입력하세요 (종료 입력 시 종료): ";
        std::getline(std::cin, taskName);

        if (taskName == "종료")
        {
            break;
        }

        std::cout << "작업 우선순위를 입력하세요: ";
        std::cin >> taskPriority;
     

        tasks.push_back(Task(taskName, taskPriority));
    }

    std::string FtaskName;
    int FtaskPriority;
    std::cout << "앞쪽에 추가할 작업의 이름과 우선순위를 입력하세요: ";
    std::getline(std::cin, FtaskName);
    std::cin >> FtaskPriority;
    tasks.push_front(Task(FtaskName, FtaskPriority));

    std::string EtaskName;
    int EtaskPriority;
    std::cout << "뒤쪽에 추가할 작업의 이름과 우선순위를 입력하세요: ";
    std::cin.ignore();
    std::getline(std::cin, EtaskName);
    std::cin >> EtaskPriority;
    tasks.push_back(Task(EtaskName, EtaskPriority));

    std::string XtaskName;
    std::cout << "삭제할 작업의 이름을 입력하세요: ";
    std::cin.ignore();
    std::getline(std::cin, XtaskName);

    for (auto it = tasks.begin(); it != tasks.end(); ) 
    {
        if (it->getName() == XtaskName) 
        {
            it = tasks.erase(it);
            std::cout << "'" << XtaskName << "' 작업을 삭제하였습니다." << std::endl;
        }
        else
        {
            ++it;
        }
    }

    if (!tasks.empty()) 
    {
        tasks.erase(--tasks.end());
        std::cout << "마지막 작업을 삭제하였습니다." << std::endl;
    }

    std::cout << "\n현재 남아있는 작업들:\n";
    for (const auto& task : tasks) 
    {
        std::cout << task.getName() << " (우선순위: " << task.getPriority() << ")" << std::endl;
    }

    std::cout << "작업의 총 개수: " << tasks.size() << std::endl;

    return 0;
}
