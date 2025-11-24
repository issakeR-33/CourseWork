#ifndef IBOOKINGSERVICE_H
#define IBOOKINGSERVICE_H

#include <string>
#include <vector>

/**
 * @interface IBookingService
 * @brief Інтерфейс для сервісів бронювання
 *
 * Визначає контракт для класів, що займаються бронюванням
 */
class IBookingService {
public:
    /**
     * @brief Віртуальний деструктор
     */
    virtual ~IBookingService() = default;

    /**
     * @brief Перевіряє доступність номера на певні дати
     * @param hotelId ID готелю
     * @param roomNumber Номер кімнати
     * @param checkIn Дата заїзду
     * @param checkOut Дата виїзду
     * @return true якщо доступний, false в іншому випадку
     */
    virtual bool checkAvailability(int hotelId, int roomNumber,
        const std::string& checkIn,
        const std::string& checkOut) const = 0;

    /**
     * @brief Створює нове бронювання
     * @param hotelId ID готелю
     * @param roomNumber Номер кімнати
     * @param clientName Ім'я клієнта
     * @param passport Паспортні дані
     * @param checkIn Дата заїзду
     * @param checkOut Дата виїзду
     * @return true якщо успішно, false в іншому випадку
     */
    virtual bool createBooking(int hotelId, int roomNumber,
        const std::string& clientName,
        const std::string& passport,
        const std::string& checkIn,
        const std::string& checkOut) = 0;

    /**
     * @brief Скасовує бронювання
     * @param bookingId ID бронювання
     * @return true якщо успішно, false в іншому випадку
     */
    virtual bool cancelBooking(int bookingId) = 0;

    /**
     * @brief Отримує список всіх бронювань
     * @return Вектор рядків з інформацією про бронювання
     */
    virtual std::vector<std::string> getAllBookings() const = 0;

    /**
     * @brief Зберігає бронювання у файл
     * @return true якщо успішно, false в іншому випадку
     */
    virtual bool saveBookings() = 0;

    /**
     * @brief Завантажує бронювання з файлу
     * @return true якщо успішно, false в іншому випадку
     */
    virtual bool loadBookings() = 0;
};

#endif // IBOOKINGSERVICE_H