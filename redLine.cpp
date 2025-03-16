#include "metro.h"

// Мьютексы для красной линии
std::mutex IcheriSheherRight, IcheriSheherLeft;
std::mutex SahilRight, SahilLeft;
std::mutex May28Right, May28Left;
std::mutex GenclikRight, GenclikLeft;
std::mutex NarimanNarimanovRight, NarimanNarimanovLeft;
std::mutex BakmilRight, BakmilLeft;
std::mutex UlduzRight, UlduzLeft;
std::mutex KorogluRight, KorogluLeft;
std::mutex QaraQarayevRight, QaraQarayevLeft;
std::mutex NeftchilerRight, NeftchilerLeft;
std::mutex XalqlarDostluquRight, XalqlarDostluquLeft;
std::mutex AhmedliRight, AhmedliLeft;

// Объявляем общие мьютексы для пересадочных узлов
std::mutex May28_Interchange;

// Функция для действий на станции красной линии
void RedLineStationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index){
    std::unique_lock<std::mutex> lock(station_mutex);
    
    std::string start_time = getFormattedTime(index);
    
    // Увеличиваем смещение времени для поезда (поездка между станциями)
    train_time_offset[index] += REAL_TRAVEL_TIME_MIN;
    
    std::string arrival_time = getFormattedTime(index);
    
    std::string travel_message = from + " -> " + to + " " + start_time + " - " + arrival_time;
    logToFile(index, travel_message);
    
    // Симулируем время в пути
    sleep_(TRAVEL_TIME_MS);
    
    logToFile(index, "Поезд " + std::to_string(index) + " прибыл на станцию " + to);
    
    // Остановка на станции на 1 минуту
    logToFile(index, "Поезд " + std::to_string(index) + " делает остановку на станции " + to);
    
    // Увеличиваем смещение времени для остановки на станции
    train_time_offset[index] += 1; // 1 минута остановки
    
    std::string departure_time = getFormattedTime(index);
    logToFile(index, "Поезд " + std::to_string(index) + " отправляется со станции " + to + " в " + departure_time);
    
    // Симулируем время остановки
    sleep_(1); // 1 миллисекунда в симуляции для остановки
}

// Функции для движения вперед (в сторону HeziAslanov)
void IcheriSheher(int index) {
    RedLineStationAction("IcheriSheher", "Sahil", IcheriSheherRight, index);
}

void Sahil(int index) {
    RedLineStationAction("Sahil", "May28", SahilRight, index);
}

void May28(int index) {
    // При входе на пересадочную станцию блокируем общий мьютекс
    std::lock_guard<std::mutex> interchange_lock(May28_Interchange);
    
    RedLineStationAction("May28", "Genclik", May28Right, index);
}

void Genclik(int index) {
    // Блокируем мьютекс для общего участка с зеленой линией
    std::lock_guard<std::mutex> interchange_lock(red_green_interchange_mutex);
    
    RedLineStationAction("Genclik", "NarimanNarimanov", GenclikRight, index);
}

void NarimanNarimanov(int index) {
    // Блокируем мьютекс для общего участка с зеленой линией
    std::lock_guard<std::mutex> interchange_lock(red_green_interchange_mutex);
    
    RedLineStationAction("NarimanNarimanov", "Bakmil", NarimanNarimanovRight, index);
}

void Bakmil(int index) {
    // Блокируем мьютекс для общего участка с зеленой линией
    std::lock_guard<std::mutex> interchange_lock(red_green_interchange_mutex);
    
    RedLineStationAction("Bakmil", "Ulduz", BakmilRight, index);
}

void Ulduz(int index) {
    RedLineStationAction("Ulduz", "Koroglu", UlduzRight, index);
}

void Koroglu(int index) {
    RedLineStationAction("Koroglu", "QaraQarayev", KorogluRight, index);
}

void QaraQarayev(int index) {
    RedLineStationAction("QaraQarayev", "Neftchiler", QaraQarayevRight, index);
}

void Neftchiler(int index) {
    RedLineStationAction("Neftchiler", "XalqlarDostluqu", NeftchilerRight, index);
}

void XalqlarDostluqu(int index) {
    RedLineStationAction("XalqlarDostluqu", "Ahmedli", XalqlarDostluquRight, index);
}

void Ahmedli(int index) {
    RedLineStationAction("Ahmedli", "HeziAslanov", AhmedliRight, index);
}

// Функции для движения назад (в сторону IcheriSheher)
void HeziAslanov_(int index) {
    RedLineStationAction("HeziAslanov", "Ahmedli", AhmedliLeft, index);
}

void Ahmedli_(int index) {
    RedLineStationAction("Ahmedli", "XalqlarDostluqu", XalqlarDostluquLeft, index);
}

void XalqlarDostluqu_(int index) {
    RedLineStationAction("XalqlarDostluqu", "Neftchiler", NeftchilerLeft, index);
}

void Neftchiler_(int index) {
    RedLineStationAction("Neftchiler", "QaraQarayev", QaraQarayevLeft, index);
}

void QaraQarayev_(int index) {
    RedLineStationAction("QaraQarayev", "Koroglu", QaraQarayevLeft, index);
}

void Koroglu_(int index) {
    RedLineStationAction("Koroglu", "Ulduz", KorogluLeft, index);
}

void Ulduz_(int index) {
    RedLineStationAction("Ulduz", "NarimanNarimanov", UlduzLeft, index);
}

void Bakmil_(int index) {
    // Блокируем мьютекс для общего участка с зеленой линией
    std::lock_guard<std::mutex> interchange_lock(red_green_interchange_mutex);
    
    RedLineStationAction("Bakmil", "NarimanNarimanov", NarimanNarimanovLeft, index);
}

void NarimanNarimanov_(int index) {
    // Блокируем мьютекс для общего участка с зеленой линией
    std::lock_guard<std::mutex> interchange_lock(red_green_interchange_mutex);
    
    RedLineStationAction("NarimanNarimanov", "Genclik", GenclikLeft, index);
}

void Genclik_(int index) {
    // Блокируем мьютекс для общего участка с зеленой линией
    std::lock_guard<std::mutex> interchange_lock(red_green_interchange_mutex);
    
    RedLineStationAction("Genclik", "May28", May28Left, index);
}

void May28_(int index) {
    // При входе на пересадочную станцию блокируем общий мьютекс
    std::lock_guard<std::mutex> interchange_lock(May28_Interchange);
    
    RedLineStationAction("May28", "Sahil", SahilLeft, index);
}

void Sahil_(int index) {
    RedLineStationAction("Sahil", "IcheriSheher", IcheriSheherLeft, index);
}

// Логирование действий для красной линии
void logRedLineAction(int index, const std::string& action) {
    std::string time = getFormattedTime(index);
    logToFile(index, time + " - " + action);
    
    // Добавляем небольшое смещение для "непоездных" действий
    train_time_offset[index] += 2; // 2 минуты на действие
}

void Dvijeniye_krasniy(int index) {
    // Инициализация времени для этого поезда
    train_time_offset[index] = (index - 4) * 10; // Поезд 4 начнет первым, потом 5, потом 6
    
    // Начальное положение - поезд находится на полпути к IcheriSheher
    logRedLineAction(index, "Поезд " + std::to_string(index) + " начинает движение от Bakmil в сторону IcheriSheher");
    
    Bakmil_(index);
    sleep_(1);
    NarimanNarimanov_(index);
    sleep_(1);
    Genclik_(index);
    sleep_(1);
    May28_(index);
    sleep_(1);
    Sahil_(index);
    sleep_(1);
    
    for(int i = 1; i <= 10; i++) { // Ограничим до 10 кругов вместо бесконечного цикла
        logRedLineAction(index, "Поезд " + std::to_string(index) + " начинает круг " + std::to_string(i));
        
        IcheriSheher(index);
        sleep_(1);
        Sahil(index);
        
        if(i % 5 == 0) {
            // Раз в 5 поездок заворачиваем на Bakmil
            logRedLineAction(index, "Поезд " + std::to_string(index) + " следует по короткому маршруту до Bakmil");
            
            IcheriSheher(index);
            sleep_(1);
            Sahil(index);
            sleep_(1);
            May28(index);
            sleep_(1);
            Genclik(index);
            sleep_(1);
            NarimanNarimanov(index);
            sleep_(1);
            Bakmil(index);
            sleep_(1);
            
            // Конечная, делаем разворот
            logRedLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Bakmil и делает разворот");
            train_time_offset[index] += 5; // Пять минут на разворот
            
            Bakmil_(index);
            sleep_(1);
            NarimanNarimanov_(index);
            sleep_(1);
            Genclik_(index);
            sleep_(1);
            May28_(index);
            sleep_(1);
            Sahil_(index);
            
            logRedLineAction(index, "Поезд " + std::to_string(index) + " завершил короткий маршрут и вернулся к IcheriSheher");
        } else {
            // Обычный маршрут до HeziAslanov
            logRedLineAction(index, "Поезд " + std::to_string(index) + " следует по полному маршруту до HeziAslanov");
            
            IcheriSheher(index);
            sleep_(1);
            Sahil(index);
            sleep_(1);
            May28(index);
            sleep_(1);
            Genclik(index);
            sleep_(1);
            NarimanNarimanov(index);
            sleep_(1);
            Ulduz(index);
            sleep_(1);
            Koroglu(index);
            sleep_(1);
            QaraQarayev(index);
            sleep_(1);
            Neftchiler(index);
            sleep_(1);
            XalqlarDostluqu(index);
            sleep_(1);
            Ahmedli(index);
            
            // Прибыли на конечную станцию
            logRedLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную HeziAslanov и делает разворот");
            train_time_offset[index] += 5; // Пять минут на разворот
            
            HeziAslanov_(index);
            sleep_(1);
            Ahmedli_(index);
            sleep_(1);
            XalqlarDostluqu_(index);
            sleep_(1);
            Neftchiler_(index);
            sleep_(1);
            QaraQarayev_(index);
            sleep_(1);
            Koroglu_(index);
            sleep_(1);
            Ulduz_(index);
            sleep_(1);
            NarimanNarimanov_(index);
            sleep_(1);
            Genclik_(index);
            sleep_(1);
            May28_(index);
            sleep_(1);
            Sahil_(index);
            sleep_(1);
            
            logRedLineAction(index, "Поезд " + std::to_string(index) + " завершил полный маршрут и вернулся к IcheriSheher");
        }
        
        logRedLineAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i));
    }
}
