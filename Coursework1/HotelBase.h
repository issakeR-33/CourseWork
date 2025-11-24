#ifndef HOTELBASE_H
#define HOTELBASE_H

#include "Room.h"
#include <string>
#include <vector>
#include <memory>

/**
 * @class HotelBase
 * @brief Абстрактний базовий клас для готелю
 *
 * Містить базові поля та методи для всіх типів готелів
 */
class HotelBase {
protected:
    int hotelId;
    std::string name;
    std::string city;
    std::string description;
    std::vector<Room> rooms;

public:
    // Конструктори
    HotelBase();
    HotelBase(int id, const std::string& name, const std::string& city, const std::string& description);
    HotelBase(const HotelBase& other);
    HotelBase(HotelBase&& other) noexcept;

    // Деструктор
    virtual ~HotelBase();

    // Оператори присвоєння
    HotelBase& operator=(const HotelBase& other);
    HotelBase& operator=(HotelBase&& other) noexcept;

    // Getters
    int getHotelId() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getDescription() const;
    std::vector<Room> getRooms() const;

    // Setters
    void setHotelId(int id);
    void setName(const std::string& name);
    void setCity(const std::string& city);
    void setDescription(const std::string& description);
    void setRooms(const std::vector<Room>& rooms);

    // Чисті віртуальні методи (для абстрактності)

    /**
     * @brief Отримує тип готелю
     * @return Тип готелю (Premium, Budget)
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Виводить детальну інформацію про готель
     */
    virtual void displayInfo() const = 0;

    /**
     * @brief Розраховує середню ціну номера в готелі
     * @return Середня ціна
     */
    virtual double calculateAveragePrice() const = 0;

    // Власні методи (мінімум 5)

    /**
     * @brief Додає номер до готелю
     * @param room Номер для додавання
     */
    void addRoom(const Room& room);

    /**
     * @brief Видаляє номер за номером кімнати
     * @param roomNumber Номер кімнати
     * @return true якщо успішно, false в іншому випадку
     */
    bool removeRoom(int roomNumber);

    /**
     * @brief Знаходить номер за номером кімнати
     * @param roomNumber Номер кімнати
     * @return Вказівник на номер або nullptr
     */
    Room* findRoom(int roomNumber);

    /**
     * @brief Отримує кількість номерів у готелі
     * @return Кількість номерів
     */
    int getRoomCount() const;

    /**
     * @brief Виводить список всіх номерів
     */
    void displayRooms() const;

    /**
     * @brief Перевіряє чи є вільні номери
     * @return true якщо є вільні, false в іншому випадку
     */
    bool hasAvailableRooms() const;

    /**
     * @brief Отримує всі номери певного класу
     * @param roomClass Клас номера
     * @return Вектор номерів
     */
    std::vector<Room> getRoomsByClass(const std::string& roomClass) const;
};

#endif // HOTELBASE_H