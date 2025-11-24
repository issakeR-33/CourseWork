#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H

#include "Booking.h"
#include "IBookingService.h"
#include "HotelManager.h"
#include <vector>
#include <string>

/**
 * @class BookingManager
 * @brief Менеджер для управління бронюваннями
 *
 * Реалізує інтерфейс IBookingService та відповідає за
 * створення, пошук, сортування та фільтрацію бронювань
 */
class BookingManager : public IBookingService {
private:
    std::vector<Booking> bookings;
    std::string filename;
    int nextBookingId;
    HotelManager* hotelManager;

public:
    // Конструктори
    BookingManager();
    BookingManager(const std::string& filename, HotelManager* hotelManager);
    BookingManager(const BookingManager& other);
    BookingManager(BookingManager&& other) noexcept;

    // Деструктор
    ~BookingManager() override;

    // Оператори присвоєння
    BookingManager& operator=(const BookingManager& other);
    BookingManager& operator=(BookingManager&& other) noexcept;

    // Getters
    std::vector<Booking> getBookings() const;
    int getNextBookingId() const;

    // Setters
    void setFilename(const std::string& filename);
    void setHotelManager(HotelManager* manager);

    // Реалізація методів інтерфейсу IBookingService
    bool checkAvailability(int hotelId, int roomNumber,
        const std::string& checkIn,
        const std::string& checkOut) const override;

    bool createBooking(int hotelId, int roomNumber,
        const std::string& clientName,
        const std::string& passport,
        const std::string& checkIn,
        const std::string& checkOut) override;

    bool cancelBooking(int bookingId) override;

    std::vector<std::string> getAllBookings() const override;

    bool saveBookings() override;

    bool loadBookings() override;

    // Власні методи (мінімум 5)

    /**
     * @brief Виводить всі бронювання
     */
    void displayAllBookings() const;

    /**
     * @brief Знаходить бронювання за ID
     * @param bookingId ID бронювання
     * @return Вказівник на бронювання або nullptr
     */
    Booking* findBooking(int bookingId);

    /**
     * @brief Шукає бронювання за ім'ям клієнта
     * @param clientName Ім'я клієнта
     * @return Вектор бронювань
     */
    std::vector<Booking> findBookingsByClient(const std::string& clientName) const;

    /**
     * @brief Шукає бронювання за паспортом
     * @param passport Паспортні дані
     * @return Вектор бронювань
     */
    std::vector<Booking> findBookingsByPassport(const std::string& passport) const;

    /**
     * @brief Шукає бронювання за готелем
     * @param hotelId ID готелю
     * @return Вектор бронювань
     */
    std::vector<Booking> findBookingsByHotel(int hotelId) const;

    /**
     * @brief Шукає бронювання за статусом
     * @param status Статус бронювання
     * @return Вектор бронювань
     */
    std::vector<Booking> findBookingsByStatus(const std::string& status) const;

    /**
     * @brief Шукає активні бронювання
     * @return Вектор активних бронювань
     */
    std::vector<Booking> getActiveBookings() const;

    /**
     * @brief Сортує бронювання за датою заїзду
     * @return Відсортований вектор бронювань
     */
    std::vector<Booking> sortByCheckInDate() const;

    /**
     * @brief Сортує бронювання за ціною
     * @return Відсортований вектор бронювань
     */
    std::vector<Booking> sortByPrice() const;

    /**
     * @brief Фільтрує бронювання за датою
     * @param startDate Початкова дата
     * @param endDate Кінцева дата
     * @return Вектор бронювань
     */
    std::vector<Booking> filterByDateRange(const std::string& startDate,
        const std::string& endDate) const;

    /**
     * @brief Завершує бронювання
     * @param bookingId ID бронювання
     * @return true якщо успішно, false в іншому випадку
     */
    bool completeBooking(int bookingId);

    /**
     * @brief Отримує загальну кількість бронювань
     * @return Кількість бронювань
     */
    int getBookingCount() const;

    /**
     * @brief Розраховує загальний дохід від бронювань
     * @return Сума доходу
     */
    double calculateTotalRevenue() const;
};

#endif // BOOKINGMANAGER_H