#include "Booking.h"
#include "Constants.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

// Конструктор за замовчуванням
Booking::Booking()
    : bookingId(0), hotelId(0), roomNumber(0), clientName(""), passport(""),
    checkInDate(""), checkOutDate(""), status(BOOKING_STATUS_ACTIVE), totalPrice(0.0) {
}

// Конструктор з параметрами
Booking::Booking(int bookingId, int hotelId, int roomNumber,
    const std::string& clientName, const std::string& passport,
    const std::string& checkIn, const std::string& checkOut)
    : bookingId(bookingId), hotelId(hotelId), roomNumber(roomNumber),
    clientName(clientName), passport(passport), checkInDate(checkIn),
    checkOutDate(checkOut), status(BOOKING_STATUS_ACTIVE), totalPrice(0.0) {
}

// Копіювальний конструктор
Booking::Booking(const Booking& other)
    : bookingId(other.bookingId), hotelId(other.hotelId), roomNumber(other.roomNumber),
    clientName(other.clientName), passport(other.passport), checkInDate(other.checkInDate),
    checkOutDate(other.checkOutDate), status(other.status), totalPrice(other.totalPrice) {
}

// Переміщувальний конструктор
Booking::Booking(Booking&& other) noexcept
    : bookingId(other.bookingId), hotelId(other.hotelId), roomNumber(other.roomNumber),
    clientName(std::move(other.clientName)), passport(std::move(other.passport)),
    checkInDate(std::move(other.checkInDate)), checkOutDate(std::move(other.checkOutDate)),
    status(std::move(other.status)), totalPrice(other.totalPrice) {
}

// Деструктор
Booking::~Booking() {
    // std::cout << "Об'єкт Booking #" << bookingId << " знищено." << std::endl;
}

// Оператор копіювального присвоєння
Booking& Booking::operator=(const Booking& other) {
    if (this != &other) {
        bookingId = other.bookingId;
        hotelId = other.hotelId;
        roomNumber = other.roomNumber;
        clientName = other.clientName;
        passport = other.passport;
        checkInDate = other.checkInDate;
        checkOutDate = other.checkOutDate;
        status = other.status;
        totalPrice = other.totalPrice;
    }
    return *this;
}

// Оператор переміщувального присвоєння
Booking& Booking::operator=(Booking&& other) noexcept {
    if (this != &other) {
        bookingId = other.bookingId;
        hotelId = other.hotelId;
        roomNumber = other.roomNumber;
        clientName = std::move(other.clientName);
        passport = std::move(other.passport);
        checkInDate = std::move(other.checkInDate);
        checkOutDate = std::move(other.checkOutDate);
        status = std::move(other.status);
        totalPrice = other.totalPrice;
    }
    return *this;
}

// Getters
int Booking::getBookingId() const {
    return bookingId;
}

int Booking::getHotelId() const {
    return hotelId;
}

int Booking::getRoomNumber() const {
    return roomNumber;
}

std::string Booking::getClientName() const {
    return clientName;
}

std::string Booking::getPassport() const {
    return passport;
}

std::string Booking::getCheckInDate() const {
    return checkInDate;
}

std::string Booking::getCheckOutDate() const {
    return checkOutDate;
}

std::string Booking::getStatus() const {
    return status;
}

double Booking::getTotalPrice() const {
    return totalPrice;
}

// Setters
void Booking::setBookingId(int id) {
    this->bookingId = id;
}

void Booking::setHotelId(int id) {
    this->hotelId = id;
}

void Booking::setRoomNumber(int number) {
    this->roomNumber = number;
}

void Booking::setClientName(const std::string& name) {
    this->clientName = name;
}

void Booking::setPassport(const std::string& passport) {
    this->passport = passport;
}

void Booking::setCheckInDate(const std::string& date) {
    this->checkInDate = date;
}

void Booking::setCheckOutDate(const std::string& date) {
    this->checkOutDate = date;
}

void Booking::setStatus(const std::string& status) {
    this->status = status;
}

void Booking::setTotalPrice(double price) {
    this->totalPrice = price;
}

// Власні методи

void Booking::displayInfo() const {
    std::cout << "\n=== Бронювання #" << bookingId << " ===" << std::endl;
    std::cout << "Готель ID: " << hotelId << std::endl;
    std::cout << "Номер: " << roomNumber << std::endl;
    std::cout << "Клієнт: " << clientName << std::endl;
    std::cout << "Паспорт: " << passport << std::endl;
    std::cout << "Заїзд: " << checkInDate << std::endl;
    std::cout << "Виїзд: " << checkOutDate << std::endl;
    std::cout << "Статус: " << status << std::endl;
    std::cout << "Вартість: " << std::fixed << std::setprecision(2)
        << totalPrice << " грн" << std::endl;
    std::cout << "Кількість ночей: " << calculateNights() << std::endl;
}

bool Booking::validate() const {
    if (bookingId <= 0 || hotelId <= 0 || roomNumber <= 0) {
        return false;
    }

    if (clientName.empty() || passport.empty()) {
        return false;
    }

    if (checkInDate.empty() || checkOutDate.empty()) {
        return false;
    }

    if (checkInDate >= checkOutDate) {
        return false;
    }

    if (totalPrice < 0) {
        return false;
    }

    return true;
}

int Booking::calculateNights() const {
    // Спрощена реалізація - в реальному проекті потрібна бібліотека для дат
    // Припускаємо формат DD.MM.YYYY

    int dayIn = 0, monthIn = 0, yearIn = 0;
    int dayOut = 0, monthOut = 0, yearOut = 0;

    // Використання std::stringstream для парсингу дат
    std::stringstream ssIn(checkInDate);
    std::stringstream ssOut(checkOutDate);
    char delimiter;

    ssIn >> dayIn >> delimiter >> monthIn >> delimiter >> yearIn;
    ssOut >> dayOut >> delimiter >> monthOut >> delimiter >> yearOut;

    // Приблизний розрахунок (можна покращити)
    int totalDaysIn = yearIn * 365 + monthIn * 30 + dayIn;
    int totalDaysOut = yearOut * 365 + monthOut * 30 + dayOut;

    return totalDaysOut - totalDaysIn;
}

void Booking::activate() {
    status = BOOKING_STATUS_ACTIVE;
}

void Booking::complete() {
    status = BOOKING_STATUS_COMPLETED;
}

void Booking::cancel() {
    status = BOOKING_STATUS_CANCELLED;
}

bool Booking::isActive() const {
    return status == BOOKING_STATUS_ACTIVE;
}

bool Booking::overlaps(const std::string& checkIn, const std::string& checkOut) const {
    if (!isActive()) {
        return false;
    }

    // Спрощена перевірка перекриття дат
    // В реальному проекті потрібна краща логіка порівняння дат

    return !(checkOut <= checkInDate || checkIn >= checkOutDate);
}

std::string Booking::getDetailedDescription() const {
    std::stringstream ss;
    ss << "Бронювання #" << bookingId
        << " | Готель: " << hotelId
        << " | Номер: " << roomNumber
        << " | Клієнт: " << clientName
        << " | " << checkInDate << " - " << checkOutDate
        << " | Статус: " << status;
    return ss.str();
}