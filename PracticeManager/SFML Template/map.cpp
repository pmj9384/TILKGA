#include <iostream>
#include <map>

int main()
{
	std::map<int, std::string> students;
		
	// ����

	std::pair<int, std::string> pair;
	pair.first = 103;
	pair.second = "����";
	students.insert(pair);

	students.insert({ 101 ,"Alice" });

	students.insert({ std::make_pair(102, "Bob") });

	students[104] = "Charlie";

	std::cout << students[105] << std::endl; 
	for (auto p : students)
	{
		std::cout << p.first << " " << p.second << std::endl;
	}

	students.erase(102);
	students.erase(101);
	/*for (auto p : students )
	{
		std::cout << p.first << " " << p.second << std::endl;
	}*/

	for (auto p = students.begin(); p != students.end(); ++p)
	{
		std::cout << p->first << " " << p->second << std::endl;
	}

	auto find = students.find(101);
	if (find == students.end())
	{
		std::cout << "����" << std::endl;
	}
	else
	{
		std::cout << "�ִ�" << std::endl;
	}

	find = students.find(103);
	if (find == students.end())
	{
		std::cout << "����" << std::endl;
	}
	else
	{
		std::cout << "�ִ�" << std::endl;
	}

	find->second = "!!!";

	for (auto p = students.rbegin(); p != students.rend(); ++p)
	{
		std::cout << p->first << " " << p->second << std::endl;
	}
	for (auto p = students.rbegin(); p != students.rend(); ++p)
	{
		std::cout << p->first << " " << p->second << std::endl;
	}
}