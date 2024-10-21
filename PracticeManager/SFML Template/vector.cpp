#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
// std::vector 동적 배열

int main()
{
	std::vector<int> vec1; //vector 생성 템플릿씀
	std::vector<int> vec2(5);
	std::vector<int> vec3(5, 10);
	std::vector<int> vec4 = { 1,2,3,4,5 };

	std::list<int> numbers2;
	numbers2.push_front(10);
	//numbers2.at(0) = 10;


	std::list<int> numbers;
	std::vector<std::string> words;
	
	//추가
	numbers.push_back(1);
	numbers.push_back(2);

	numbers.remove(1);
	//for (auto number : numbers)
	//{// 범위 기반 루프 순회
	//	number *= 10;
	//	std::cout << number << std::endl;
	//}

	numbers.insert(numbers.begin(),+1, 100); //insert = 100을 index 맨앞에 넣음 두번째 자리넣고싶으면 앞에 +1 넣음
	numbers.insert(numbers.end(),  100); //end()는 인덱스 맨뒤 

	auto it = numbers.begin();  // 순서가 3000 2000 1000순으로 출력함 이게
	it = numbers.insert(it, 1000); // 첫번째로넣은 1000이 뒤에 입력된 2000이 앞으로가고 뒤로 밀리는 순이기 때문
	it = numbers.insert(it, 2000);
	it = numbers.insert(it, 3000);

	auto it = numbers.begin(); //이렇게 insert하면 순서대로 잘나옴 
	it = numbers.insert(it, { 1000, 2000, 3000 });

	std::vector<int> temp = { 1000,2000,3000 };
	auto it = numbers.begin(); //이것도 순서대로 처음부터 끝까지 나옴
	it = numbers.insert(it, temp.begin(), temp.end());


	for (auto it = numbers.begin(); it  != numbers.end(); ++it)
	{ //iterator 사용한 순회
		*it *= 10;
		std::cout << *it << std::endl;
	}

	std::cout << std::endl;
	// 삭제 remove, erase
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

	for (auto it = numbers.rbegin(); it != numbers.rend(); ++it) // 역방향 순회
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