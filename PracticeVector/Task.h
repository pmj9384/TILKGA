#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

class Task 
{
   

private:
std::string name;
int priority;

public:
	Task();
Task(const std::string& name, int priority);
std::string getName() const;
int getPriority() const;
};





