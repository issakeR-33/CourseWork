#include "PremiumHotel.h"
#include "Constants.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

// Конструктор за замовчуванням
PremiumHotel::PremiumHotel()
    : HotelBase(), stars(4), hasPool(false), hasSpa(false), hasRestaurant(false) {
}

// Конструктор з параметрами
PremiumHotel::PremiumHotel(int id, const std::string& name, const std::string& city,
    const std::string& description, int stars)
    : HotelBase(id, name, city, description), stars(stars),
    hasPool(false), hasSpa(false), hasRestaurant(false) {
}

// Копіювальний конструктор
PremiumHotel::PremiumHotel(const PremiumHotel& other)
    : HotelBase(other), stars(other.stars), services(other.services),
    hasPool(other.hasPool), hasSpa(other.hasSpa), hasRestaurant(other.hasRestaurant) {
}

// Переміщувальний конструктор
PremiumHotel::PremiumHotel(PremiumHotel&& other) noexcept
    : HotelBase(std::move(other)), stars(other.stars), services(std::move(other.services)),
    hasPool(other.hasPool), hasSpa(other.hasSpa), hasRestaurant(other.hasRestaurant) {
}

// Деструктор
PremiumHotel::~PremiumHotel() {
    std::cout << "Об'єкт PremiumHotel '" << getName() << "' знищено." << std::endl;
}

// Оператор копіювального присвоєння
PremiumHotel& PremiumHotel::operator=(const PremiumHotel& other) {
    if (this != &other) {
        HotelBase::operator=(other);
        stars = other.stars;
        services = other.services;
        hasPool = other.hasPool;
        hasSpa = other.hasSpa;
        hasRestaurant = other.hasRestaurant;
    }
    return *this;
}

// Оператор переміщувального присвоєння
PremiumHotel& PremiumHotel::operator=(PremiumHotel&& other) noexcept {
    if (this != &other) {
        HotelBase::operator=(std::move(other));
        stars = other.stars;
        services = std::move(other.services);
        hasPool = other.hasPool;
        hasSpa = other.hasSpa;
        hasRestaurant = other.hasRestaurant;
    }
    return *this;
}

// Getters
int PremiumHotel::getStars() const {
    return stars;
}

std::vector<std::string> PremiumHotel::getServices() const {
    return services;
}

bool PremiumHotel::getHasPool() const {
    return hasPool;
}

bool PremiumHotel::getHasSpa() const {
    return hasSpa;
}

bool PremiumHotel::getHasRestaurant() const {
    return hasRestaurant;
}

// Setters
void PremiumHotel::setStars(int stars) {
    this->stars = stars;
}

void PremiumHotel::setServices(const std::vector<std::string>& services) {
    this->services = services;
}

void PremiumHotel::setHasPool(bool hasPool) {
    this->hasPool = hasPool;
}

void PremiumHotel::setHasSpa(bool hasSpa) {
    this->hasSpa = hasSpa;
}

void PremiumHotel::setHasRestaurant(bool hasRestaurant) {
    this->hasRestaurant = hasRestaurant;
}

// Реалізація віртуальних методів

std::string PremiumHotel::getType() const {
    return HOTEL_TYPE_PREMIUM;
}

void PremiumHotel::displayInfo() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "PREMIUM HOTEL" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "ID: " << getHotelId() << std::endl;
    std::cout << "Назва: " << getName() << std::endl;
    std::cout << "Місто: " << getCity() << std::endl;
    std::cout << "Опис: " << getDescription() << std::endl;
    std::cout << "Зірок: " << getStarsRepresentation() << std::endl;
    std::cout << "Кількість номерів: " << getRoomCount() << std::endl;
    std::cout << "Середня ціна: " << std::fixed << std::setprecision(2)
        << calculateAveragePrice() << " грн/ніч" << std::endl;
    std::cout << "Басейн: " << (hasPool ? "Так" : "Ні") << std::endl;
    std::cout << "SPA: " << (hasSpa ? "Так" : "Ні") << std::endl;
    std::cout << "Ресторан: " << (hasRestaurant ? "Так" : "Ні") << std::endl;

    if (!services.empty()) {
        std::cout << "Сервіси: ";
        for (size_t i = 0; i < services.size(); ++i) {
            std::cout << services[i];
            if (i < services.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "========================================" << std::endl;
}

double PremiumHotel::calculateAveragePrice() const {
    if (rooms.empty()) {
        return 0.0;
    }

    double totalPrice = 0.0;
    for (const auto& room : rooms) {
        totalPrice += room.getPricePerNight();
    }

    return totalPrice / rooms.size();
}

// Власні методи

void PremiumHotel::addService(const std::string& service) {
    if (hasService(service)) {
        std::cerr << "Такий сервіс вже існує!" << std::endl;
        return;
    }
    services.push_back(service);
}

bool PremiumHotel::removeService(const std::string& service) {
    auto it = std::remove(services.begin(), services.end(), service);

    if (it != services.end()) {
        services.erase(it, services.end());
        return true;
    }

    return false;
}

void PremiumHotel::displayServices() const {
    if (services.empty()) {
        std::cout << "Додаткові сервіси відсутні." << std::endl;
        return;
    }

    std::cout << "\n=== Доступні сервіси ===" << std::endl;
    for (size_t i = 0; i < services.size(); ++i) {
        std::cout << (i + 1) << ". " << services[i] << std::endl;
    }
}

bool PremiumHotel::hasService(const std::string& service) const {
    return std::find(services.begin(), services.end(), service) != services.end();
}

std::string PremiumHotel::getStarsRepresentation() const {
    std::string result;
    for (int i = 0; i < stars; ++i) {
        result += "★";
    }
    return result + " (" + std::to_string(stars) + ")";
}

bool PremiumHotel::validate() const {
    if (stars < 4 || stars > MAX_STARS) {
        return false;
    }

    if (getName().empty() || getCity().empty()) {
        return false;
    }

    return true;
}

int PremiumHotel::calculateRating() const {
    int rating = stars * 15;

    if (hasPool) rating += 10;
    if (hasSpa) rating += 10;
    if (hasRestaurant) rating += 10;

    rating += services.size() * 5;

    return std::min(rating, 100);
}