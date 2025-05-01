#include "metro.h"

int main() {
    std::vector<std::thread> metroTrains;
    
    std::cout << "Запуск симуляции метро Баку..." << std::endl;
    
    // Инициализация файлов для логов (6 + 10 + 10 = 26 поездов)
    // 6 на фиолетовой, 10 на зеленой, 10 на красной линии
    for (int i = 1; i <= 26; ++i) {
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
        // Запуск поездов фиолетовой линии (индексы 1-6)
        std::cout << "Запуск поездов фиолетовой линии..." << std::endl;
        for (int i = 1; i <= 6; ++i) {
            metroTrains.push_back(std::thread([i]() {
                Dvijeniye_violete(i);
            }));
            
            sleep_(15);
            std::cout << "Поезд #" << i << " фиолетовой линии запущен" << std::endl;
        }
        
        // Запуск поездов зеленой линии (индексы 7-16, начиная с 6:00)
        std::cout << "Запуск поездов зеленой линии..." << std::endl;
        for (int i = 7; i <= 16; ++i) {
            int greenIndex = i;
            metroTrains.push_back(std::thread([greenIndex]() {
                // Чередование с поездами красной линии
                // Зеленые поезда: 6:00, 6:20, 6:40...
                train_time_offset[greenIndex] = (greenIndex - 7) * 20;
                
                // Запуск движения на 5 кругов
                Dvijeniye_green(greenIndex, 5);
            }));
            
            sleep_(15);
            std::cout << "Поезд #" << i << " зеленой линии запущен" << std::endl;
            
            // Запускаем соответствующий поезд красной линии (индексы 17-26, начиная с 6:10)
            if (i <= 16) {
                int redIndex = i + 10; // 17-26
                metroTrains.push_back(std::thread([redIndex]() {
                    // Красные поезда: 6:10, 6:30, 6:50...
                    train_time_offset[redIndex] = ((redIndex - 17) * 20) + 10;
                    
                    // Запуск движения на 5 кругов
                    Dvijeniye_krasniy(redIndex, 5);
                }));
                
                sleep_(15);
                std::cout << "Поезд #" << redIndex << " красной линии запущен" << std::endl;
            }
        }
        
        std::cout << "Все поезда запущены. Симуляция выполняется..." << std::endl;
        
        // Ожидание завершения всех потоков
        for (auto& train : metroTrains) {
            if (train.joinable()) {
                train.join();
            }
        }
        
        std::cout << "Симуляция метро Баку завершена успешно." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в симуляции: " << e.what() << std::endl;
        
        // В случае ошибки пытаемся корректно завершить все потоки
        for (auto& train : metroTrains) {
            if (train.joinable()) {
                train.join();
            }
        }
        
        return 1; // Возвращаем код ошибки
    }
    
    return 0;
}