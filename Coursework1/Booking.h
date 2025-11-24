#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <iostream>

/**
 * @class Booking
 * @brief Клас для представлення бронювання номера
 *
 * Містить інформацію про клієнта, дати та зв'язок з готелем/номером
 */
class Booking {
private:
    int bookingId;
    int hotelId;
    int roomNumber;
    std::string clientName;
    std::string passport;
    std::string checkInDate;
    std::string checkOutDate;
    std::string status;
    double totalPrice;

public:
    // Конструктори
    Booking();
    Booking(int bookingId, int hotelId, int roomNumber,
        const std::string& clientName, const std::string& passport,
        const std::string& checkIn, const std::string& checkOut);
    Booking(const Booking& other);
    Booking(Booking&& other) noexcept;

    // Деструктор
    ~Booking();

    // Оператори присвоєння
    Booking& operator=(const Booking& other);
    Booking& operator=(Booking&& other) noexcept;

    // Getters
    int getBookingId() const;
    int getHotelId() const;
    int getRoomNumber() const;
    std::string getClientName() const;
    std::string getPassport() const;
    std::string getCheckInDate() const;
    std::string getCheckOutDate() const;
    std::string getStatus() const;
    double getTotalPrice() const;

    // Setters
    void setBookingId(int id);
    void setHotelId(int id);
    void setRoomNumber(int number);
    void setClientName(const std::string& name);
    void setPassport(const std::string& passport);
    void setCheckInDate(const std::string& date);
    void setCheckOutDate(const std::string& date);
    void setStatus(const std::string& status);
    void setTotalPrice(double price);

    // Власні методи (мінімум 5)

    /**
     * @brief Виводить інформацію про бронювання
     */
    void displayInfo() const;

    /**
     * @brief Валідує дані бронювання
     * @return true якщо дані коректні, false в іншому випадку
     */
    bool validate() const;

    /**
     * @brief Розраховує кількість днів проживання
     * @return Кількість днів
     */
    int calculateNights() const;

    /**
     * @brief Активує бронювання
     */
    void activate();

    /**
     * @brief Завершує бронювання
     */
    void complete();

    /**
     * @brief Скасовує бронювання
     */
    void cancel();

    /**
     * @brief Перевіряє чи активне бронювання
     * @return true якщо активне, false в іншому випадку
     */
    bool isActive() const;

    /**
     * @brief Перевіряє чи перекривається бронювання з іншим періодом
     * @param checkIn Дата заїзду
     * @param checkOut Дата виїзду
     * @return true якщо перекривається, false в іншому випадку
     */
    bool overlaps(const std::string& checkIn, const std::string& checkOut) const;

    /**
     * @brief Отримує детальний опис бронювання
     * @return Рядок з описом
     */
    std::string getDetailedDescription() const;
};

#endif // BOOKING_H