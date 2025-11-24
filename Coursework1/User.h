#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

/**
 * @class User
 * @brief Клас для представлення користувача системи
 *
 * Містить інформацію про логін, пароль та рівень доступу користувача
 */
class User {
private:
    std::string username;
    std::string password;
    int accessLevel;

public:
    // Конструктори
    User();
    User(const std::string& username, const std::string& password, int accessLevel);
    User(const User& other);
    User(User&& other) noexcept;

    // Деструктор
    ~User();

    // Оператори присвоєння
    User& operator=(const User& other);
    User& operator=(User&& other) noexcept;

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    int getAccessLevel() const;

    // Setters
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setAccessLevel(int accessLevel);

    // Власні методи (мінімум 5)

    /**
     * @brief Перевіряє чи є користувач адміністратором
     * @return true якщо адміністратор, false в іншому випадку
     */
    bool isAdmin() const;

    /**
     * @brief Перевіряє правильність пароля
     * @param inputPassword Пароль для перевірки
     * @return true якщо пароль співпадає, false в іншому випадку
     */
    bool verifyPassword(const std::string& inputPassword) const;

    /**
     * @brief Валідує username (перевіряє на коректність)
     * @return true якщо username валідний, false в іншому випадку
     */
    bool validateUsername() const;

    /**
     * @brief Валідує пароль (перевіряє довжину)
     * @return true якщо пароль валідний, false в іншому випадку
     */
    bool validatePassword() const;

    /**
     * @brief Виводить інформацію про користувача
     */
    void displayInfo() const;

    /**
     * @brief Змінює пароль користувача
     * @param oldPassword Старий пароль
     * @param newPassword Новий пароль
     * @return true якщо пароль змінено, false в іншому випадку
     */
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);

    /**
     * @brief Отримує текстову назву рівня доступу
     * @return Назва рівня доступу
     */
    std::string getAccessLevelName() const;
};

#endif // USER_H