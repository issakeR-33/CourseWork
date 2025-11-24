#include "HotelManager.h"
#include "Constants.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Конструктор за замовчуванням
HotelManager::HotelManager()
    : filename(HOTELS_FILE), nextHotelId(1) {
}

// Конструктор з параметром
HotelManager::HotelManager(const std::string& filename)
    : filename(filename), nextHotelId(1) {
}

// Копіювальний конструктор
HotelManager::HotelManager(const HotelManager& other)
    : hotels(other.hotels), filename(other.filename), nextHotelId(other.nextHotelId) {
}

// Переміщувальний конструктор
HotelManager::HotelManager(HotelManager&& other) noexcept
    : hotels(std::move(other.hotels)), filename(std::move(other.filename)),
    nextHotelId(other.nextHotelId) {
}

// Деструктор
HotelManager::~HotelManager() {
    std::cout << "Об'єкт HotelManager знищено." << std::endl;
}

// Оператор копіювального присвоєння
HotelManager& HotelManager::operator=(const HotelManager& other) {
    if (this != &other) {
        hotels = other.hotels;
        filename = other.filename;
        nextHotelId = other.nextHotelId;
    }
    return *this;
}

// Оператор переміщувального присвоєння
HotelManager& HotelManager::operator=(HotelManager&& other) noexcept {
    if (this != &other) {
        hotels = std::move(other.hotels);
        filename = std::move(other.filename);
        nextHotelId = other.nextHotelId;
    }
    return *this;
}

// Getters
std::vector<std::shared_ptr<HotelBase>> HotelManager::getHotels() const {
    return hotels;
}

int HotelManager::getNextHotelId() const {
    return nextHotelId;
}

// Setters
void HotelManager::setFilename(const std::string& filename) {
    this->filename = filename;
}

// Власні методи

bool HotelManager::loadHotels() {
    try {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
            return false;
        }

        hotels.clear();
        std::string line;

        // Пропускаємо заголовок
        std::getline(file, line);

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;

            // Парсимо CSV рядок
            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() < 10) continue;

            int id = std::stoi(tokens[0]);
            std::string type = tokens[1];
            std::string name = tokens[2];
            std::string city = tokens[3];
            std::string description = tokens[4];
            int stars = std::stoi(tokens[5]);
            int roomNumber = std::stoi(tokens[7]);
            std::string roomClass = tokens[8];
            int capacity = std::stoi(tokens[9]);
            double price = std::stod(tokens[10]);

            // Шукаємо чи готель вже існує
            auto existingHotel = findHotel(id);

            if (existingHotel) {
                // Додаємо номер до існуючого готелю
                Room room(roomNumber, roomClass, capacity, price);
                existingHotel->addRoom(room);
            }
            else {
                // Створюємо новий готель
                std::shared_ptr<HotelBase> hotel;

                if (type == HOTEL_TYPE_PREMIUM) {
                    auto premiumHotel = std::make_shared<PremiumHotel>(id, name, city, description, stars);

                    // Додаткові поля для Premium
                    if (tokens.size() > 6 && !tokens[6].empty()) {
                        std::stringstream servicesStream(tokens[6]);
                        std::string service;
                        while (std::getline(servicesStream, service, ';')) {
                            premiumHotel->addService(service);
                        }
                    }

                    hotel = premiumHotel;
                }
                else {
                    auto budgetHotel = std::make_shared<BudgetHotel>(id, name, city, description, stars);

                    // Додаткові поля для Budget
                    if (tokens.size() > 6 && !tokens[6].empty()) {
                        if (tokens[6].find("WiFi") != std::string::npos) budgetHotel->setHasFreeWifi(true);
                        if (tokens[6].find("Parking") != std::string::npos) budgetHotel->setHasFreeParking(true);
                        if (tokens[6].find("Breakfast") != std::string::npos) budgetHotel->setHasBreakfast(true);
                    }

                    hotel = budgetHotel;
                }

                // Додаємо перший номер
                Room room(roomNumber, roomClass, capacity, price);
                hotel->addRoom(room);
                hotels.push_back(hotel);

                if (id >= nextHotelId) {
                    nextHotelId = id + 1;
                }
            }
        }

        file.close();
        return true;

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка завантаження готелів: " << e.what() << std::endl;
        return false;
    }
}

bool HotelManager::saveHotels() {
    try {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
            return false;
        }

        // Записуємо заголовок
        file << "id,type,name,city,description,stars,services,room_number,room_class,capacity,price" << std::endl;

        // Записуємо дані
        for (const auto& hotel : hotels) {
            std::string type = hotel->getType();
            std::string services = "";
            int stars = 0;

            if (type == HOTEL_TYPE_PREMIUM) {
                auto premiumHotel = std::dynamic_pointer_cast<PremiumHotel>(hotel);
                if (premiumHotel) {
                    stars = premiumHotel->getStars();
                    auto servicesList = premiumHotel->getServices();
                    for (size_t i = 0; i < servicesList.size(); ++i) {
                        services += servicesList[i];
                        if (i < servicesList.size() - 1) services += ";";
                    }
                }
            }
            else {
                auto budgetHotel = std::dynamic_pointer_cast<BudgetHotel>(hotel);
                if (budgetHotel) {
                    stars = budgetHotel->getStars();
                    if (budgetHotel->getHasFreeWifi()) services += "WiFi;";
                    if (budgetHotel->getHasFreeParking()) services += "Parking;";
                    if (budgetHotel->getHasBreakfast()) services += "Breakfast;";
                }
            }

            // Записуємо кожен номер готелю
            for (const auto& room : hotel->getRooms()) {
                file << hotel->getHotelId() << ","
                    << type << ","
                    << hotel->getName() << ","
                    << hotel->getCity() << ","
                    << hotel->getDescription() << ","
                    << stars << ","
                    << services << ","
                    << room.getRoomNumber() << ","
                    << room.getRoomClass() << ","
                    << room.getCapacity() << ","
                    << room.getPricePerNight() << std::endl;
            }
        }

        file.close();
        return true;

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка збереження готелів: " << e.what() << std::endl;
        return false;
    }
}

bool HotelManager::addHotel(std::shared_ptr<HotelBase> hotel) {
    if (!hotel) {
        std::cerr << "Некоректний вказівник на готель!" << std::endl;
        return false;
    }

    hotel->setHotelId(nextHotelId++);
    hotels.push_back(hotel);
    return saveHotels();
}

bool HotelManager::removeHotel(int hotelId) {
    auto it = std::remove_if(hotels.begin(), hotels.end(),
        [hotelId](const std::shared_ptr<HotelBase>& hotel) {
            return hotel->getHotelId() == hotelId;
        });

    if (it != hotels.end()) {
        hotels.erase(it, hotels.end());
        return saveHotels();
    }

    return false;
}

std::shared_ptr<HotelBase> HotelManager::findHotel(int hotelId) {
    for (auto& hotel : hotels) {
        if (hotel->getHotelId() == hotelId) {
            return hotel;
        }
    }
    return nullptr;
}

void HotelManager::displayAllHotels() const {
    if (hotels.empty()) {
        std::cout << "\nНемає готелів у базі даних." << std::endl;
        return;
    }

    std::cout << "\n========== СПИСОК ГОТЕЛІВ ==========" << std::endl;
    for (const auto& hotel : hotels) {
        hotel->displayInfo();
    }
    std::cout << "\nВсього готелів: " << hotels.size() << std::endl;
}

std::vector<std::shared_ptr<HotelBase>> HotelManager::findHotelsByCity(const std::string& city) const {
    std::vector<std::shared_ptr<HotelBase>> result;

    std::copy_if(hotels.begin(), hotels.end(), std::back_inserter(result),
        [&city](const std::shared_ptr<HotelBase>& hotel) {
            return hotel->getCity() == city;
        });

    return result;
}

std::vector<std::shared_ptr<HotelBase>> HotelManager::findHotelsByType(const std::string& type) const {
    std::vector<std::shared_ptr<HotelBase>> result;

    std::copy_if(hotels.begin(), hotels.end(), std::back_inserter(result),
        [&type](const std::shared_ptr<HotelBase>& hotel) {
            return hotel->getType() == type;
        });

    return result;
}

std::vector<std::shared_ptr<HotelBase>> HotelManager::findHotelsByStars(int stars) const {
    std::vector<std::shared_ptr<HotelBase>> result;

    for (const auto& hotel : hotels) {
        if (hotel->getType() == HOTEL_TYPE_PREMIUM) {
            auto premiumHotel = std::dynamic_pointer_cast<PremiumHotel>(hotel);
            if (premiumHotel && premiumHotel->getStars() == stars) {
                result.push_back(hotel);
            }
        }
        else {
            auto budgetHotel = std::dynamic_pointer_cast<BudgetHotel>(hotel);
            if (budgetHotel && budgetHotel->getStars() == stars) {
                result.push_back(hotel);
            }
        }
    }

    return result;
}

std::vector<std::shared_ptr<HotelBase>> HotelManager::findAvailableRooms(
    const std::string& city,
    const std::string& roomClass,
    int minCapacity,
    double maxPrice) const {

    std::vector<std::shared_ptr<HotelBase>> result;

    for (const auto& hotel : hotels) {
        // Фільтр по місту
        if (!city.empty() && hotel->getCity() != city) {
            continue;
        }

        // Перевіряємо номери
        bool hasMatchingRoom = false;
        for (const auto& room : hotel->getRooms()) {
            if (!room.getIsAvailable()) continue;

            if (!roomClass.empty() && room.getRoomClass() != roomClass) continue;
            if (room.getCapacity() < minCapacity) continue;
            if (room.getPricePerNight() > maxPrice) continue;

            hasMatchingRoom = true;
            break;
        }

        if (hasMatchingRoom) {
            result.push_back(hotel);
        }
    }

    return result;
}

std::vector<std::shared_ptr<HotelBase>> HotelManager::sortByPrice() const {
    std::vector<std::shared_ptr<HotelBase>> sorted = hotels;

    std::sort(sorted.begin(), sorted.end(),
        [](const std::shared_ptr<HotelBase>& a, const std::shared_ptr<HotelBase>& b) {
            return a->calculateAveragePrice() < b->calculateAveragePrice();
        });

    return sorted;
}

std::vector<std::shared_ptr<HotelBase>> HotelManager::sortByName() const {
    std::vector<std::shared_ptr<HotelBase>> sorted = hotels;

    std::sort(sorted.begin(), sorted.end(),
        [](const std::shared_ptr<HotelBase>& a, const std::shared_ptr<HotelBase>& b) {
            return a->getName() < b->getName();
        });

    return sorted;
}

int HotelManager::getHotelCount() const {
    return hotels.size();
}