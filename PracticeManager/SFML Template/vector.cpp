#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
// std::vector ���� �迭

int main()
{
	std::vector<int> vec1; //vector ���� ���ø���
	std::vector<int> vec2(5);
	std::vector<int> vec3(5, 10);
	std::vector<int> vec4 = { 1,2,3,4,5 };

	std::list<int> numbers2;
	numbers2.push_front(10);
	//numbers2.at(0) = 10;


	std::list<int> numbers;
	std::vector<std::string> words;
	
	//�߰�
	numbers.push_back(1);
	numbers.push_back(2);

	numbers.remove(1);
	//for (auto number : numbers)
	//{// ���� ��� ���� ��ȸ
	//	number *= 10;
	//	std::cout << number << std::endl;
	//}

	numbers.insert(numbers.begin(),+1, 100); //insert = 100�� index �Ǿտ� ���� �ι�° �ڸ��ְ������ �տ� +1 ����
	numbers.insert(numbers.end(),  100); //end()�� �ε��� �ǵ� 

	auto it = numbers.begin();  // ������ 3000 2000 1000������ ����� �̰�
	it = numbers.insert(it, 1000); // ù��°�γ��� 1000�� �ڿ� �Էµ� 2000�� �����ΰ��� �ڷ� �и��� ���̱� ����
	it = numbers.insert(it, 2000);
	it = numbers.insert(it, 3000);

	auto it = numbers.begin(); //�̷��� insert�ϸ� ������� �߳��� 
	it = numbers.insert(it, { 1000, 2000, 3000 });

	std::vector<int> temp = { 1000,2000,3000 };
	auto it = numbers.begin(); //�̰͵� ������� ó������ ������ ����
	it = numbers.insert(it, temp.begin(), temp.end());


	for (auto it = numbers.begin(); it  != numbers.end(); ++it)
	{ //iterator ����� ��ȸ
		*it *= 10;
		std::cout << *it << std::endl;
	}

	std::cout << std::endl;
	// ���� remove, erase
	// std::remove(numbers.begin(), numbers.end(), 10000);

	numbers.erase(numbers.begin() + 1, numbers.end() - 1);



	for (auto it = numbers.begin(); it != numbers.end(); )
	{
		if (*it == 10000)
		{
			numbers.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = numbers.begin(); it != numbers.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	for (auto it = numbers.rbegin(); it != numbers.rend(); ++it) // ������ ��ȸ
	{
		std::cout << *it << std::endl;
	}
	words.push_back("Hello");
	words.push_back("world");

	std::cout << std::endl;

	words[0] = "ABCDEF";

	std::cout << words[0] << std::endl;
	std::cout << words[1] << std::endl;

	words.clear();




}