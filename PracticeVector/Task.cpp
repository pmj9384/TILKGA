#include "Task.h"

Task::Task():name(),priority()
{

}

Task::Task(const std::string& name, int priority) : name(name), priority(priority) {}

std::string Task::getName() const {
    return name;
}

int Task::getPriority() const {
    return priority;
}
