#include "BookingManager.h"
#include "Constants.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

// Конструктор за замовчуванням
BookingManager::BookingManager()
    : filename(BOOKINGS_FILE), nextBookingId(1), hotelManager(nullptr) {
}

// Конструктор з параметрами
BookingManager::BookingManager(const std::string& filename, HotelManager* hotelManager)
    : filename(filename), nextBookingId(1), hotelManager(hotelManager) {
}

// Копіювальний конструктор
BookingManager::BookingManager(const BookingManager& other)
    : bookings(other.bookings), filename(other.filename),
    nextBookingId(other.nextBookingId), hotelManager(other.hotelManager) {
}

// Переміщувальний конструктор
BookingManager::BookingManager(BookingManager&& other) noexcept
    : bookings(std::move(other.bookings)), filename(std::move(other.filename)),
    nextBookingId(other.nextBookingId), hotelManager(other.hotelManager) {
    other.hotelManager = nullptr;
}

// Деструктор
BookingManager::~BookingManager() {
    std::cout << "Об'єкт BookingManager знищено." << std::endl;
}

// Оператор копіювального присвоєння
BookingManager& BookingManager::operator=(const BookingManager& other) {
    if (this != &other) {
        bookings = other.bookings;
        filename = other.filename;
        nextBookingId = other.nextBookingId;
        hotelManager = other.hotelManager;
    }
    return *this;
}

// Оператор переміщувального присвоєння
BookingManager& BookingManager::operator=(BookingManager&& other) noexcept {
    if (this != &other) {
        bookings = std::move(other.bookings);
        filename = std::move(other.filename);
        nextBookingId = other.nextBookingId;
        hotelManager = other.hotelManager;
        other.hotelManager = nullptr;
    }
    return *this;
}

// Getters
std::vector<Booking> BookingManager::getBookings() const {
    return bookings;
}

int BookingManager::getNextBookingId() const {
    return nextBookingId;
}

// Setters
void BookingManager::setFilename(const std::string& filename) {
    this->filename = filename;
}

void BookingManager::setHotelManager(HotelManager* manager) {
    this->hotelManager = manager;
}

// Реалізація методів інтерфейсу

bool BookingManager::checkAvailability(int hotelId, int roomNumber,
    const std::string& checkIn,
    const std::string& checkOut) const {
    // Перевіряємо чи існує готель
    if (!hotelManager) {
        std::cerr << "HotelManager не встановлено!" << std::endl;
        return false;
    }

    auto hotel = hotelManager->findHotel(hotelId);
    if (!hotel) {
        std::cerr << "Готель не знайдено!" << std::endl;
        return false;
    }

    // Перевіряємо чи існує номер
    Room* room = hotel->findRoom(roomNumber);
    if (!room) {
        std::cerr << "Номер не знайдено!" << std::endl;
        return false;
    }

    // Перевіряємо перекриття з існуючими бронюваннями
    for (const auto& booking : bookings) {
        if (booking.getHotelId() == hotelId &&
            booking.getRoomNumber() == roomNumber &&
            booking.isActive() &&
            booking.overlaps(checkIn, checkOut)) {
            return false;
        }
    }

    return true;
}

bool BookingManager::createBooking(int hotelId, int roomNumber,
    const std::string& clientName,
    const std::string& passport,
    const std::string& checkIn,
    const std::string& checkOut) {
    // Перевіряємо доступність
    if (!checkAvailability(hotelId, roomNumber, checkIn, checkOut)) {
        std::cerr << "Номер недоступний на вказані дати!" << std::endl;
        return false;
    }

    // Отримуємо готель та номер для розрахунку ціни
    auto hotel = hotelManager->findHotel(hotelId);
    if (!hotel) {
        return false;
    }

    Room* room = hotel->findRoom(roomNumber);
    if (!room) {
        return false;
    }

    // Створюємо бронювання
    Booking newBooking(nextBookingId++, hotelId, roomNumber,
        clientName, passport, checkIn, checkOut);

    // Розраховуємо вартість
    int nights = newBooking.calculateNights();
    double totalPrice = room->getPricePerNight() * nights;
    newBooking.setTotalPrice(totalPrice);

    // Валідуємо
    if (!newBooking.validate()) {
        std::cerr << "Некоректні дані бронювання!" << std::endl;
        return false;
    }

    bookings.push_back(newBooking);
    return saveBookings();
}

bool BookingManager::cancelBooking(int bookingId) {
    Booking* booking = findBooking(bookingId);

    if (!booking) {
        std::cerr << "Бронювання не знайдено!" << std::endl;
        return false;
    }

    booking->cancel();
    return saveBookings();
}

std::vector<std::string> BookingManager::getAllBookings() const {
    std::vector<std::string> result;

    for (const auto& booking : bookings) {
        result.push_back(booking.getDetailedDescription());
    }

    return result;
}

bool BookingManager::saveBookings() {
    try {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
            return false;
        }

        // Записуємо заголовок
        file << "id,hotel_id,room_number,client_name,passport,check_in,check_out,status,total_price" << std::endl;

        // Записуємо дані
        for (const auto& booking : bookings) {
            file << booking.getBookingId() << ","
                << booking.getHotelId() << ","
                << booking.getRoomNumber() << ","
                << booking.getClientName() << ","
                << booking.getPassport() << ","
                << booking.getCheckInDate() << ","
                << booking.getCheckOutDate() << ","
                << booking.getStatus() << ","
                << booking.getTotalPrice() << std::endl;
        }

        file.close();
        return true;

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка збереження бронювань: " << e.what() << std::endl;
        return false;
    }
}

bool BookingManager::loadBookings() {
    try {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
            return false;
        }

        bookings.clear();
        std::string line;

        // Пропускаємо заголовок
        std::getline(file, line);

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() < 9) continue;

            int id = std::stoi(tokens[0]);
            int hotelId = std::stoi(tokens[1]);
            int roomNumber = std::stoi(tokens[2]);
            std::string clientName = tokens[3];
            std::string passport = tokens[4];
            std::string checkIn = tokens[5];
            std::string checkOut = tokens[6];
            std::string status = tokens[7];
            double totalPrice = std::stod(tokens[8]);

            Booking booking(id, hotelId, roomNumber, clientName, passport, checkIn, checkOut);
            booking.setStatus(status);
            booking.setTotalPrice(totalPrice);

            bookings.push_back(booking);

            if (id >= nextBookingId) {
                nextBookingId = id + 1;
            }
        }

        file.close();
        return true;

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка завантаження бронювань: " << e.what() << std::endl;
        return false;
    }
}

// Власні методи

void BookingManager::displayAllBookings() const {
    if (bookings.empty()) {
        std::cout << "\nНемає бронювань у базі даних." << std::endl;
        return;
    }

    std::cout << "\n========== СПИСОК БРОНЮВАНЬ ==========" << std::endl;
    for (const auto& booking : bookings) {
        booking.displayInfo();
        std::cout << "----------------------------------------" << std::endl;
    }
    std::cout << "\nВсього бронювань: " << bookings.size() << std::endl;
}

Booking* BookingManager::findBooking(int bookingId) {
    for (auto& booking : bookings) {
        if (booking.getBookingId() == bookingId) {
            return &booking;
        }
    }
    return nullptr;
}

std::vector<Booking> BookingManager::findBookingsByClient(const std::string& clientName) const {
    std::vector<Booking> result;

    std::copy_if(bookings.begin(), bookings.end(), std::back_inserter(result),
        [&clientName](const Booking& booking) {
            return booking.getClientName() == clientName;
        });

    return result;
}

std::vector<Booking> BookingManager::findBookingsByPassport(const std::string& passport) const {
    std::vector<Booking> result;

    std::copy_if(bookings.begin(), bookings.end(), std::back_inserter(result),
        [&passport](const Booking& booking) {
            return booking.getPassport() == passport;
        });

    return result;
}

std::vector<Booking> BookingManager::findBookingsByHotel(int hotelId) const {
    std::vector<Booking> result;

    std::copy_if(bookings.begin(), bookings.end(), std::back_inserter(result),
        [hotelId](const Booking& booking) {
            return booking.getHotelId() == hotelId;
        });

    return result;
}

std::vector<Booking> BookingManager::findBookingsByStatus(const std::string& status) const {
    std::vector<Booking> result;

    std::copy_if(bookings.begin(), bookings.end(), std::back_inserter(result),
        [&status](const Booking& booking) {
            return booking.getStatus() == status;
        });

    return result;
}

std::vector<Booking> BookingManager::getActiveBookings() const {
    return findBookingsByStatus(BOOKING_STATUS_ACTIVE);
}

std::vector<Booking> BookingManager::sortByCheckInDate() const {
    std::vector<Booking> sorted = bookings;

    std::sort(sorted.begin(), sorted.end(),
        [](const Booking& a, const Booking& b) {
            return a.getCheckInDate() < b.getCheckInDate();
        });

    return sorted;
}

std::vector<Booking> BookingManager::sortByPrice() const {
    std::vector<Booking> sorted = bookings;

    std::sort(sorted.begin(), sorted.end(),
        [](const Booking& a, const Booking& b) {
            return a.getTotalPrice() < b.getTotalPrice();
        });

    return sorted;
}

std::vector<Booking> BookingManager::filterByDateRange(const std::string& startDate,
    const std::string& endDate) const {
    std::vector<Booking> result;

    std::copy_if(bookings.begin(), bookings.end(), std::back_inserter(result),
        [&startDate, &endDate](const Booking& booking) {
            return booking.getCheckInDate() >= startDate &&
                booking.getCheckInDate() <= endDate;
        });

    return result;
}

bool BookingManager::completeBooking(int bookingId) {
    Booking* booking = findBooking(bookingId);

    if (!booking) {
        std::cerr << "Бронювання не знайдено!" << std::endl;
        return false;
    }

    booking->complete();
    return saveBookings();
}

int BookingManager::getBookingCount() const {
    return bookings.size();
}

double BookingManager::calculateTotalRevenue() const {
    double total = 0.0;

    for (const auto& booking : bookings) {
        if (booking.getStatus() == BOOKING_STATUS_COMPLETED) {
            total += booking.getTotalPrice();
        }
    }

    return total;
}