#include "metro.h"

int main() {
    std::vector<std::thread> metroTrains;

    std::cout << "Запуск симуляции метро Баку..." << std::endl;

    for (int i = 1; i <= 28; ++i) {
        std::ofstream file("train_" + std::to_string(i) + ".txt");
        if (file.is_open()) {
            file << "=== Инициализация файла логов для поезда " << i << " ===" << std::endl;
            file.close();
        } else {
            std::cerr << "Ошибка: не удалось создать файл логов для поезда " << i << std::endl;
            return 1;
        }
    }

    try {
        std::cout << "Запуск поездов фиолетовой линии..." << std::endl;
        for (int i = 1; i <= 6; ++i) {
            metroTrains.push_back(std::thread([i]() {
                Dvijeniye_violete(i, 5);
            }));

            sleep_(15);
            std::cout << "Поезд #" << i << " фиолетовой линии запущен" << std::endl;
        }

        std::cout << "Запуск поездов зеленой линии..." << std::endl;
        for (int i = 7; i <= 16; ++i) {
            int greenIndex = i;
            metroTrains.push_back(std::thread([greenIndex]() {
                train_time_offset[greenIndex] = (greenIndex - 7) * 20;

                Dvijeniye_green(greenIndex, 5);
            }));

            sleep_(15);
            std::cout << "Поезд #" << i << " зеленой линии запущен" << std::endl;

            if (i <= 16) {
                int redIndex = i + 10;
                metroTrains.push_back(std::thread([redIndex]() {
                    train_time_offset[redIndex] = ((redIndex - 17) * 20) + 10;

                    Dvijeniye_krasniy(redIndex, 5);
                }));

                sleep_(15);
                std::cout << "Поезд #" << redIndex << " красной линии запущен" << std::endl;
            }
        }

        for (int i = 27; i!= 29; ++i) {
            metroTrains.push_back(std::thread([i]() {
                Dvijeniye_Solatoviy(i, 10);
            }));

            sleep_(15);
            std::cout << "Поезд #" << i << " солатовой линии запущен" << std::endl;
        }

        std::cout << "Все поезда запущены. Симуляция выполняется..." << std::endl;

        for (auto& train : metroTrains) {
            if (train.joinable()) {
                train.join();
            }
        }

        std::cout << "Симуляция метро Баку завершена успешно." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в симуляции: " << e.what() << std::endl;

        for (auto& train : metroTrains) {
            if (train.joinable()) {
                train.join();
            }
        }

        return 1;
    }

    return 0;
}