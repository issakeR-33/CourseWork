#include "UserAccountManager.h"
#include "Constants.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

// Конструктор за замовчуванням
UserAccountManager::UserAccountManager()
    : currentUser(nullptr), filename(USERS_FILE) {
}

// Конструктор з параметром
UserAccountManager::UserAccountManager(const std::string& filename)
    : currentUser(nullptr), filename(filename) {
}

// Копіювальний конструктор
UserAccountManager::UserAccountManager(const UserAccountManager& other)
    : users(other.users), currentUser(nullptr), filename(other.filename) {
}

// Переміщувальний конструктор
UserAccountManager::UserAccountManager(UserAccountManager&& other) noexcept
    : users(std::move(other.users)), currentUser(other.currentUser), filename(std::move(other.filename)) {
    other.currentUser = nullptr;
}

// Деструктор
UserAccountManager::~UserAccountManager() {
    logout();
    std::cout << "Об'єкт UserAccountManager знищено." << std::endl;
}

// Оператор копіювального присвоєння
UserAccountManager& UserAccountManager::operator=(const UserAccountManager& other) {
    if (this != &other) {
        users = other.users;
        filename = other.filename;
        currentUser = nullptr;
    }
    return *this;
}

// Оператор переміщувального присвоєння
UserAccountManager& UserAccountManager::operator=(UserAccountManager&& other) noexcept {
    if (this != &other) {
        users = std::move(other.users);
        filename = std::move(other.filename);
        currentUser = other.currentUser;
        other.currentUser = nullptr;
    }
    return *this;
}

// Getters
User* UserAccountManager::getCurrentUser() const {
    return currentUser;
}

std::vector<User> UserAccountManager::getUsers() const {
    return users;
}

// Setters
void UserAccountManager::setFilename(const std::string& filename) {
    this->filename = filename;
}

// Власні методи

bool UserAccountManager::loadUsers() {
    try {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
            initializeDefaultAdmin();
            return false;
        }

        users.clear();
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string username, password;
            int accessLevel;

            if (std::getline(ss, username, ':') && std::getline(ss, password, ':') && ss >> accessLevel) {
                users.emplace_back(username, password, accessLevel);
            }
        }

        file.close();

        if (users.empty()) {
            initializeDefaultAdmin();
        }

        return true;

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка завантаження користувачів: " << e.what() << std::endl;
        initializeDefaultAdmin();
        return false;
    }
}

bool UserAccountManager::saveUsers() {
    try {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
            return false;
        }

        for (const auto& user : users) {
            file << user.getUsername() << ":"
                << user.getPassword() << ":"
                << user.getAccessLevel() << std::endl;
        }

        file.close();
        return true;

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка збереження користувачів: " << e.what() << std::endl;
        return false;
    }
}

bool UserAccountManager::login(const std::string& username, const std::string& password) {
    for (auto& user : users) {
        if (user.getUsername() == username && user.verifyPassword(password)) {
            currentUser = &user;
            return true;
        }
    }
    return false;
}

void UserAccountManager::logout() {
    currentUser = nullptr;
}

bool UserAccountManager::registerUser(const std::string& username, const std::string& password, int accessLevel) {
    if (userExists(username)) {
        std::cerr << "Користувач з таким логіном вже існує!" << std::endl;
        return false;
    }

    User newUser(username, password, accessLevel);

    if (!newUser.validateUsername() || !newUser.validatePassword()) {
        std::cerr << "Некоректні дані користувача!" << std::endl;
        return false;
    }

    users.push_back(newUser);
    return saveUsers();
}

bool UserAccountManager::deleteUser(const std::string& username) {
    if (username == "admin") {
        std::cerr << "Не можна видалити адміністратора!" << std::endl;
        return false;
    }

    auto it = std::remove_if(users.begin(), users.end(),
        [&username](const User& user) { return user.getUsername() == username; });

    if (it != users.end()) {
        users.erase(it, users.end());
        return saveUsers();
    }

    return false;
}

void UserAccountManager::displayAllUsers() const {
    std::cout << "\n=== Список користувачів ===" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    for (const auto& user : users) {
        std::cout << "Логін: " << user.getUsername()
            << " | Рівень доступу: " << user.getAccessLevelName() << std::endl;
    }

    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Всього користувачів: " << users.size() << std::endl;
}

bool UserAccountManager::userExists(const std::string& username) const {
    return std::any_of(users.begin(), users.end(),
        [&username](const User& user) { return user.getUsername() == username; });
}

bool UserAccountManager::isCurrentUserAdmin() const {
    return currentUser != nullptr && currentUser->isAdmin();
}

void UserAccountManager::initializeDefaultAdmin() {
    if (!userExists("admin")) {
        users.emplace_back("admin", "admin123", ACCESS_LEVEL_ADMIN);
        saveUsers();
        std::cout << "Створено адміністратора за замовчуванням (admin:admin123)" << std::endl;
    }
}