#include "HotelBase.h"
#include <iostream>
#include <algorithm>

// Конструктор за замовчуванням
HotelBase::HotelBase()
    : hotelId(0), name(""), city(""), description("") {
}

// Конструктор з параметрами
HotelBase::HotelBase(int id, const std::string& name, const std::string& city, const std::string& description)
    : hotelId(id), name(name), city(city), description(description) {
}

// Копіювальний конструктор
HotelBase::HotelBase(const HotelBase& other)
    : hotelId(other.hotelId), name(other.name), city(other.city),
    description(other.description), rooms(other.rooms) {
}

// Переміщувальний конструктор
HotelBase::HotelBase(HotelBase&& other) noexcept
    : hotelId(other.hotelId), name(std::move(other.name)),
    city(std::move(other.city)), description(std::move(other.description)),
    rooms(std::move(other.rooms)) {
}

// Деструктор
HotelBase::~HotelBase() {
    std::cout << "Об'єкт HotelBase '" << name << "' знищено." << std::endl;
}

// Оператор копіювального присвоєння
HotelBase& HotelBase::operator=(const HotelBase& other) {
    if (this != &other) {
        hotelId = other.hotelId;
        name = other.name;
        city = other.city;
        description = other.description;
        rooms = other.rooms;
    }
    return *this;
}

// Оператор переміщувального присвоєння
HotelBase& HotelBase::operator=(HotelBase&& other) noexcept {
    if (this != &other) {
        hotelId = other.hotelId;
        name = std::move(other.name);
        city = std::move(other.city);
        description = std::move(other.description);
        rooms = std::move(other.rooms);
    }
    return *this;
}

// Getters
int HotelBase::getHotelId() const {
    return hotelId;
}

std::string HotelBase::getName() const {
    return name;
}

std::string HotelBase::getCity() const {
    return city;
}

std::string HotelBase::getDescription() const {
    return description;
}

std::vector<Room> HotelBase::getRooms() const {
    return rooms;
}

// Setters
void HotelBase::setHotelId(int id) {
    this->hotelId = id;
}

void HotelBase::setName(const std::string& name) {
    this->name = name;
}

void HotelBase::setCity(const std::string& city) {
    this->city = city;
}

void HotelBase::setDescription(const std::string& description) {
    this->description = description;
}

void HotelBase::setRooms(const std::vector<Room>& rooms) {
    this->rooms = rooms;
}

// Власні методи

void HotelBase::addRoom(const Room& room) {
    if (!room.validate()) {
        std::cerr << "Некоректні дані номера!" << std::endl;
        return;
    }

    if (findRoom(room.getRoomNumber()) != nullptr) {
        std::cerr << "Номер з таким номером вже існує!" << std::endl;
        return;
    }

    rooms.push_back(room);
}

bool HotelBase::removeRoom(int roomNumber) {
    auto it = std::remove_if(rooms.begin(), rooms.end(),
        [roomNumber](const Room& room) { return room.getRoomNumber() == roomNumber; });

    if (it != rooms.end()) {
        rooms.erase(it, rooms.end());
        return true;
    }

    return false;
}

Room* HotelBase::findRoom(int roomNumber) {
    for (auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            return &room;
        }
    }
    return nullptr;
}

int HotelBase::getRoomCount() const {
    return rooms.size();
}

void HotelBase::displayRooms() const {
    if (rooms.empty()) {
        std::cout << "Немає доступних номерів." << std::endl;
        return;
    }

    std::cout << "\n=== Номери готелю '" << name << "' ===" << std::endl;
    for (const auto& room : rooms) {
        room.displayInfo();
    }
}

bool HotelBase::hasAvailableRooms() const {
    return std::any_of(rooms.begin(), rooms.end(),
        [](const Room& room) { return room.getIsAvailable(); });
}

std::vector<Room> HotelBase::getRoomsByClass(const std::string& roomClass) const {
    std::vector<Room> result;

    std::copy_if(rooms.begin(), rooms.end(), std::back_inserter(result),
        [&roomClass](const Room& room) { return room.getRoomClass() == roomClass; });

    return result;
}