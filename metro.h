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
const int REAL_TRAVEL_TIME_MIN = 4; // Изменено с 6 на 4 минуты

// Глобальное смещение времени для каждого поезда
extern std::map<int, int> train_time_offset;

// Общий мьютекс для файловых операций
extern std::mutex files_mutex;

// Мьютексы для станций и перегонов
// Общие мьютексы для обеих линий
extern std::mutex May28_Interchange; // Мьютекс для пересадки на станции May28

// Мьютексы для перегонов общего участка
extern std::mutex May28_Genclik_Segment;
extern std::mutex Genclik_NarimanNarimanov_Segment;
extern std::mutex NarimanNarimanov_Bakmil_Segment;
extern std::mutex NarimanNarimanov_Ulduz_Segment;

// Мьютексы для перегонов на участке NarimanNarimanov - HeziAslanov
extern std::mutex Ulduz_Koroglu_Segment;
extern std::mutex Koroglu_QaraQarayev_Segment;
extern std::mutex QaraQarayev_Neftchiler_Segment;
extern std::mutex Neftchiler_XalqlarDostluqu_Segment;
extern std::mutex XalqlarDostluqu_Ahmedli_Segment;
extern std::mutex Ahmedli_HeziAslanov_Segment;

// Мьютексы для станций
extern std::mutex May28_Station;
extern std::mutex Genclik_Station;
extern std::mutex NarimanNarimanov_Station;
extern std::mutex Bakmil_Station;

// Мьютексы для красной линии
extern std::mutex IcheriSheherRight, IcheriSheherLeft;
extern std::mutex SahilRight, SahilLeft;
extern std::mutex May28Right, May28Left;

// Мьютексы для зеленой линии
extern std::mutex DernegulRight, DernegulLeft;
extern std::mutex AzadliqProspektiRight, AzadliqProspektiLeft;
extern std::mutex NasimiRight, NasimiLeft;
extern std::mutex MemarEcemiRight, MemarEcemiLeft;
extern std::mutex YanvarRight, YanvarLeft;
extern std::mutex InsaatcilarRight, InsaatcilarLeft;
extern std::mutex ElmlerAkademiyasiRight, ElmlerAkademiyasiLeft;
extern std::mutex NizamiGenceviRight, NizamiGenceviLeft;
extern std::mutex May28GreenRight, May28GreenLeft;

// Мьютексы для фиолетовой линии
extern std::mutex XodjasanRight, XodjasanLeft;
extern std::mutex AvtovogzalRight, AvtovogzalLeft;
extern std::mutex VioleteMemarAdjemiRight, VioleteMemarAdjemiLeft;

// Остальные общие мьютексы для остальных станций и перегонов
extern std::mutex UlduzRight, UlduzLeft;
extern std::mutex KorogluRight, KorogluLeft;
extern std::mutex QaraQarayevRight, QaraQarayevLeft;
extern std::mutex NeftchilerRight, NeftchilerLeft;
extern std::mutex XalqlarDostluquRight, XalqlarDostluquLeft;
extern std::mutex AhmedliRight, AhmedliLeft;
extern std::mutex HeziAslanovRight, HeziAslanovLeft;
extern std::mutex GenclikRight, GenclikLeft;
extern std::mutex NarimanNarimanovRight, NarimanNarimanovLeft;
extern std::mutex BakmilRight, BakmilLeft;

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

// Функции для красной и зеленой линий (из redGreenLines.cpp)
void RedLineStationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index);
void GreenLineStationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index);
void logRedLineAction(int index, const std::string& action);
void logGreenLineAction(int index, const std::string& action);

// Перегоны общего участка
void Bakmil_to_NarimanNarimanov(int index, bool isRed);
void NarimanNarimanov_to_Genclik(int index, bool isRed);
void Genclik_to_May28(int index, bool isRed);
void May28_to_Genclik(int index, bool isRed);
void Genclik_to_NarimanNarimanov(int index, bool isRed);
void NarimanNarimanov_to_Bakmil(int index, bool isRed);
void NarimanNarimanov_to_Ulduz(int index, bool isRed);

// Перегоны длинного маршрута
void Ulduz_to_Koroglu(int index, bool isRed);
void Koroglu_to_QaraQarayev(int index, bool isRed);
void QaraQarayev_to_Neftchiler(int index, bool isRed);
void Neftchiler_to_XalqlarDostluqu(int index, bool isRed);
void XalqlarDostluqu_to_Ahmedli(int index, bool isRed);
void Ahmedli_to_HeziAslanov(int index, bool isRed);

// Перегоны в обратном направлении
void HeziAslanov_to_Ahmedli(int index, bool isRed);
void Ahmedli_to_XalqlarDostluqu(int index, bool isRed);
void XalqlarDostluqu_to_Neftchiler(int index, bool isRed);
void Neftchiler_to_QaraQarayev(int index, bool isRed);
void QaraQarayev_to_Koroglu(int index, bool isRed);
void Koroglu_to_Ulduz(int index, bool isRed);
void Ulduz_to_NarimanNarimanov(int index, bool isRed);

// Перегоны уникальные для красной линии
void May28_to_Sahil(int index);
void Sahil_to_IcheriSheher(int index);
void IcheriSheher_to_Sahil(int index);
void Sahil_to_May28(int index);

// Функции для зеленой линии (уникальные участки)
void May28_to_NizamiGencevi(int index);
void NizamiGencevi_to_ElmlerAkademiyasi(int index);
void ElmlerAkademiyasi_to_Insaatcilar(int index);
void Insaatcilar_to_20Yanvar(int index);
void Yanvar20_to_MemarEcemi(int index);
void MemarEcemi_to_Nasimi(int index);
void Nasimi_to_AzadliqProspekti(int index);
void AzadliqProspekti_to_Dernegul(int index);
void Dernegul_to_AzadliqProspekti(int index);
void AzadliqProspekti_to_Nasimi(int index);
void Nasimi_to_MemarEcemi(int index);
void MemarEcemi_to_20Yanvar(int index);
void Yanvar20_to_Insaatcilar(int index);
void Insaatcilar_to_ElmlerAkademiyasi(int index);
void ElmlerAkademiyasi_to_NizamiGencevi(int index);
void NizamiGencevi_to_May28(int index);

// Функции для маршрутов
void RedLineInitialRoute(int index);
void RedLineLongRoute(int index);
void RedLineShortRoute(int index);
void RedLineReturnFromHeziAslanov(int index);
void RedLineReturnFromBakmil(int index);
void GreenLineInitialRoute(int index);
void GreenLineLongRoute(int index);
void GreenLineShortRoute(int index);
void GreenLineReturnFromHeziAslanov(int index);
void GreenLineReturnFromBakmil(int index);

// Основные функции движения поездов
void Dvijeniye_krasniy(int index);
void Dvijeniye_zeleniy(int index);

#endif // METRO_H