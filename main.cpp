#include "metro.h"

int main() {
    std::vector<std::thread> Trains;
    
    std::cout << "Запуск симуляции метро Баку..." << std::endl;
    
    // Инициализация файлов для логов (16 поездов: 4 на фиолетовой, 6 на зеленой, 6 на красной)
    for (int i = 1; i <= 16; ++i) {
        std::ofstream file("train_" + std::to_string(i) + ".txt");
        if (file.is_open()) {
            file << "=== Инициализация файла логов для поезда " << i << " ===" << std::endl;
            file.close();
        } else {
            std::cerr << "Ошибка: не удалось создать файл логов для поезда " << i << std::endl;
        }
    }
    
    try {
        // Вместо отрицательного смещения времени используем положительные значения
        // и смещаем базовое время для всех поездов на +10 минут
        
        // Базовое время смещаем вперед на 10 минут (с 06:00 на 06:10)
        const int BASE_TIME_OFFSET = 10;
        
        // Для всех поездов добавляем смещение BASE_TIME_OFFSET
        
        // Запуск поездов фиолетовой линии (4 поезда: 1, 2, 3, 4)
        std::cout << "Запуск поездов фиолетовой линии..." << std::endl;
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[1] = BASE_TIME_OFFSET; // 06:10
            Dvijeniye_violete(1);
        }));
        sleep_(15);
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[2] = BASE_TIME_OFFSET; // 06:10
            Dvijeniye_violete(2);
        }));
        sleep_(15);
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[3] = BASE_TIME_OFFSET; // 06:10
            Dvijeniye_violete(3);
        }));
        sleep_(15);
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[4] = BASE_TIME_OFFSET; // 06:10
            Dvijeniye_violete(4);
        }));
        
        // Запуск поездов зеленой и красной линий с чередованием
        std::cout << "Запуск поездов зеленой и красной линий с чередованием..." << std::endl;
        
        // Зеленая линия (6 поездов: 5, 7, 9, 11, 13, 15)
        // Стартуют в: 06:00, 06:10, 06:20, 06:30, 06:40, 06:50 (с учетом смещения)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[5] = BASE_TIME_OFFSET + 0; // 06:10 (вместо 05:50)
            Dvijeniye_zeleniy(5);
        }));
        sleep_(15);
        
        // Красная линия (6 поездов: 6, 8, 10, 12, 14, 16)
        // Стартуют в: 06:05, 06:15, 06:25, 06:35, 06:45, 06:55 (с учетом смещения)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[6] = BASE_TIME_OFFSET + 5; // 06:15 (вместо 05:55)
            Dvijeniye_krasniy(6);
        }));
        sleep_(15);
        
        // Чередуем запуск остальных поездов
        
        // Зеленый 2 (06:10 → 06:20)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[7] = BASE_TIME_OFFSET + 10; // 06:20
            Dvijeniye_zeleniy(7);
        }));
        sleep_(15);
        
        // Красный 2 (06:15 → 06:25)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[8] = BASE_TIME_OFFSET + 15; // 06:25
            Dvijeniye_krasniy(8);
        }));
        sleep_(15);
        
        // Зеленый 3 (06:20 → 06:30)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[9] = BASE_TIME_OFFSET + 20; // 06:30
            Dvijeniye_zeleniy(9);
        }));
        sleep_(15);
        
        // Красный 3 (06:25 → 06:35)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[10] = BASE_TIME_OFFSET + 25; // 06:35
            Dvijeniye_krasniy(10);
        }));
        sleep_(15);
        
        // Зеленый 4 (06:30 → 06:40)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[11] = BASE_TIME_OFFSET + 30; // 06:40
            Dvijeniye_zeleniy(11);
        }));
        sleep_(15);
        
        // Красный 4 (06:35 → 06:45)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[12] = BASE_TIME_OFFSET + 35; // 06:45
            Dvijeniye_krasniy(12);
        }));
        sleep_(15);
        
        // Зеленый 5 (06:40 → 06:50)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[13] = BASE_TIME_OFFSET + 40; // 06:50
            Dvijeniye_zeleniy(13);
        }));
        sleep_(15);
        
        // Красный 5 (06:45 → 06:55)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[14] = BASE_TIME_OFFSET + 45; // 06:55
            Dvijeniye_krasniy(14);
        }));
        sleep_(15);
        
        // Зеленый 6 (06:50 → 07:00)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[15] = BASE_TIME_OFFSET + 50; // 07:00
            Dvijeniye_zeleniy(15);
        }));
        sleep_(15);
        
        // Красный 6 (06:55 → 07:05)
        Trains.push_back(std::thread([BASE_TIME_OFFSET](){
            train_time_offset[16] = BASE_TIME_OFFSET + 55; // 07:05
            Dvijeniye_krasniy(16);
        }));
        
        std::cout << "Все поезда запущены. Симуляция выполняется..." << std::endl;
        
        // Ожидание завершения всех потоков
        for (auto& train : Trains) {
            if (train.joinable()) {
                train.join();
            }
        }
        
        std::cout << "Симуляция завершена успешно." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в симуляции: " << e.what() << std::endl;
        
        // В случае ошибки пытаемся корректно завершить все потоки
        for (auto& train : Trains) {
            if (train.joinable()) {
                train.join();
            }
        }
        
        return 1; // Возвращаем код ошибки
    }
    
    return 0;
}