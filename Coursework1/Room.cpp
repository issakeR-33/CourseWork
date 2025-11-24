#include "Room.h"
#include "Constants.hpp"
#include <iomanip>

// Конструктор за замовчуванням
Room::Room()
    : roomNumber(0), roomClass(ROOM_CLASS_STANDARD), capacity(2), pricePerNight(0.0), isAvailable(true) {
}

// Конструктор з параметрами
Room::Room(int roomNumber, const std::string& roomClass, int capacity, double pricePerNight)
    : roomNumber(roomNumber), roomClass(roomClass), capacity(capacity),
    pricePerNight(pricePerNight), isAvailable(true) {
}

// Копіювальний конструктор
Room::Room(const Room& other)
    : roomNumber(other.roomNumber), roomClass(other.roomClass),
    capacity(other.capacity), pricePerNight(other.pricePerNight),
    isAvailable(other.isAvailable) {
}

// Переміщувальний конструктор
Room::Room(Room&& other) noexcept
    : roomNumber(other.roomNumber), roomClass(std::move(other.roomClass)),
    capacity(other.capacity), pricePerNight(other.pricePerNight),
    isAvailable(other.isAvailable) {
}

// Деструктор
Room::~Room() {
    // std::cout << "Об'єкт Room #" << roomNumber << " знищено." << std::endl;
}

// Оператор копіювального присвоєння
Room& Room::operator=(const Room& other) {
    if (this != &other) {
        roomNumber = other.roomNumber;
        roomClass = other.roomClass;
        capacity = other.capacity;
        pricePerNight = other.pricePerNight;
        isAvailable = other.isAvailable;
    }
    return *this;
}

// Оператор переміщувального присвоєння
Room& Room::operator=(Room&& other) noexcept {
    if (this != &other) {
        roomNumber = other.roomNumber;
        roomClass = std::move(other.roomClass);
        capacity = other.capacity;
        pricePerNight = other.pricePerNight;
        isAvailable = other.isAvailable;
    }
    return *this;
}

// Getters
int Room::getRoomNumber() const {
    return roomNumber;
}

std::string Room::getRoomClass() const {
    return roomClass;
}

int Room::getCapacity() const {
    return capacity;
}

double Room::getPricePerNight() const {
    return pricePerNight;
}

bool Room::getIsAvailable() const {
    return isAvailable;
}

// Setters
void Room::setRoomNumber(int roomNumber) {
    this->roomNumber = roomNumber;
}

void Room::setRoomClass(const std::string& roomClass) {
    this->roomClass = roomClass;
}

void Room::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Room::setPricePerNight(double price) {
    this->pricePerNight = price;
}

void Room::setIsAvailable(bool available) {
    this->isAvailable = available;
}

// Власні методи

void Room::displayInfo() const {
    std::cout << "Номер: " << roomNumber
        << " | Клас: " << roomClass
        << " | Місць: " << capacity
        << " | Ціна/ніч: " << std::fixed << std::setprecision(2) << pricePerNight << " грн"
        << " | Статус: " << (isAvailable ? "Вільний" : "Зайнятий") << std::endl;
}

bool Room::validate() const {
    if (roomNumber <= 0) {
        return false;
    }

    if (capacity < MIN_CAPACITY || capacity > MAX_CAPACITY) {
        return false;
    }

    if (pricePerNight < MIN_PRICE || pricePerNight > MAX_PRICE) {
        return false;
    }

    if (roomClass != ROOM_CLASS_LUXURY &&
        roomClass != ROOM_CLASS_STANDARD &&
        roomClass != ROOM_CLASS_ECONOMY) {
        return false;
    }

    return true;
}

double Room::calculateTotalPrice(int nights) const {
    if (nights <= 0) {
        return 0.0;
    }
    return pricePerNight * nights;
}

void Room::applyDiscount(double discountPercent) {
    if (discountPercent < 0 || discountPercent > 100) {
        std::cerr << "Некоректний відсоток знижки!" << std::endl;
        return;
    }

    pricePerNight = pricePerNight * (1.0 - discountPercent / 100.0);
}

std::string Room::getDetailedDescription() const {
    std::string status = isAvailable ? "вільний" : "зайнятий";
    return "Номер " + std::to_string(roomNumber) +
        " (" + roomClass + ", " + std::to_string(capacity) + " місць) - " +
        std::to_string(pricePerNight) + " грн/ніч [" + status + "]";
}

void Room::book() {
    isAvailable = false;
}

void Room::release() {
    isAvailable = true;
}

bool Room::isCheaperThan(const Room& other) const {
    return pricePerNight < other.pricePerNight;
}