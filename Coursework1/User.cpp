#include "User.h"
#include "Constants.hpp"

// Конструктор за замовчуванням
User::User() : username(""), password(""), accessLevel(ACCESS_LEVEL_USER) {
}

// Конструктор з параметрами
User::User(const std::string& username, const std::string& password, int accessLevel)
    : username(username), password(password), accessLevel(accessLevel) {
}

// Копіювальний конструктор
User::User(const User& other)
    : username(other.username), password(other.password), accessLevel(other.accessLevel) {
}

// Переміщувальний конструктор
User::User(User&& other) noexcept
    : username(std::move(other.username)),
    password(std::move(other.password)),
    accessLevel(other.accessLevel) {
}

// Деструктор
User::~User() {
    std::cout << "Об'єкт User '" << username << "' знищено." << std::endl;
}

// Оператор копіювального присвоєння
User& User::operator=(const User& other) {
    if (this != &other) {
        username = other.username;
        password = other.password;
        accessLevel = other.accessLevel;
    }
    return *this;
}

// Оператор переміщувального присвоєння
User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        username = std::move(other.username);
        password = std::move(other.password);
        accessLevel = other.accessLevel;
    }
    return *this;
}

// Getters
std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

int User::getAccessLevel() const {
    return accessLevel;
}

// Setters
void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

void User::setAccessLevel(int accessLevel) {
    this->accessLevel = accessLevel;
}

// Власні методи

bool User::isAdmin() const {
    return accessLevel == ACCESS_LEVEL_ADMIN;
}

bool User::verifyPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}

bool User::validateUsername() const {
    if (username.empty() || username.length() > MAX_USERNAME_LENGTH) {
        return false;
    }

    for (char ch : username) {
        if (!isalnum(ch) && ch != '_') {
            return false;
        }
    }

    return true;
}

bool User::validatePassword() const {
    return password.length() >= MIN_PASSWORD_LENGTH;
}

void User::displayInfo() const {
    std::cout << "=== Інформація про користувача ===" << std::endl;
    std::cout << "Логін: " << username << std::endl;
    std::cout << "Рівень доступу: " << getAccessLevelName() << std::endl;
}

bool User::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    if (!verifyPassword(oldPassword)) {
        return false;
    }

    if (newPassword.length() < MIN_PASSWORD_LENGTH) {
        return false;
    }

    password = newPassword;
    return true;
}

std::string User::getAccessLevelName() const {
    switch (accessLevel) {
    case ACCESS_LEVEL_ADMIN:
        return "Адміністратор";
    case ACCESS_LEVEL_USER:
        return "Користувач";
    default:
        return "Невідомо";
    }
}