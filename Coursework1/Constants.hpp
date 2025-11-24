#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

// Файли даних
const std::string USERS_FILE = "users.txt";
const std::string HOTELS_FILE = "hotels.csv";
const std::string BOOKINGS_FILE = "bookings.csv";

// Рівні доступу користувачів
const int ACCESS_LEVEL_ADMIN = 1;
const int ACCESS_LEVEL_USER = 2;

// Типи готелів
const std::string HOTEL_TYPE_PREMIUM = "Premium";
const std::string HOTEL_TYPE_BUDGET = "Budget";

// Класи номерів
const std::string ROOM_CLASS_LUXURY = "Luxury";
const std::string ROOM_CLASS_STANDARD = "Standard";
const std::string ROOM_CLASS_ECONOMY = "Economy";

// Статуси бронювання
const std::string BOOKING_STATUS_ACTIVE = "Active";
const std::string BOOKING_STATUS_COMPLETED = "Completed";
const std::string BOOKING_STATUS_CANCELLED = "Cancelled";

// Обмеження
const int MIN_PASSWORD_LENGTH = 4;
const int MAX_USERNAME_LENGTH = 50;
const int MIN_STARS = 1;
const int MAX_STARS = 5;
const int MIN_CAPACITY = 1;
const int MAX_CAPACITY = 10;
const double MIN_PRICE = 0.0;
const double MAX_PRICE = 100000.0;

// Повідомлення
const std::string MSG_LOGIN_SUCCESS = "Успішна авторизація!";
const std::string MSG_LOGIN_FAILED = "Невірний логін або пароль!";
const std::string MSG_ACCESS_DENIED = "Доступ заборонено!";
const std::string MSG_INVALID_INPUT = "Некоректне введення!";
const std::string MSG_FILE_ERROR = "Помилка роботи з файлом!";
const std::string MSG_DATA_SAVED = "Дані успішно збережено!";
const std::string MSG_DATA_LOADED = "Дані успішно завантажено!";

// Формат дати
const std::string DATE_FORMAT = "DD.MM.YYYY";

#endif // CONSTANTS_H