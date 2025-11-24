#ifndef HOTELMANAGER_H
#define HOTELMANAGER_H

#include "HotelBase.h"
#include "PremiumHotel.h"
#include "BudgetHotel.h"
#include <vector>
#include <string>
#include <memory>

/**
 * @class HotelManager
 * @brief Менеджер для управління готелями
 *
 * Відповідає за зберігання, пошук та управління готелями
 */
class HotelManager {
private:
    std::vector<std::shared_ptr<HotelBase>> hotels;
    std::string filename;
    int nextHotelId;

public:
    // Конструктори
    HotelManager();
    HotelManager(const std::string& filename);
    HotelManager(const HotelManager& other);
    HotelManager(HotelManager&& other) noexcept;

    // Деструктор
    ~HotelManager();

    // Оператори присвоєння
    HotelManager& operator=(const HotelManager& other);
    HotelManager& operator=(HotelManager&& other) noexcept;

    // Getters
    std::vector<std::shared_ptr<HotelBase>> getHotels() const;
    int getNextHotelId() const;

    // Setters
    void setFilename(const std::string& filename);

    // Власні методи (мінімум 5)

    /**
     * @brief Завантажує готелі з файлу CSV
     * @return true якщо успішно, false в іншому випадку
     */
    bool loadHotels();

    /**
     * @brief Зберігає готелі у файл CSV
     * @return true якщо успішно, false в іншому випадку
     */
    bool saveHotels();

    /**
     * @brief Додає новий готель
     * @param hotel Вказівник на готель
     * @return true якщо успішно, false в іншому випадку
     */
    bool addHotel(std::shared_ptr<HotelBase> hotel);

    /**
     * @brief Видаляє готель за ID
     * @param hotelId ID готелю
     * @return true якщо успішно, false в іншому випадку
     */
    bool removeHotel(int hotelId);

    /**
     * @brief Знаходить готель за ID
     * @param hotelId ID готелю
     * @return Вказівник на готель або nullptr
     */
    std::shared_ptr<HotelBase> findHotel(int hotelId);

    /**
     * @brief Виводить всі готелі
     */
    void displayAllHotels() const;

    /**
     * @brief Шукає готелі за містом
     * @param city Назва міста
     * @return Вектор готелів
     */
    std::vector<std::shared_ptr<HotelBase>> findHotelsByCity(const std::string& city) const;

    /**
     * @brief Шукає готелі за типом
     * @param type Тип готелю (Premium/Budget)
     * @return Вектор готелів
     */
    std::vector<std::shared_ptr<HotelBase>> findHotelsByType(const std::string& type) const;

    /**
     * @brief Шукає готелі за кількістю зірок
     * @param stars Кількість зірок
     * @return Вектор готелів
     */
    std::vector<std::shared_ptr<HotelBase>> findHotelsByStars(int stars) const;

    /**
     * @brief Шукає вільні номери за критеріями
     * @param city Місто (опціонально)
     * @param roomClass Клас номера (опціонально)
     * @param minCapacity Мінімальна місткість
     * @param maxPrice Максимальна ціна
     * @return Вектор готелів з доступними номерами
     */
    std::vector<std::shared_ptr<HotelBase>> findAvailableRooms(
        const std::string& city = "",
        const std::string& roomClass = "",
        int minCapacity = 1,
        double maxPrice = 999999.0) const;

    /**
     * @brief Сортує готелі за ціною (зростання)
     * @return Відсортований вектор готелів
     */
    std::vector<std::shared_ptr<HotelBase>> sortByPrice() const;

    /**
     * @brief Сортує готелі за назвою (алфавітний порядок)
     * @return Відсортований вектор готелів
     */
    std::vector<std::shared_ptr<HotelBase>> sortByName() const;

    /**
     * @brief Отримує кількість готелів
     * @return Кількість готелів
     */
    int getHotelCount() const;
};

#endif // HOTELMANAGER_H