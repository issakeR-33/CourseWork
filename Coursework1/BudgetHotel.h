#ifndef BUDGETHOTEL_H
#define BUDGETHOTEL_H

#include "HotelBase.h"
#include <string>

/**
 * @class BudgetHotel
 * @brief Клас-нащадок для бюджетних готелів (1-3 зірки)
 *
 * Додає специфічні поля та методи для готелів економ-класу
 */
class BudgetHotel : public HotelBase {
private:
    int stars;
    bool hasFreeWifi;
    bool hasFreeParking;
    bool hasBreakfast;
    double discountPercent;

public:
    // Конструктори
    BudgetHotel();
    BudgetHotel(int id, const std::string& name, const std::string& city,
        const std::string& description, int stars);
    BudgetHotel(const BudgetHotel& other);
    BudgetHotel(BudgetHotel&& other) noexcept;

    // Деструктор
    ~BudgetHotel() override;

    // Оператори присвоєння
    BudgetHotel& operator=(const BudgetHotel& other);
    BudgetHotel& operator=(BudgetHotel&& other) noexcept;

    // Getters
    int getStars() const;
    bool getHasFreeWifi() const;
    bool getHasFreeParking() const;
    bool getHasBreakfast() const;
    double getDiscountPercent() const;

    // Setters
    void setStars(int stars);
    void setHasFreeWifi(bool hasFreeWifi);
    void setHasFreeParking(bool hasFreeParking);
    void setHasBreakfast(bool hasBreakfast);
    void setDiscountPercent(double discountPercent);

    // Реалізація віртуальних методів
    std::string getType() const override;
    void displayInfo() const override;
    double calculateAveragePrice() const override;

    // Власні методи (мінімум 5)

    /**
     * @brief Застосовує знижку до всіх номерів
     */
    void applyDiscountToAllRooms();

    /**
     * @brief Розраховує економію при бронюванні
     * @param nights Кількість ночей
     * @return Сума економії
     */
    double calculateSavings(int nights) const;

    /**
     * @brief Перевіряє чи надає готель безкоштовні послуги
     * @return true якщо є хоча б одна безкоштовна послуга
     */
    bool hasFreeServices() const;

    /**
     * @brief Отримує список безкоштовних послуг
     * @return Рядок з переліком послуг
     */
    std::string getFreeServicesList() const;

    /**
     * @brief Валідує дані бюджетного готелю
     * @return true якщо дані коректні, false в іншому випадку
     */
    bool validate() const;

    /**
     * @brief Отримує рейтинг готелю на основі безкоштовних послуг
     * @return Рейтинг від 0 до 100
     */
    int calculateRating() const;

    /**
     * @brief Отримує текстове представлення зірок
     * @return Рядок зі зірками
     */
    std::string getStarsRepresentation() const;
};

#endif // BUDGETHOTEL_H