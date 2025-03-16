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
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setfill('0') << std::setw(2) << minutes;
    
    return ss.str();
}

void logToFile(int train_index, const std::string& message) {
    std::lock_guard<std::mutex> file_guard(files_mutex);
    std::ofstream file("train_" + std::to_string(train_index) + ".txt", std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
        file.close();
    }
}

void StationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index){
    std::unique_lock<std::mutex> lock(station_mutex);
    
    std::string start_time = getFormattedTime(index);
    
    train_time_offset[index] += REAL_TRAVEL_TIME_MIN;
    
    std::string arrival_time = getFormattedTime(index);
    
    std::string travel_message = from + " -> " + to + " " + start_time + " - " + arrival_time;
    logToFile(index, travel_message);
    
    sleep_(TRAVEL_TIME_MS);
    
    logToFile(index, "Поезд " + std::to_string(index) + " прибыл на станцию " + to);
    
    logToFile(index, "Поезд " + std::to_string(index) + " делает остановку на станции " + to);
    
    train_time_offset[index] += 1;
    
    std::string departure_time = getFormattedTime(index);
    logToFile(index, "Поезд " + std::to_string(index) + " отправляется со станции " + to + " в " + departure_time);
    
    sleep_(1);
}

void Xodjasan(int index) {
    StationAction("Xodjasan", "Avtovogzal", XodjasanRight, index);
}

void Avtovogzal(int index) {
    StationAction("Avtovogzal", "VioleteMemarAdjemi", AvtovogzalRight, index);
}

void VioleteMemarAdjemi(int index) {
    StationAction("VioleteMemarAdjemi", "8Noyabr", VioleteMemarAdjemiRight, index);
}

void Noyabr8(int index) {
    StationAction("8Noyabr", "VioleteMemarAdjemi", VioleteMemarAdjemiLeft, index);
}

void VioleteMemarAdjemi_(int index) {
    StationAction("VioleteMemarAdjemi", "Avtovogzal", AvtovogzalLeft, index);
}

void Avtovogzal_(int index) {
    StationAction("Avtovogzal", "Xodjasan", XodjasanLeft, index);
}

void logAction(int index, const std::string& action) {
    std::string time = getFormattedTime(index);
    logToFile(index, time + " - " + action);
    
    train_time_offset[index] += 2;
}

void Dvijeniye_violete(int index){
    train_time_offset[index] = (index-1) * 10;
    
    {
        std::ofstream file("train_" + std::to_string(index) + ".txt");
        file.close();
    }
    
    for(int i = 0; i < 5; ++i){
        logAction(index, "Поезд " + std::to_string(index) + " готовится к маршруту (круг " + std::to_string(i+1) + ")");
        
        sleep_(2);
        Xodjasan(index);
        sleep_(1);
        Avtovogzal(index);
        sleep_(1);
        VioleteMemarAdjemi(index);
        
        logAction(index, "Поезд " + std::to_string(index) + " делает разворот");
        
        sleep_(4);
        Noyabr8(index);
        sleep_(1);
        VioleteMemarAdjemi_(index);
        sleep_(1);
        Avtovogzal_(index);
        
        logAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i+1));
    }
}
