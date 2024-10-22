#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>


	class Content 
	{
	private:
		std::string name;
		std::string phoneNumber;
		std::string email;
	public:

		Content();
		Content(const std::string& name, const std::string& phoneNumber, const std::string& email);

		std::string getName() const;
		std::string getPhoneNumber() const;
		std::string getEmail() const;

		void updateContent(const std::string& newPhoneNumber, const std::string& newEmail);


	};






