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
        
        std::cout << "�̸�, ��ȭ��ȣ, �̸����� �Է��ϼ��� (�ִ� 5��, '����' �Է� �� �ߴ�): ";
        std::getline(std::cin, contentName);
        if (contentName == "����")
        {
           
            break;
        }

        
        std::cout << "��ȭ��ȣ: ";
        std::getline(std::cin, contentPhoneNumber);
        std::cout << "�̸���: ";
        std::getline(std::cin, contentEmail);

        Contents[contentName] = Content(contentName, contentPhoneNumber, contentEmail);
       
    }
    std::cout << "������ ����ó�� �̸��� �Է��ϼ���: ";
    std::getline(std::cin, contentName);

    auto find = Contents.find(contentName);

    if (find == Contents.end())
    {
        std::cout << "����" << std::endl;
    }
    else
    {
        std::cout << "���ο� ��ȭ��ȣ�� �̸����� �Է��ϼ���:" << std::endl;
        std::getline(std::cin, contentPhoneNumber);
        std::getline(std::cin, contentEmail);
        Contents[contentName] = Content(contentName, contentPhoneNumber, contentEmail);
    }
    std::cout << "��ȸ�� �̸��� �Է��ϼ���:" << std::endl;
    std::getline(std::cin, contentName);

    find = Contents.find(contentName);

    if (find == Contents.end())
    {
        std::cout << "�������� �ʴ� �̸��Դϴ�." << std::endl;
    }
    else
    {
        std::cout << "�����ϴ� �̸��Դϴ�." << std::endl;
    }
    std::cout << "���� ��ȭ��ȣ��:" << std::endl;


    for (auto p = Contents.begin(); p != Contents.end(); ++p)
    {
        std::cout << p->first << " " << p->second.getPhoneNumber() << p->second.getEmail() << std::endl;
    }
    std::cout << "����ó�� �� ����:" << Contents.size()  << std::endl;
}
