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
const int REAL_TRAVEL_TIME_MIN = 4;

extern std::map<int, int> train_time_offset;

extern std::mutex files_mutex;

void sleep_(int milliseconds);
std::string getFormattedTime(int train_index, int additional_minutes = 0);
void logToFile(int train_index, const std::string& message);



extern std::mutex Xodjasan_Avtovogzal, Avtovogzal_Xodjasan;
extern std::mutex Avtovogzal_VioleteMemarAdjemi, VioleteMemarAdjemi_Avtovogzal;
extern std::mutex VioleteMemarAdjemi_Noyabr8, Noyabr8_VioleteMemarAdjemi;

void StationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index);
void fromXodjasan(int index);
void fromAvtovogzal(int index);
void fromVioleteMemarAdjemi(int index);
void toVioleteMemarAdjemi(int index);
void toAvtovogzal(int index);
void toXodjasan(int index);
void logAction(int index, const std::string& action);

void Dvijeniye_violete(int index, int amountOfCircles);








extern std::mutex Dernegul_AzadliqProspekti, AzadliqProspekti_Dernegul;
extern std::mutex AzadliqProspekti_Nasimi, Nasimi_AzadliqProspekti;
extern std::mutex Nasimi_MemarEcemi, MemarEcemi_Nasimi;
extern std::mutex MemarEcemi_Yanvar, Yanvar_MemarEcemi;
extern std::mutex Yanvar_Insaatcilar, Insaatcilar_Yanvar;
extern std::mutex Insaatcilar_ElmlerAkademiyasi, ElmlerAkademiyasi_Insaatcilar;
extern std::mutex ElmlerAkademiyasi_NizamiGencevi, NizamiGencevi_ElmlerAkademiyasi;
extern std::mutex NizamiGencevi_May28, May28_NizamiGencevi;

extern std::mutex IcheriSheher_Sahil, Sahil_IcheriSheher;
extern std::mutex Sahil_May28, May28_Sahil;


extern std::mutex May28_Genclik, Genclik_May28;
extern std::mutex Genclik_NarimanNarimanov, NarimanNarimanov_Genclik;
extern std::mutex NarimanNarimanov_Bakmil, Bakmil_NarimanNarimanov;

extern std::mutex NarimanNarimanov_Ulduz, Ulduz_NarimanNarimanov;
extern std::mutex Ulduz_Koroglu, Koroglu_Ulduz;
extern std::mutex Koroglu_QaraQarayev, QaraQarayev_Koroglu;
extern std::mutex QaraQarayev_Neftchiler, Neftchiler_QaraQarayev;
extern std::mutex Neftchiler_XalqlarDostluqu, XalqlarDostluqu_Neftchiler;
extern std::mutex XalqlarDostluqu_Ahmedli, Ahmedli_XalqlarDostluqu;
extern std::mutex Ahmedli_HeziAslanov, HeziAslanov_Ahmedli;

void Dernegul_to_AzadliqProspekti(int index);
void AzadliqProspekti_to_Dernegul(int index);
void AzadliqProspekti_to_Nasimi(int index);
void Nasimi_to_AzadliqProspekti(int index);
void Nasimi_to_MemarEcemi(int index);
void MemarEcemi_to_Nasimi(int index);
void MemarEcemi_to_20Yanvar(int index);
void Yanvar20_to_MemarEcemi(int index);
void Yanvar20_to_Insaatcilar(int index);
void Insaatcilar_to_20Yanvar(int index);
void Insaatcilar_to_ElmlerAkademiyasi(int index);
void ElmlerAkademiyasi_to_Insaatcilar(int index);
void ElmlerAkademiyasi_to_NizamiGencevi(int index);
void NizamiGencevi_to_ElmlerAkademiyasi(int index);
void NizamiGencevi_to_May28(int index);
void May28_to_NizamiGencevi(int index);



void IcheriSheher_to_Sahil(int index);
void Sahil_to_IcheriSheher(int index);
void Sahil_to_May28(int index);
void May28_to_Sahil(int index);



void May28_to_Genclik(int index);
void Genclik_to_May28(int index);
void Genclik_to_NarimanNarimanov(int index);
void NarimanNarimanov_to_Genclik(int index);
void NarimanNarimanov_to_Bakmil(int index);
void Bakmil_to_NarimanNarimanov(int index);

void NarimanNarimanov_to_Ulduz(int index);
void Ulduz_to_NarimanNarimanov(int index);
void Ulduz_to_Koroglu(int index);
void Koroglu_to_Ulduz(int index);
void Koroglu_to_QaraQarayev(int index);
void QaraQarayev_to_Koroglu(int index);
void QaraQarayev_to_Neftchiler(int index);
void Neftchiler_to_QaraQarayev(int index);
void Neftchiler_to_XalqlarDostluqu(int index);
void XalqlarDostluqu_to_Neftchiler(int index);
void XalqlarDostluqu_to_Ahmedli(int index);
void Ahmedli_to_XalqlarDostluqu(int index);
void Ahmedli_to_HeziAslanov(int index);
void HeziAslanov_to_Ahmedli(int index);



void Dvijeniye_green(int index, int amountOfCircles);
void Dvijeniye_krasniy(int index, int amountOfCircles);





extern std::mutex JafarJabbarli_Xetai, Xetai_JafarJabbarli;



void JafarJabbarli_to_Xetai(int index);
void Xetai_to_JafarJabbarli(int index);


void Dvijeniye_Solatoviy(int index, int amountOfCircles);

#endif