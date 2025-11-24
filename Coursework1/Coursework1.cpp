#include <iostream>
#include <limits>
#include <string>
#include "Constants.hpp"
#include "UserAccountManager.h"
#include "HotelManager.h"
#include "BookingManager.h"
#include "PremiumHotel.h"
#include "BudgetHotel.h"

// Функція для очищення буфера вводу
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Функція для очікування натискання Enter
void waitForEnter() {
    std::cout << "\nНатисніть Enter для продовження...";
    clearInput();
}

// Функція виведення головного меню
void displayMainMenu(bool isAdmin) {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║   СИСТЕМА БРОНЮВАННЯ ГОТЕЛІВ          ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    std::cout << "1.  Переглянути всі готелі" << std::endl;
    std::cout << "2.  Пошук готелів" << std::endl;
    std::cout << "3.  Переглянути бронювання" << std::endl;
    std::cout << "4.  Створити бронювання" << std::endl;
    std::cout << "5.  Скасувати бронювання" << std::endl;
    std::cout << "6.  Пошук бронювань" << std::endl;

    if (isAdmin) {
        std::cout << "\n--- Адміністративні функції ---" << std::endl;
        std::cout << "7.  Додати готель" << std::endl;
        std::cout << "8.  Видалити готель" << std::endl;
        std::cout << "9.  Додати номер до готелю" << std::endl;
        std::cout << "10. Управління користувачами" << std::endl;
        std::cout << "11. Статистика" << std::endl;
    }

    std::cout << "\n12. Інструкція користувача" << std::endl;
    std::cout << "0.  Вихід" << std::endl;
    std::cout << "\nВаш вибір: ";
}

// Функція виведення інструкції
void displayHelp() {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║   ІНСТРУКЦІЯ КОРИСТУВАЧА               ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    std::cout << "\n=== Пояснення роботи програми ===" << std::endl;
    std::cout << "Ця система призначена для управління бронюванням готелів." << std::endl;
    std::cout << "\n=== Правила вводу даних ===" << std::endl;
    std::cout << "- Дати вводити у форматі: ДД.ММ.РРРР (наприклад: 25.12.2025)" << std::endl;
    std::cout << "- Паспортні дані: 2 літери + 6 цифр (наприклад: АА123456)" << std::endl;
    std::cout << "- Всі поля обов'язкові для заповнення" << std::endl;
    std::cout << "\n=== Короткий опис команд ===" << std::endl;
    std::cout << "1. Перегляд готелів - показує всі доступні готелі" << std::endl;
    std::cout << "2. Пошук готелів - пошук за містом, типом або зірками" << std::endl;
    std::cout << "3. Перегляд бронювань - показує всі бронювання" << std::endl;
    std::cout << "4. Створити бронювання - нове бронювання номера" << std::endl;
    std::cout << "5. Скасувати бронювання - скасування існуючого бронювання" << std::endl;
    std::cout << "6. Пошук бронювань - пошук за клієнтом або паспортом" << std::endl;
    std::cout << "\n=== Адміністративні функції ===" << std::endl;
    std::cout << "Доступні лише для адміністратора." << std::endl;
    std::cout << "Дозволяють додавати/видаляти готелі, керувати користувачами." << std::endl;
}

// Функція пошуку готелів
void searchHotels(HotelManager& hotelManager) {
    std::cout << "\n=== Пошук готелів ===" << std::endl;
    std::cout << "1. За містом" << std::endl;
    std::cout << "2. За типом (Premium/Budget)" << std::endl;
    std::cout << "3. За кількістю зірок" << std::endl;
    std::cout << "4. Пошук вільних номерів" << std::endl;
    std::cout << "Виберіть опцію: ";

    int choice;
    std::cin >> choice;
    clearInput();

    try {
        switch (choice) {
        case 1: {
            std::cout << "Введіть місто: ";
            std::string city;
            std::getline(std::cin, city);

            auto results = hotelManager.findHotelsByCity(city);
            if (results.empty()) {
                std::cout << "Готелі не знайдено." << std::endl;
            }
            else {
                for (const auto& hotel : results) {
                    hotel->displayInfo();
                }
            }
            break;
        }
        case 2: {
            std::cout << "Введіть тип (Premium/Budget): ";
            std::string type;
            std::getline(std::cin, type);

            auto results = hotelManager.findHotelsByType(type);
            if (results.empty()) {
                std::cout << "Готелі не знайдено." << std::endl;
            }
            else {
                for (const auto& hotel : results) {
                    hotel->displayInfo();
                }
            }
            break;
        }
        case 3: {
            std::cout << "Введіть кількість зірок (1-5): ";
            int stars;
            std::cin >> stars;
            clearInput();

            auto results = hotelManager.findHotelsByStars(stars);
            if (results.empty()) {
                std::cout << "Готелі не знайдено." << std::endl;
            }
            else {
                for (const auto& hotel : results) {
                    hotel->displayInfo();
                }
            }
            break;
        }
        case 4: {
            std::cout << "Введіть місто (або Enter для пропуску): ";
            std::string city;
            std::getline(std::cin, city);

            std::cout << "Введіть клас номера (Luxury/Standard/Economy або Enter): ";
            std::string roomClass;
            std::getline(std::cin, roomClass);

            std::cout << "Введіть мінімальну місткість: ";
            int capacity;
            std::cin >> capacity;

            std::cout << "Введіть максимальну ціну: ";
            double maxPrice;
            std::cin >> maxPrice;
            clearInput();

            auto results = hotelManager.findAvailableRooms(city, roomClass, capacity, maxPrice);
            if (results.empty()) {
                std::cout << "Номери не знайдено." << std::endl;
            }
            else {
                for (const auto& hotel : results) {
                    hotel->displayInfo();
                    hotel->displayRooms();
                }
            }
            break;
        }
        default:
            std::cout << "Некоректний вибір!" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Помилка пошуку: " << e.what() << std::endl;
    }
}

// Функція створення бронювання
void createBooking(BookingManager& bookingManager, HotelManager& hotelManager) {
    std::cout << "\n=== Створення бронювання ===" << std::endl;

    try {
        std::cout << "Введіть ID готелю: ";
        int hotelId;
        std::cin >> hotelId;
        clearInput();

        auto hotel = hotelManager.findHotel(hotelId);
        if (!hotel) {
            std::cout << "Готель не знайдено!" << std::endl;
            return;
        }

        hotel->displayRooms();

        std::cout << "\nВведіть номер кімнати: ";
        int roomNumber;
        std::cin >> roomNumber;
        clearInput();

        std::cout << "Введіть ім'я клієнта: ";
        std::string clientName;
        std::getline(std::cin, clientName);

        std::cout << "Введіть паспортні дані: ";
        std::string passport;
        std::getline(std::cin, passport);

        std::cout << "Введіть дату заїзду (ДД.ММ.РРРР): ";
        std::string checkIn;
        std::getline(std::cin, checkIn);

        std::cout << "Введіть дату виїзду (ДД.ММ.РРРР): ";
        std::string checkOut;
        std::getline(std::cin, checkOut);

        if (bookingManager.createBooking(hotelId, roomNumber, clientName, passport, checkIn, checkOut)) {
            std::cout << "\n✓ Бронювання успішно створено!" << std::endl;
        }
        else {
            std::cout << "\n✗ Помилка створення бронювання!" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }
}

// Функція пошуку бронювань
void searchBookings(BookingManager& bookingManager) {
    std::cout << "\n=== Пошук бронювань ===" << std::endl;
    std::cout << "1. За іменем клієнта" << std::endl;
    std::cout << "2. За паспортом" << std::endl;
    std::cout << "3. За готелем" << std::endl;
    std::cout << "4. За статусом" << std::endl;
    std::cout << "Виберіть опцію: ";

    int choice;
    std::cin >> choice;
    clearInput();

    try {
        switch (choice) {
        case 1: {
            std::cout << "Введіть ім'я клієнта: ";
            std::string name;
            std::getline(std::cin, name);

            auto results = bookingManager.findBookingsByClient(name);
            if (results.empty()) {
                std::cout << "Бронювання не знайдено." << std::endl;
            }
            else {
                for (const auto& booking : results) {
                    booking.displayInfo();
                }
            }
            break;
        }
        case 2: {
            std::cout << "Введіть паспортні дані: ";
            std::string passport;
            std::getline(std::cin, passport);

            auto results = bookingManager.findBookingsByPassport(passport);
            if (results.empty()) {
                std::cout << "Бронювання не знайдено." << std::endl;
            }
            else {
                for (const auto& booking : results) {
                    booking.displayInfo();
                }
            }
            break;
        }
        case 3: {
            std::cout << "Введіть ID готелю: ";
            int hotelId;
            std::cin >> hotelId;
            clearInput();

            auto results = bookingManager.findBookingsByHotel(hotelId);
            if (results.empty()) {
                std::cout << "Бронювання не знайдено." << std::endl;
            }
            else {
                for (const auto& booking : results) {
                    booking.displayInfo();
                }
            }
            break;
        }
        case 4: {
            std::cout << "Введіть статус (Active/Completed/Cancelled): ";
            std::string status;
            std::getline(std::cin, status);

            auto results = bookingManager.findBookingsByStatus(status);
            if (results.empty()) {
                std::cout << "Бронювання не знайдено." << std::endl;
            }
            else {
                for (const auto& booking : results) {
                    booking.displayInfo();
                }
            }
            break;
        }
        default:
            std::cout << "Некоректний вибір!" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Помилка пошуку: " << e.what() << std::endl;
    }
}

// Функція додавання готелю
void addHotel(HotelManager& hotelManager) {
    std::cout << "\n=== Додавання готелю ===" << std::endl;
    std::cout << "Виберіть тип готелю:" << std::endl;
    std::cout << "1. Premium (4-5 зірок)" << std::endl;
    std::cout << "2. Budget (1-3 зірки)" << std::endl;
    std::cout << "Ваш вибір: ";

    int type;
    std::cin >> type;
    clearInput();

    try {
        std::cout << "Введіть назву готелю: ";
        std::string name;
        std::getline(std::cin, name);

        std::cout << "Введіть місто: ";
        std::string city;
        std::getline(std::cin, city);

        std::cout << "Введіть опис: ";
        std::string description;
        std::getline(std::cin, description);

        std::cout << "Введіть кількість зірок: ";
        int stars;
        std::cin >> stars;
        clearInput();

        std::shared_ptr<HotelBase> hotel;

        if (type == 1) {
            hotel = std::make_shared<PremiumHotel>(0, name, city, description, stars);
        }
        else {
            hotel = std::make_shared<BudgetHotel>(0, name, city, description, stars);
        }

        if (hotelManager.addHotel(hotel)) {
            std::cout << "\n✓ Готель успішно додано!" << std::endl;
        }
        else {
            std::cout << "\n✗ Помилка додавання готелю!" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }
}

// Функція управління користувачами
void manageUsers(UserAccountManager& userManager) {
    std::cout << "\n=== Управління користувачами ===" << std::endl;
    std::cout << "1. Переглянути всіх користувачів" << std::endl;
    std::cout << "2. Додати користувача" << std::endl;
    std::cout << "3. Видалити користувача" << std::endl;
    std::cout << "Виберіть опцію: ";

    int choice;
    std::cin >> choice;
    clearInput();

    try {
        switch (choice) {
        case 1:
            userManager.displayAllUsers();
            break;
        case 2: {
            std::cout << "Введіть логін: ";
            std::string username;
            std::getline(std::cin, username);

            std::cout << "Введіть пароль: ";
            std::string password;
            std::getline(std::cin, password);

            std::cout << "Рівень доступу (1-Адмін, 2-Користувач): ";
            int accessLevel;
            std::cin >> accessLevel;
            clearInput();

            if (userManager.registerUser(username, password, accessLevel)) {
                std::cout << "\n✓ Користувача додано!" << std::endl;
            }
            else {
                std::cout << "\n✗ Помилка додавання користувача!" << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Введіть логін користувача для видалення: ";
            std::string username;
            std::getline(std::cin, username);

            if (userManager.deleteUser(username)) {
                std::cout << "\n✓ Користувача видалено!" << std::endl;
            }
            else {
                std::cout << "\n✗ Помилка видалення користувача!" << std::endl;
            }
            break;
        }
        default:
            std::cout << "Некоректний вибір!" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }
}

// Функція виведення статистики
void displayStatistics(HotelManager& hotelManager, BookingManager& bookingManager) {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║           СТАТИСТИКА СИСТЕМИ           ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;

    std::cout << "Всього готелів: " << hotelManager.getHotelCount() << std::endl;
    std::cout << "Всього бронювань: " << bookingManager.getBookingCount() << std::endl;
    std::cout << "Активних бронювань: " << bookingManager.getActiveBookings().size() << std::endl;
    std::cout << "Загальний дохід: " << bookingManager.calculateTotalRevenue() << " грн" << std::endl;
}

int main() {
    std::cout << "╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║   СИСТЕМА БРОНЮВАННЯ ГОТЕЛІВ          ║" << std::endl;
    std::cout << "║        Запуск програми...              ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝\n" << std::endl;

    try {
        // Ініціалізація менеджерів
        UserAccountManager userManager;
        HotelManager hotelManager;
        BookingManager bookingManager(BOOKINGS_FILE, &hotelManager);

        // Завантаження даних
        userManager.loadUsers();
        hotelManager.loadHotels();
        bookingManager.loadBookings();

        // Авторизація
        bool authenticated = false;
        int attempts = 0;
        const int maxAttempts = 3;

        while (!authenticated && attempts < maxAttempts) {
            std::cout << "\n=== АВТОРИЗАЦІЯ ===" << std::endl;
            std::cout << "Логін: ";
            std::string username;
            std::getline(std::cin, username);

            std::cout << "Пароль: ";
            std::string password;
            std::getline(std::cin, password);

            if (userManager.login(username, password)) {
                authenticated = true;
                std::cout << "\n✓ " << MSG_LOGIN_SUCCESS << std::endl;
                std::cout << "Вітаємо, " << username << "!" << std::endl;
            }
            else {
                attempts++;
                std::cout << "\n✗ " << MSG_LOGIN_FAILED << std::endl;
                std::cout << "Залишилось спроб: " << (maxAttempts - attempts) << std::endl;
            }
        }

        if (!authenticated) {
            std::cout << "\nПеревищено кількість спроб входу. Програма завершується." << std::endl;
            return 1;
        }

        // Головний цикл програми
        bool running = true;
        bool isAdmin = userManager.isCurrentUserAdmin();

        while (running) {
            displayMainMenu(isAdmin);

            int choice;
            std::cin >> choice;
            clearInput();

            try {
                switch (choice) {
                case 1:
                    hotelManager.displayAllHotels();
                    waitForEnter();
                    break;

                case 2:
                    searchHotels(hotelManager);
                    waitForEnter();
                    break;

                case 3:
                    bookingManager.displayAllBookings();
                    waitForEnter();
                    break;

                case 4:
                    createBooking(bookingManager, hotelManager);
                    waitForEnter();
                    break;

                case 5: {
                    std::cout << "Введіть ID бронювання для скасування: ";
                    int bookingId;
                    std::cin >> bookingId;
                    clearInput();

                    if (bookingManager.cancelBooking(bookingId)) {
                        std::cout << "\n✓ Бронювання скасовано!" << std::endl;
                    }
                    else {
                        std::cout << "\n✗ Помилка скасування бронювання!" << std::endl;
                    }
                    waitForEnter();
                    break;
                }

                case 6:
                    searchBookings(bookingManager);
                    waitForEnter();
                    break;

                case 7:
                    if (isAdmin) {
                        addHotel(hotelManager);
                    }
                    else {
                        std::cout << MSG_ACCESS_DENIED << std::endl;
                    }
                    waitForEnter();
                    break;

                case 8:
                    if (isAdmin) {
                        std::cout << "Введіть ID готелю для видалення: ";
                        int hotelId;
                        std::cin >> hotelId;
                        clearInput();

                        if (hotelManager.removeHotel(hotelId)) {
                            std::cout << "\n✓ Готель видалено!" << std::endl;
                        }
                        else {
                            std::cout << "\n✗ Помилка видалення готелю!" << std::endl;
                        }
                    }
                    else {
                        std::cout << MSG_ACCESS_DENIED << std::endl;
                    }
                    waitForEnter();
                    break;

                case 9:
                    if (isAdmin) {
                        std::cout << "Функція додавання номера (розширити за необхідністю)" << std::endl;
                    }
                    else {
                        std::cout << MSG_ACCESS_DENIED << std::endl;
                    }
                    waitForEnter();
                    break;

                case 10:
                    if (isAdmin) {
                        manageUsers(userManager);
                    }
                    else {
                        std::cout << MSG_ACCESS_DENIED << std::endl;
                    }
                    waitForEnter();
                    break;

                case 11:
                    if (isAdmin) {
                        displayStatistics(hotelManager, bookingManager);
                    }
                    else {
                        std::cout << MSG_ACCESS_DENIED << std::endl;
                    }
                    waitForEnter();
                    break;

                case 12:
                    displayHelp();
                    waitForEnter();
                    break;

                case 0:
                    std::cout << "\nЗбереження даних..." << std::endl;
                    hotelManager.saveHotels();
                    bookingManager.saveBookings();
                    userManager.saveUsers();
                    std::cout << "До побачення!" << std::endl;
                    running = false;
                    break;

                default:
                    std::cout << MSG_INVALID_INPUT << std::endl;
                    waitForEnter();
                }

            }
            catch (const std::exception& e) {
                std::cerr << "\nПомилка виконання операції: " << e.what() << std::endl;
                waitForEnter();
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Критична помилка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}