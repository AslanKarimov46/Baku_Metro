#include "metro.h"

std::mutex XodjasanRight, XodjasanLeft;
std::mutex AvtovogzalRight, AvtovogzalLeft;
std::mutex VioleteMemarAdjemiRight, VioleteMemarAdjemiLeft;
std::mutex files_mutex;

std::map<int, int> train_time_offset;

void sleep_(int milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

std::string getFormattedTime(int train_index, int additional_minutes) {
    int base_hour = 6;
    int base_minute = 0;
    
    int total_minutes = train_time_offset[train_index] + additional_minutes;
    
    int hours = base_hour + (total_minutes / 60);
    int minutes = base_minute + (total_minutes % 60);
    
    if (minutes >= 60) {
        hours += 1;
        minutes -= 60;
    }
    
    if (hours >= 24)
        hours %= 24;
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setfill('0') << std::setw(2) << minutes;
    
    return ss.str();
}

void logToFile(int train_index, const std::string& message) {
    try {
        std::lock_guard<std::mutex> file_guard(files_mutex);
        std::ofstream file("train_" + std::to_string(train_index) + ".txt", std::ios::app);
        if (file.is_open()) {
            file << message << std::endl;
            file.close();
        } else {
            std::cerr << "Ошибка: не удалось открыть файл для поезда " << train_index << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при записи в файл: " << e.what() << std::endl;
    }
}

void StationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index) {
    try {
        std::unique_lock<std::mutex> lock(station_mutex);
        
        std::string start_time = getFormattedTime(index);
        
        train_time_offset[index] += REAL_TRAVEL_TIME_MIN;
        
        std::string arrival_time = getFormattedTime(index);
        
        std::string fromPadded = from;
        std::string toPadded = to;
        
        const int maxStationLength = 25;
        fromPadded.resize(maxStationLength, ' ');
        toPadded.resize(maxStationLength, ' ');
        
        std::stringstream ss;
        ss << fromPadded << "->   " << toPadded << "[ " << start_time << " - " << arrival_time << " ]";
        
        logToFile(index, ss.str());
        
        sleep_(TRAVEL_TIME_MS * 5);
        
        train_time_offset[index] += 1;
        
        sleep_(5);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при обработке перегона " << from << " -> " << to << ": " << e.what() << std::endl;
    }
}

void fromXodjasan(int index) {
    StationAction("Xodjasan", "Avtovogzal", XodjasanRight, index);
}

void fromAvtovogzal(int index) {
    StationAction("Avtovogzal", "VioleteMemarAdjemi", AvtovogzalRight, index);
}

void fromVioleteMemarAdjemi(int index) {
    StationAction("VioleteMemarAdjemi", "8Noyabr", VioleteMemarAdjemiRight, index);
}

void toVioleteMemarAdjemi(int index) {
    StationAction("8Noyabr", "VioleteMemarAdjemi", VioleteMemarAdjemiLeft, index);
}

void toAvtovogzal(int index) {
    StationAction("VioleteMemarAdjemi", "Avtovogzal", AvtovogzalLeft, index);
}

void toXodjasan(int index) {
    StationAction("Avtovogzal", "Xodjasan", XodjasanLeft, index);
}

void logAction(int index, const std::string& action) {
    try {
        std::string time = getFormattedTime(index);
        logToFile(index, time + " - " + action);
        
        train_time_offset[index] += 2;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при логировании действия: " << e.what() << std::endl;
    }
}

void Dvijeniye_violete(int index){
    try {
        train_time_offset[index] = (index-1) * 10;
        
        {
            std::lock_guard<std::mutex> file_guard(files_mutex);
            std::ofstream file("train_" + std::to_string(index) + ".txt");
            if (file.is_open()) {
                file << "=== Лог поезда " << index << " (Фиолетовая линия) ===" << std::endl;
                file.close();
            } else {
                std::cerr << "Ошибка: не удалось создать файл для поезда " << index << std::endl;
                return;
            }
        }
        
        for(int i = 0; i < 5; ++i){
            logAction(index, "Поезд " + std::to_string(index) + " готовится к маршруту (круг " + std::to_string(i+1) + ")");
            
            sleep_(10);
            fromXodjasan(index);
            sleep_(5);
            fromAvtovogzal(index);
            sleep_(5);
            fromVioleteMemarAdjemi(index);
            
            logAction(index, "Поезд " + std::to_string(index) + " делает разворот");
            
            sleep_(15);
            toVioleteMemarAdjemi(index);
            sleep_(5);
            toAvtovogzal(index);
            sleep_(5);
            toXodjasan(index);
            
            logAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i+1));
        }
        
        logAction(index, "Поезд " + std::to_string(index) + " завершил маршрут фиолетовой линии");
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в маршруте поезда " << index << ": " << e.what() << std::endl;
    }
}