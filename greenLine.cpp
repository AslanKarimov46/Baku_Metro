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
    std::unique_lock<std::mutex> lock(station_mutex);
    
    std::string start_time = getFormattedTime(index);
    
    train_time_offset[index] += REAL_TRAVEL_TIME_MIN;
    
    std::string arrival_time = getFormattedTime(index);
    
    std::string travel_message = from + " -> " + to + " " + start_time + " - " + arrival_time;
    logToFile(index, travel_message);
    
    sleep_(TRAVEL_TIME_MS);
    
    logToFile(index, "Поезд " + std::to_string(index) + " прибыл на станцию " + to);
    
    logToFile(index, "Поезд " + std::to_string(index) + " делает остановку на станции " + to);
    
    train_time_offset[index] += 1; // 1 минута остановки
    
    std::string departure_time = getFormattedTime(index);
    logToFile(index, "Поезд " + std::to_string(index) + " отправляется со станции " + to + " в " + departure_time);
    
    sleep_(1);
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
    GreenLineStationAction("28May", "Genclik", May28GreenRight, index);
}

void GenclikGreen(int index) {
    GreenLineStationAction("Genclik", "NarimanNarimanov", GenclikGreenRight, index);
}

void NarimanNarimanovGreen(int index) {
    GreenLineStationAction("NarimanNarimanov", "Bakmil", NarimanNarimanovGreenRight, index);
}

void BakmilGreen(int index) {
    GreenLineStationAction("Bakmil", "Конечная", BakmilGreenRight, index);
}

// Функции для движения назад (в сторону Dernegul)
void May28Green_(int index) {
    GreenLineStationAction("28May", "NizamiGencevi", May28GreenLeft, index);
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
    GreenLineStationAction("Bakmil", "NarimanNarimanov", BakmilGreenLeft, index);
}

void NarimanNarimanovGreen_(int index) {
    GreenLineStationAction("NarimanNarimanov", "Genclik", NarimanNarimanovGreenLeft, index);
}

void GenclikGreen_(int index) {
    GreenLineStationAction("Genclik", "May28", GenclikGreenLeft, index);
}

void logGreenLineAction(int index, const std::string& action) {
    std::string time = getFormattedTime(index);
    logToFile(index, time + " - " + action);
    
    train_time_offset[index] += 2; // 2 минуты на действие
}

void Dvijeniye_zeleniy(int index) {
    train_time_offset[index] = (index - 7) * 10; 
    logGreenLineAction(index, "Поезд " + std::to_string(index) + " начинает движение от Bakmil");
    
    BakmilGreen_(index);
    sleep_(1);
    NarimanNarimanovGreen_(index);
    sleep_(1);
    GenclikGreen_(index);
    sleep_(1);
    May28Green_(index);
    sleep_(1);
    NizamiGencevi_(index);
    sleep_(1);
    ElmlerAkademiyasi_(index);
    sleep_(1);
    Insaatcilar_(index);
    sleep_(1);
    Yanvar20_(index);
    sleep_(1);
    MemarEcemi_(index);
    sleep_(1);
    Nasimi_(index);
    sleep_(1);
    AzadliqProspekti_(index);
    
    logGreenLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Dernegul и делает разворот");
    train_time_offset[index] += 5; 
    
    for(int i = 1; i <= 10; i++) { 
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " начинает круг " + std::to_string(i));
        
        if (i % 5 == 0) {
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " следует по короткому маршруту до Bakmil");
            
            Dernegul(index);
            sleep_(1);
            AzadliqProspekti(index);
            sleep_(1);
            Nasimi(index);
            sleep_(1);
            MemarEcemi(index);
            sleep_(1);
            Yanvar20(index);
            sleep_(1);
            Insaatcilar(index);
            sleep_(1);
            ElmlerAkademiyasi(index);
            sleep_(1);
            NizamiGencevi(index);
            sleep_(1);
            May28Green(index);
            sleep_(1);
            GenclikGreen(index);
            sleep_(1);
            NarimanNarimanovGreen(index);
            sleep_(1);
            BakmilGreen(index);
            
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Bakmil и делает разворот");
            train_time_offset[index] += 5; 
          
            BakmilGreen_(index);
            sleep_(1);
            NarimanNarimanovGreen_(index);
            sleep_(1);
            GenclikGreen_(index);
            sleep_(1);
            May28Green_(index);
            sleep_(1);
            NizamiGencevi_(index);
            sleep_(1);
            ElmlerAkademiyasi_(index);
            sleep_(1);
            Insaatcilar_(index);
            sleep_(1);
            Yanvar20_(index);
            sleep_(1);
            MemarEcemi_(index);
            sleep_(1);
            Nasimi_(index);
            sleep_(1);
            AzadliqProspekti_(index);
            
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " вернулся на станцию Dernegul");
        } else {
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " следует по полному маршруту до Bakmil");
            
            // Движение от Dernegul до Bakmil
            Dernegul(index);
            sleep_(1);
            AzadliqProspekti(index);
            sleep_(1);
            Nasimi(index);
            sleep_(1);
            MemarEcemi(index);
            sleep_(1);
            Yanvar20(index);
            sleep_(1);
            Insaatcilar(index);
            sleep_(1);
            ElmlerAkademiyasi(index);
            sleep_(1);
            NizamiGencevi(index);
            sleep_(1);
            May28Green(index);
            sleep_(1);
            GenclikGreen(index);
            sleep_(1);
            NarimanNarimanovGreen(index);
            sleep_(1);
            BakmilGreen(index);
            
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Bakmil и делает разворот");
            train_time_offset[index] += 5; 
            
            BakmilGreen_(index);
            sleep_(1);
            NarimanNarimanovGreen_(index);
            sleep_(1);
            GenclikGreen_(index);
            sleep_(1);
            May28Green_(index);
            sleep_(1);
            NizamiGencevi_(index);
            sleep_(1);
            ElmlerAkademiyasi_(index);
            sleep_(1);
            Insaatcilar_(index);
            sleep_(1);
            Yanvar20_(index);
            sleep_(1);
            MemarEcemi_(index);
            sleep_(1);
            Nasimi_(index);
            sleep_(1);
            AzadliqProspekti_(index);
            
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " вернулся на станцию Dernegul");
        }
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " делает длинную остановку на станции Dernegul");
        train_time_offset[index] += 5; 
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i));
    }
}
