#ifndef USERACCOUNTMANAGER_H
#define USERACCOUNTMANAGER_H

#include "User.h"
#include <vector>
#include <string>

/**
 * @class UserAccountManager
 * @brief Менеджер для управління обліковими записами користувачів
 *
 * Відповідає за авторизацію, реєстрацію, видалення та перегляд користувачів
 */
class UserAccountManager {
private:
    std::vector<User> users;
    User* currentUser;
    std::string filename;

public:
    // Конструктори
    UserAccountManager();
    UserAccountManager(const std::string& filename);
    UserAccountManager(const UserAccountManager& other);
    UserAccountManager(UserAccountManager&& other) noexcept;

    // Деструктор
    ~UserAccountManager();

    // Оператори присвоєння
    UserAccountManager& operator=(const UserAccountManager& other);
    UserAccountManager& operator=(UserAccountManager&& other) noexcept;

    // Getters
    User* getCurrentUser() const;
    std::vector<User> getUsers() const;

    // Setters
    void setFilename(const std::string& filename);

    // Власні методи (мінімум 5)

    /**
     * @brief Завантажує користувачів з файлу
     * @return true якщо успішно, false в іншому випадку
     */
    bool loadUsers();

    /**
     * @brief Зберігає користувачів у файл
     * @return true якщо успішно, false в іншому випадку
     */
    bool saveUsers();

    /**
     * @brief Авторизує користувача
     * @param username Логін
     * @param password Пароль
     * @return true якщо успішно, false в іншому випадку
     */
    bool login(const std::string& username, const std::string& password);

    /**
     * @brief Вихід з системи
     */
    void logout();

    /**
     * @brief Реєструє нового користувача
     * @param username Логін
     * @param password Пароль
     * @param accessLevel Рівень доступу
     * @return true якщо успішно, false в іншому випадку
     */
    bool registerUser(const std::string& username, const std::string& password, int accessLevel);

    /**
     * @brief Видаляє користувача за логіном
     * @param username Логін користувача
     * @return true якщо успішно, false в іншому випадку
     */
    bool deleteUser(const std::string& username);

    /**
     * @brief Виводить список усіх користувачів
     */
    void displayAllUsers() const;

    /**
     * @brief Перевіряє чи існує користувач з таким логіном
     * @param username Логін
     * @return true якщо існує, false в іншому випадку
     */
    bool userExists(const std::string& username) const;

    /**
     * @brief Перевіряє чи є поточний користувач адміністратором
     * @return true якщо адміністратор, false в іншому випадку
     */
    bool isCurrentUserAdmin() const;

    /**
     * @brief Ініціалізує адміністратора за замовчуванням
     */
    void initializeDefaultAdmin();
};

#endif // USERACCOUNTMANAGER_H