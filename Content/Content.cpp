#include "Content.h"

Content::Content() :name(),phoneNumber(),email()
{
}

Content::Content(const std::string& name, const std::string& phoneNumber, const std::string& email)
    : name(name), phoneNumber(phoneNumber), email(email) {}

std::string Content::getName() const {
    return name;
}

std::string Content::getPhoneNumber() const {
    return phoneNumber;
}

std::string Content::getEmail() const {
    return email;
}

void Content::updateContent(const std::string& newPhoneNumber, const std::string& newEmail) {
    phoneNumber = newPhoneNumber;
    email = newEmail;
}
