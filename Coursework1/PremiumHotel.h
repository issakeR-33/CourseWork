#ifndef PREMIUMHOTEL_H
#define PREMIUMHOTEL_H

#include "HotelBase.h"
#include <string>
#include <vector>

/**
 * @class PremiumHotel
 * @brief Клас-нащадок для преміум готелів (4-5 зірок)
 *
 * Додає специфічні поля та методи для готелів високого класу
 */
class PremiumHotel : public HotelBase {
private:
    int stars;
    std::vector<std::string> services;
    bool hasPool;
    bool hasSpa;
    bool hasRestaurant;

public:
    // Конструктори
    PremiumHotel();
    PremiumHotel(int id, const std::string& name, const std::string& city,
        const std::string& description, int stars);
    PremiumHotel(const PremiumHotel& other);
    PremiumHotel(PremiumHotel&& other) noexcept;

    // Деструктор
    ~PremiumHotel() override;

    // Оператори присвоєння
    PremiumHotel& operator=(const PremiumHotel& other);
    PremiumHotel& operator=(PremiumHotel&& other) noexcept;

    // Getters
    int getStars() const;
    std::vector<std::string> getServices() const;
    bool getHasPool() const;
    bool getHasSpa() const;
    bool getHasRestaurant() const;

    // Setters
    void setStars(int stars);
    void setServices(const std::vector<std::string>& services);
    void setHasPool(bool hasPool);
    void setHasSpa(bool hasSpa);
    void setHasRestaurant(bool hasRestaurant);

    // Реалізація віртуальних методів
    std::string getType() const override;
    void displayInfo() const override;
    double calculateAveragePrice() const override;

    // Власні методи (мінімум 5)

    /**
     * @brief Додає сервіс до готелю
     * @param service Назва сервісу
     */
    void addService(const std::string& service);

    /**
     * @brief Видаляє сервіс з готелю
     * @param service Назва сервісу
     * @return true якщо успішно, false в іншому випадку
     */
    bool removeService(const std::string& service);

    /**
     * @brief Виводить всі доступні сервіси
     */
    void displayServices() const;

    /**
     * @brief Перевіряє чи є певний сервіс
     * @param service Назва сервісу
     * @return true якщо є, false в іншому випадку
     */
    bool hasService(const std::string& service) const;

    /**
     * @brief Отримує кількість зірок готелю
     * @return Текстове представлення зірок
     */
    std::string getStarsRepresentation() const;

    /**
     * @brief Валідує дані преміум готелю
     * @return true якщо дані коректні, false в іншому випадку
     */
    bool validate() const;

    /**
     * @brief Отримує рейтинг готелю на основі сервісів
     * @return Рейтинг від 0 до 100
     */
    int calculateRating() const;
};

#endif // PREMIUMHOTEL_H