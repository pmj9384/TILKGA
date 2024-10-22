#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "Content.h"
#include <map>
int main()
{
    std::map<std::string, Content> Contents;
	std::string contentName;
    std::string contentPhoneNumber;
	std::string contentEmail;

    for (int i = 0; i < 5; ++i)
    {
        
        std::cout << "이름, 전화번호, 이메일을 입력하세요 (최대 5명, '종료' 입력 시 중단): ";
        std::getline(std::cin, contentName);
        if (contentName == "종료")
        {
           
            break;
        }

        
        std::cout << "전화번호: ";
        std::getline(std::cin, contentPhoneNumber);
        std::cout << "이메일: ";
        std::getline(std::cin, contentEmail);

        Contents[contentName] = Content(contentName, contentPhoneNumber, contentEmail);
       
    }
    std::cout << "수정할 연락처의 이름을 입력하세요: ";
    std::getline(std::cin, contentName);

    auto find = Contents.find(contentName);

    if (find == Contents.end())
    {
        std::cout << "없다" << std::endl;
    }
    else
    {
        std::cout << "새로운 전화번호와 이메일을 입력하세요:" << std::endl;
        std::getline(std::cin, contentPhoneNumber);
        std::getline(std::cin, contentEmail);
        Contents[contentName] = Content(contentName, contentPhoneNumber, contentEmail);
    }
    std::cout << "조회할 이름을 입력하세요:" << std::endl;
    std::getline(std::cin, contentName);

    find = Contents.find(contentName);

    if (find == Contents.end())
    {
        std::cout << "존재하지 않는 이름입니다." << std::endl;
    }
    else
    {
        std::cout << "존재하는 이름입니다." << std::endl;
    }
    std::cout << "현재 전화번호부:" << std::endl;


    for (auto p = Contents.begin(); p != Contents.end(); ++p)
    {
        std::cout << p->first << " " << p->second.getPhoneNumber() << p->second.getEmail() << std::endl;
    }
    std::cout << "연락처의 총 개수:" << Contents.size()  << std::endl;
}
