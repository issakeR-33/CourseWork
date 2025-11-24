#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>

/**
 * @class Room
 * @brief Клас для представлення номера готелю
 *
 * Містить інформацію про номер, клас, місткість та ціну
 */
class Room {
private:
    int roomNumber;
    std::string roomClass;
    int capacity;
    double pricePerNight;
    bool isAvailable;

public:
    // Конструктори
    Room();
    Room(int roomNumber, const std::string& roomClass, int capacity, double pricePerNight);
    Room(const Room& other);
    Room(Room&& other) noexcept;

    // Деструктор
    ~Room();

    // Оператори присвоєння
    Room& operator=(const Room& other);
    Room& operator=(Room&& other) noexcept;

    // Getters
    int getRoomNumber() const;
    std::string getRoomClass() const;
    int getCapacity() const;
    double getPricePerNight() const;
    bool getIsAvailable() const;

    // Setters
    void setRoomNumber(int roomNumber);
    void setRoomClass(const std::string& roomClass);
    void setCapacity(int capacity);
    void setPricePerNight(double price);
    void setIsAvailable(bool available);

    // Власні методи (мінімум 5)

    /**
     * @brief Виводить інформацію про номер
     */
    void displayInfo() const;

    /**
     * @brief Валідує дані номера
     * @return true якщо дані коректні, false в іншому випадку
     */
    bool validate() const;

    /**
     * @brief Розраховує вартість проживання на кілька ночей
     * @param nights Кількість ночей
     * @return Загальна вартість
     */
    double calculateTotalPrice(int nights) const;

    /**
     * @brief Застосовує знижку до ціни
     * @param discountPercent Відсоток знижки (0-100)
     */
    void applyDiscount(double discountPercent);

    /**
     * @brief Отримує детальний опис номера
     * @return Рядок з описом
     */
    std::string getDetailedDescription() const;

    /**
     * @brief Бронює номер
     */
    void book();

    /**
     * @brief Звільняє номер
     */
    void release();

    /**
     * @brief Порівнює номери за ціною
     * @param other Інший номер
     * @return true якщо цей номер дешевший
     */
    bool isCheaperThan(const Room& other) const;
};

#endif // ROOM_H