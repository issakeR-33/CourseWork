#include "BudgetHotel.h"
#include "Constants.hpp"
#include <iostream>
#include <iomanip>

// Конструктор за замовчуванням
BudgetHotel::BudgetHotel()
    : HotelBase(), stars(2), hasFreeWifi(false), hasFreeParking(false),
    hasBreakfast(false), discountPercent(0.0) {
}

// Конструктор з параметрами
BudgetHotel::BudgetHotel(int id, const std::string& name, const std::string& city,
    const std::string& description, int stars)
    : HotelBase(id, name, city, description), stars(stars),
    hasFreeWifi(false), hasFreeParking(false), hasBreakfast(false), discountPercent(0.0) {
}

// Копіювальний конструктор
BudgetHotel::BudgetHotel(const BudgetHotel& other)
    : HotelBase(other), stars(other.stars), hasFreeWifi(other.hasFreeWifi),
    hasFreeParking(other.hasFreeParking), hasBreakfast(other.hasBreakfast),
    discountPercent(other.discountPercent) {
}

// Переміщувальний конструктор
BudgetHotel::BudgetHotel(BudgetHotel&& other) noexcept
    : HotelBase(std::move(other)), stars(other.stars), hasFreeWifi(other.hasFreeWifi),
    hasFreeParking(other.hasFreeParking), hasBreakfast(other.hasBreakfast),
    discountPercent(other.discountPercent) {
}

// Деструктор
BudgetHotel::~BudgetHotel() {
    std::cout << "Об'єкт BudgetHotel '" << getName() << "' знищено." << std::endl;
}

// Оператор копіювального присвоєння
BudgetHotel& BudgetHotel::operator=(const BudgetHotel& other) {
    if (this != &other) {
        HotelBase::operator=(other);
        stars = other.stars;
        hasFreeWifi = other.hasFreeWifi;
        hasFreeParking = other.hasFreeParking;
        hasBreakfast = other.hasBreakfast;
        discountPercent = other.discountPercent;
    }
    return *this;
}

// Оператор переміщувального присвоєння
BudgetHotel& BudgetHotel::operator=(BudgetHotel&& other) noexcept {
    if (this != &other) {
        HotelBase::operator=(std::move(other));
        stars = other.stars;
        hasFreeWifi = other.hasFreeWifi;
        hasFreeParking = other.hasFreeParking;
        hasBreakfast = other.hasBreakfast;
        discountPercent = other.discountPercent;
    }
    return *this;
}

// Getters
int BudgetHotel::getStars() const {
    return stars;
}

bool BudgetHotel::getHasFreeWifi() const {
    return hasFreeWifi;
}

bool BudgetHotel::getHasFreeParking() const {
    return hasFreeParking;
}

bool BudgetHotel::getHasBreakfast() const {
    return hasBreakfast;
}

double BudgetHotel::getDiscountPercent() const {
    return discountPercent;
}

// Setters
void BudgetHotel::setStars(int stars) {
    this->stars = stars;
}

void BudgetHotel::setHasFreeWifi(bool hasFreeWifi) {
    this->hasFreeWifi = hasFreeWifi;
}

void BudgetHotel::setHasFreeParking(bool hasFreeParking) {
    this->hasFreeParking = hasFreeParking;
}

void BudgetHotel::setHasBreakfast(bool hasBreakfast) {
    this->hasBreakfast = hasBreakfast;
}

void BudgetHotel::setDiscountPercent(double discountPercent) {
    this->discountPercent = discountPercent;
}

// Реалізація віртуальних методів

std::string BudgetHotel::getType() const {
    return HOTEL_TYPE_BUDGET;
}

void BudgetHotel::displayInfo() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "BUDGET HOTEL" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "ID: " << getHotelId() << std::endl;
    std::cout << "Назва: " << getName() << std::endl;
    std::cout << "Місто: " << getCity() << std::endl;
    std::cout << "Опис: " << getDescription() << std::endl;
    std::cout << "Зірок: " << getStarsRepresentation() << std::endl;
    std::cout << "Кількість номерів: " << getRoomCount() << std::endl;
    std::cout << "Середня ціна: " << std::fixed << std::setprecision(2)
        << calculateAveragePrice() << " грн/ніч" << std::endl;

    if (discountPercent > 0) {
        std::cout << "Знижка: " << discountPercent << "%" << std::endl;
    }

    std::cout << "Безкоштовний WiFi: " << (hasFreeWifi ? "Так" : "Ні") << std::endl;
    std::cout << "Безкоштовна парковка: " << (hasFreeParking ? "Так" : "Ні") << std::endl;
    std::cout << "Сніданок: " << (hasBreakfast ? "Так" : "Ні") << std::endl;
    std::cout << "========================================" << std::endl;
}

double BudgetHotel::calculateAveragePrice() const {
    if (rooms.empty()) {
        return 0.0;
    }

    double totalPrice = 0.0;
    for (const auto& room : rooms) {
        totalPrice += room.getPricePerNight();
    }

    double avgPrice = totalPrice / rooms.size();

    if (discountPercent > 0) {
        avgPrice = avgPrice * (1.0 - discountPercent / 100.0);
    }

    return avgPrice;
}

// Власні методи

void BudgetHotel::applyDiscountToAllRooms() {
    if (discountPercent <= 0) {
        std::cout << "Знижка не встановлена!" << std::endl;
        return;
    }

    for (auto& room : rooms) {
        room.applyDiscount(discountPercent);
    }

    std::cout << "Знижку " << discountPercent << "% застосовано до всіх номерів." << std::endl;
}

double BudgetHotel::calculateSavings(int nights) const {
    if (discountPercent <= 0 || nights <= 0) {
        return 0.0;
    }

    double totalOriginalPrice = 0.0;
    for (const auto& room : rooms) {
        totalOriginalPrice += room.getPricePerNight();
    }

    double avgOriginalPrice = rooms.empty() ? 0.0 : totalOriginalPrice / rooms.size();
    double savings = avgOriginalPrice * (discountPercent / 100.0) * nights;

    return savings;
}

bool BudgetHotel::hasFreeServices() const {
    return hasFreeWifi || hasFreeParking || hasBreakfast;
}

std::string BudgetHotel::getFreeServicesList() const {
    std::string services;

    if (hasFreeWifi) services += "WiFi, ";
    if (hasFreeParking) services += "Парковка, ";
    if (hasBreakfast) services += "Сніданок, ";

    if (!services.empty()) {
        services = services.substr(0, services.length() - 2);
    }
    else {
        services = "Немає безкоштовних послуг";
    }

    return services;
}

bool BudgetHotel::validate() const {
    if (stars < MIN_STARS || stars > 3) {
        return false;
    }

    if (getName().empty() || getCity().empty()) {
        return false;
    }

    if (discountPercent < 0 || discountPercent > 100) {
        return false;
    }

    return true;
}

int BudgetHotel::calculateRating() const {
    int rating = stars * 20;

    if (hasFreeWifi) rating += 10;
    if (hasFreeParking) rating += 10;
    if (hasBreakfast) rating += 10;

    if (discountPercent >= 10) rating += 5;
    if (discountPercent >= 20) rating += 5;

    return std::min(rating, 100);
}

std::string BudgetHotel::getStarsRepresentation() const {
    std::string result;
    for (int i = 0; i < stars; ++i) {
        result += "★";
    }
    return result + " (" + std::to_string(stars) + ")";
}