#ifndef METRO_H
#define METRO_H

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <map>

const int TRAVEL_TIME_MS = 3;
const int REAL_TRAVEL_TIME_MIN = 6;

// Глобальное смещение времени для каждого поезда
extern std::map<int, int> train_time_offset;

// Общий мьютекс для файловых операций
extern std::mutex files_mutex;

// Общие мьютексы для пересадочных станций
extern std::mutex May28_Interchange; // Пересадочный узел на станции 28 May между красной и зеленой линиями
extern std::mutex red_green_interchange_mutex; // Мьютекс для общих участков красной и зеленой линий

// Объявления глобальных мьютексов для фиолетовой линии
extern std::mutex XodjasanRight, XodjasanLeft;
extern std::mutex AvtovogzalRight, AvtovogzalLeft;
extern std::mutex VioleteMemarAdjemiRight, VioleteMemarAdjemiLeft;

// Объявления глобальных мьютексов для красной линии
extern std::mutex IcheriSheherRight, IcheriSheherLeft;
extern std::mutex SahilRight, SahilLeft;
extern std::mutex May28Right, May28Left;
extern std::mutex GenclikRight, GenclikLeft;
extern std::mutex NarimanNarimanovRight, NarimanNarimanovLeft;
extern std::mutex BakmilRight, BakmilLeft;
extern std::mutex UlduzRight, UlduzLeft;
extern std::mutex KorogluRight, KorogluLeft;
extern std::mutex QaraQarayevRight, QaraQarayevLeft;
extern std::mutex NeftchilerRight, NeftchilerLeft;
extern std::mutex XalqlarDostluquRight, XalqlarDostluquLeft;
extern std::mutex AhmedliRight, AhmedliLeft;

// Объявления глобальных мьютексов для зеленой линии
extern std::mutex DernegulRight, DernegulLeft;
extern std::mutex AzadliqProspektiRight, AzadliqProspektiLeft;
extern std::mutex NasimiRight, NasimiLeft;
extern std::mutex MemarEcemiRight, MemarEcemiLeft;
extern std::mutex YanvarRight, YanvarLeft;
extern std::mutex InsaatcilarRight, InsaatcilarLeft;
extern std::mutex ElmlerAkademiyasiRight, ElmlerAkademiyasiLeft;
extern std::mutex NizamiGenceviRight, NizamiGenceviLeft;

// Общие функции
void sleep_(int milliseconds);
std::string getFormattedTime(int train_index, int additional_minutes = 0);
void logToFile(int train_index, const std::string& message);

// Функции для фиолетовой линии
void StationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index);
void Xodjasan(int index);
void Avtovogzal(int index);
void VioleteMemarAdjemi(int index);
void Noyabr8(int index);
void VioleteMemarAdjemi_(int index);
void Avtovogzal_(int index);
void logAction(int index, const std::string& action);
void Dvijeniye_violete(int index);

// Функции для красной линии
void RedLineStationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index);
void IcheriSheher(int index);
void Sahil(int index);
void May28(int index);
void Genclik(int index);
void NarimanNarimanov(int index);
void Bakmil(int index);
void Ulduz(int index);
void Koroglu(int index);
void QaraQarayev(int index);
void Neftchiler(int index);
void XalqlarDostluqu(int index);
void Ahmedli(int index);
void HeziAslanov_(int index);
void Ahmedli_(int index);
void XalqlarDostluqu_(int index);
void Neftchiler_(int index);
void QaraQarayev_(int index);
void Koroglu_(int index);
void Ulduz_(int index);
void Bakmil_(int index);
void NarimanNarimanov_(int index);
void Genclik_(int index);
void May28_(int index);
void Sahil_(int index);
void logRedLineAction(int index, const std::string& action);
void Dvijeniye_krasniy(int index);

// Функции для зеленой линии
void GreenLineStationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index);
void Dernegul(int index);
void AzadliqProspekti(int index);
void Nasimi(int index);
void MemarEcemi(int index);
void Yanvar20(int index);
void Insaatcilar(int index);
void ElmlerAkademiyasi(int index);
void NizamiGencevi(int index);
void May28Green(int index);
void GenclikGreen(int index);
void NarimanNarimanovGreen(int index);
void BakmilGreen(int index);
void May28Green_(int index);
void NizamiGencevi_(int index);
void ElmlerAkademiyasi_(int index);
void Insaatcilar_(int index);
void Yanvar20_(int index);
void MemarEcemi_(int index);
void Nasimi_(int index);
void AzadliqProspekti_(int index);
void BakmilGreen_(int index);
void NarimanNarimanovGreen_(int index);
void GenclikGreen_(int index);
void logGreenLineAction(int index, const std::string& action);
void Dvijeniye_zeleniy(int index);

#endif // METRO_H
