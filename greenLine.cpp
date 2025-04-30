#include "metro.h"

std::mutex red_green_interchange_mutex;

std::mutex DernegulRight, DernegulLeft;
std::mutex AzadliqProspektiRight, AzadliqProspektiLeft;
std::mutex NasimiRight, NasimiLeft;
std::mutex MemarEcemiRight, MemarEcemiLeft;
std::mutex YanvarRight, YanvarLeft;
std::mutex InsaatcilarRight, InsaatcilarLeft;
std::mutex ElmlerAkademiyasiRight, ElmlerAkademiyasiLeft;
std::mutex NizamiGenceviRight, NizamiGenceviLeft;
std::mutex May28GreenRight, May28GreenLeft;
std::mutex GenclikGreenRight, GenclikGreenLeft;
std::mutex NarimanNarimanovGreenRight, NarimanNarimanovGreenLeft;
std::mutex BakmilGreenRight, BakmilGreenLeft;

void GreenLineStationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index){
    try {
        std::unique_lock<std::mutex> lock(station_mutex);
        
        std::string start_time = getFormattedTime(index);
        
        train_time_offset[index] += REAL_TRAVEL_TIME_MIN;
        
        std::string arrival_time = getFormattedTime(index);
        
        std::string travel_message = from + " -> " + to + " " + start_time + " - " + arrival_time;
        logToFile(index, travel_message);
        
        // Увеличено для лучшей наблюдаемости
        sleep_(TRAVEL_TIME_MS * 5);
        
        logToFile(index, "Поезд " + std::to_string(index) + " прибыл на станцию " + to);
        
        logToFile(index, "Поезд " + std::to_string(index) + " делает остановку на станции " + to);
        
        train_time_offset[index] += 1; // 1 минута остановки
        
        std::string departure_time = getFormattedTime(index);
        logToFile(index, "Поезд " + std::to_string(index) + " отправляется со станции " + to + " в " + departure_time);
        
        // Увеличено для лучшей наблюдаемости
        sleep_(5);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при обработке станции " << to << ": " << e.what() << std::endl;
    }
}

void Dernegul(int index) {
    GreenLineStationAction("Dernegul", "AzadliqProspekti", DernegulRight, index);
}

void AzadliqProspekti(int index) {
    GreenLineStationAction("AzadliqProspekti", "Nasimi", AzadliqProspektiRight, index);
}

void Nasimi(int index) {
    GreenLineStationAction("Nasimi", "MemarEcemi", NasimiRight, index);
}

void MemarEcemi(int index) {
    GreenLineStationAction("MemarEcemi", "20Yanvar", MemarEcemiRight, index);
}

void Yanvar20(int index) {
    GreenLineStationAction("20Yanvar", "Insaatcilar", YanvarRight, index);
}

void Insaatcilar(int index) {
    GreenLineStationAction("Insaatcilar", "ElmlerAkademiyasi", InsaatcilarRight, index);
}

void ElmlerAkademiyasi(int index) {
    GreenLineStationAction("ElmlerAkademiyasi", "NizamiGencevi", ElmlerAkademiyasiRight, index);
}

void NizamiGencevi(int index) {
    GreenLineStationAction("NizamiGencevi", "28May", NizamiGenceviRight, index);
}

void May28Green(int index) {
    try {
        // При входе на пересадочную станцию блокируем общий мьютекс
        std::unique_lock<std::mutex> interchange_lock(May28_Interchange);
        
        GreenLineStationAction("28May", "Genclik", May28GreenRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на станции 28May (зеленая линия): " << e.what() << std::endl;
    }
}

void GenclikGreen(int index) {
    try {
        // Блокируем мьютекс для общего участка с красной линией
        std::unique_lock<std::mutex> interchange_lock(red_green_interchange_mutex);
        
        GreenLineStationAction("Genclik", "NarimanNarimanov", GenclikGreenRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на станции Genclik (зеленая линия): " << e.what() << std::endl;
    }
}

void NarimanNarimanovGreen(int index) {
    try {
        // Блокируем мьютекс для общего участка с красной линией
        std::unique_lock<std::mutex> interchange_lock(red_green_interchange_mutex);
        
        GreenLineStationAction("NarimanNarimanov", "Bakmil", NarimanNarimanovGreenRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на станции NarimanNarimanov (зеленая линия): " << e.what() << std::endl;
    }
}

void BakmilGreen(int index) {
    try {
        // Блокируем мьютекс для общего участка с красной линией
        std::unique_lock<std::mutex> interchange_lock(red_green_interchange_mutex);
        
        GreenLineStationAction("Bakmil", "Конечная", BakmilGreenRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на станции Bakmil (зеленая линия): " << e.what() << std::endl;
    }
}

// Функции для движения назад (в сторону Dernegul)
void May28Green_(int index) {
    try {
        // При входе на пересадочную станцию блокируем общий мьютекс
        std::unique_lock<std::mutex> interchange_lock(May28_Interchange);
        
        GreenLineStationAction("28May", "NizamiGencevi", May28GreenLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на станции 28May (зеленая линия): " << e.what() << std::endl;
    }
}

void NizamiGencevi_(int index) {
    GreenLineStationAction("NizamiGencevi", "ElmlerAkademiyasi", NizamiGenceviLeft, index);
}

void ElmlerAkademiyasi_(int index) {
    GreenLineStationAction("ElmlerAkademiyasi", "Insaatcilar", ElmlerAkademiyasiLeft, index);
}

void Insaatcilar_(int index) {
    GreenLineStationAction("Insaatcilar", "20Yanvar", InsaatcilarLeft, index);
}

void Yanvar20_(int index) {
    GreenLineStationAction("20Yanvar", "MemarEcemi", YanvarLeft, index);
}

void MemarEcemi_(int index) {
    GreenLineStationAction("MemarEcemi", "Nasimi", MemarEcemiLeft, index);
}

void Nasimi_(int index) {
    GreenLineStationAction("Nasimi", "AzadliqProspekti", NasimiLeft, index);
}

void AzadliqProspekti_(int index) {
    GreenLineStationAction("AzadliqProspekti", "Dernegul", AzadliqProspektiLeft, index);
}

void BakmilGreen_(int index) {
    try {
        // Блокируем мьютекс для общего участка с красной линией
        std::unique_lock<std::mutex> interchange_lock(red_green_interchange_mutex);
        
        GreenLineStationAction("Bakmil", "NarimanNarimanov", BakmilGreenLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на станции Bakmil (зеленая линия): " << e.what() << std::endl;
    }
}

void NarimanNarimanovGreen_(int index) {
    try {
        // Блокируем мьютекс для общего участка с красной линией
        std::unique_lock<std::mutex> interchange_lock(red_green_interchange_mutex);
        
        GreenLineStationAction("NarimanNarimanov", "Genclik", NarimanNarimanovGreenLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на станции NarimanNarimanov (зеленая линия): " << e.what() << std::endl;
    }
}

void GenclikGreen_(int index) {
    try {
        // Блокируем мьютекс для общего участка с красной линией
        std::unique_lock<std::mutex> interchange_lock(red_green_interchange_mutex);
        
        GreenLineStationAction("Genclik", "May28", GenclikGreenLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на станции Genclik (зеленая линия): " << e.what() << std::endl;
    }
}

void logGreenLineAction(int index, const std::string& action) {
    try {
        std::string time = getFormattedTime(index);
        logToFile(index, time + " - " + action);
        
        train_time_offset[index] += 2; // 2 минуты на действие
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при логировании действия зеленой линии: " << e.what() << std::endl;
    }
}

void Dvijeniye_zeleniy(int index) {
    try {
        train_time_offset[index] = (index - 7) * 10;
        
        // Инициализация файла логов
        {
            std::lock_guard<std::mutex> file_guard(files_mutex);
            std::ofstream file("train_" + std::to_string(index) + ".txt");
            if (file.is_open()) {
                file << "=== Лог поезда " << index << " (Зеленая линия) ===" << std::endl;
                file.close();
            } else {
                std::cerr << "Ошибка: не удалось создать файл для поезда " << index << std::endl;
                return;
            }
        }
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " начинает движение от Bakmil");
        
        BakmilGreen_(index);
        sleep_(5);
        NarimanNarimanovGreen_(index);
        sleep_(5);
        GenclikGreen_(index);
        sleep_(5);
        May28Green_(index);
        sleep_(5);
        NizamiGencevi_(index);
        sleep_(5);
        ElmlerAkademiyasi_(index);
        sleep_(5);
        Insaatcilar_(index);
        sleep_(5);
        Yanvar20_(index);
        sleep_(5);
        MemarEcemi_(index);
        sleep_(5);
        Nasimi_(index);
        sleep_(5);
        AzadliqProspekti_(index);
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Dernegul и делает разворот");
        train_time_offset[index] += 5; 
        
        for(int i = 1; i <= 5; i++) { // Уменьшаем количество кругов для более быстрого теста
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " начинает круг " + std::to_string(i));
            
            if (i % 5 == 0) {
                logGreenLineAction(index, "Поезд " + std::to_string(index) + " следует по короткому маршруту до Bakmil");
                
                Dernegul(index);
                sleep_(5);
                AzadliqProspekti(index);
                sleep_(5);
                Nasimi(index);
                sleep_(5);
                MemarEcemi(index);
                sleep_(5);
                Yanvar20(index);
                sleep_(5);
                Insaatcilar(index);
                sleep_(5);
                ElmlerAkademiyasi(index);
                sleep_(5);
                NizamiGencevi(index);
                sleep_(5);
                May28Green(index);
                sleep_(5);
                GenclikGreen(index);
                sleep_(5);
                NarimanNarimanovGreen(index);
                sleep_(5);
                BakmilGreen(index);
                
                logGreenLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Bakmil и делает разворот");
                train_time_offset[index] += 5; 
              
                BakmilGreen_(index);
                sleep_(5);
                NarimanNarimanovGreen_(index);
                sleep_(5);
                GenclikGreen_(index);
                sleep_(5);
                May28Green_(index);
                sleep_(5);
                NizamiGencevi_(index);
                sleep_(5);
                ElmlerAkademiyasi_(index);
                sleep_(5);
                Insaatcilar_(index);
                sleep_(5);
                Yanvar20_(index);
                sleep_(5);
                MemarEcemi_(index);
                sleep_(5);
                Nasimi_(index);
                sleep_(5);
                AzadliqProspekti_(index);
                
                logGreenLineAction(index, "Поезд " + std::to_string(index) + " вернулся на станцию Dernegul");
            } else {
                logGreenLineAction(index, "Поезд " + std::to_string(index) + " следует по полному маршруту до Bakmil");
                
                // Движение от Dernegul до Bakmil
                Dernegul(index);
                sleep_(100);
                AzadliqProspekti(index);
                sleep_(100);
                Nasimi(index);
                sleep_(100);
                MemarEcemi(index);
                sleep_(100);
                Yanvar20(index);
                sleep_(100);
                Insaatcilar(index);
                sleep_(100);
                ElmlerAkademiyasi(index);
                sleep_(100);
                NizamiGencevi(index);
                sleep_(100);
                May28Green(index);
                sleep_(100);
                GenclikGreen(index);
                sleep_(100);
                NarimanNarimanovGreen(index);
                sleep_(100);
                BakmilGreen(index);
                
                logGreenLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Bakmil и делает разворот");
                train_time_offset[index] += 5; 
                
                BakmilGreen_(index);
                sleep_(100);
                NarimanNarimanovGreen_(index);
                sleep_(100);
                GenclikGreen_(index);
                sleep_(100);
                May28Green_(index);
                sleep_(100);
                NizamiGencevi_(index);
                sleep_(100);
                ElmlerAkademiyasi_(index);
                sleep_(100);
                Insaatcilar_(index);
                sleep_(100);
                Yanvar20_(index);
                sleep_(100);
                MemarEcemi_(index);
                sleep_(100);
                Nasimi_(index);
                sleep_(100);
                AzadliqProspekti_(index);
                
                logGreenLineAction(index, "Поезд " + std::to_string(index) + " вернулся на станцию Dernegul");
            }
            
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " делает длинную остановку на станции Dernegul");
            train_time_offset[index] += 5; 
            
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i));
        }
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " завершил маршрут зеленой линии");
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в маршруте поезда " << index << ": " << e.what() << std::endl;
    }
}