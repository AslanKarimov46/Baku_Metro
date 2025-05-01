#include "metro.h"


std::mutex Dernegul_AzadliqProspekti, AzadliqProspekti_Dernegul;
std::mutex AzadliqProspekti_Nasimi, Nasimi_AzadliqProspekti;
std::mutex Nasimi_MemarEcemi, MemarEcemi_Nasimi;
std::mutex MemarEcemi_Yanvar, Yanvar_MemarEcemi;
std::mutex Yanvar_Insaatcilar, Insaatcilar_Yanvar;
std::mutex Insaatcilar_ElmlerAkademiyasi, ElmlerAkademiyasi_Insaatcilar;
std::mutex ElmlerAkademiyasi_NizamiGencevi, NizamiGencevi_ElmlerAkademiyasi;
std::mutex NizamiGencevi_May28, May28_NizamiGencevi;

std::mutex IcheriSheher_Sahil, Sahil_IcheriSheher;
std::mutex Sahil_May28, May28_Sahil;


std::mutex May28_Genclik, Genclik_May28;
std::mutex Genclik_NarimanNarimanov, NarimanNarimanov_Genclik;
std::mutex NarimanNarimanov_Bakmil, Bakmil_NarimanNarimanov;

std::mutex NarimanNarimanov_Ulduz, Ulduz_NarimanNarimanov;
std::mutex Ulduz_Koroglu, Koroglu_Ulduz;
std::mutex Koroglu_QaraQarayev, QaraQarayev_Koroglu;
std::mutex QaraQarayev_Neftchiler, Neftchiler_QaraQarayev;
std::mutex Neftchiler_XalqlarDostluqu, XalqlarDostluqu_Neftchiler;
std::mutex XalqlarDostluqu_Ahmedli, Ahmedli_XalqlarDostluqu;
std::mutex Ahmedli_HeziAslanov, HeziAslanov_Ahmedli;



void Dernegul_to_AzadliqProspekti(int index) {
    StationAction("Dernegul", "AzadliqProspekti", Dernegul_AzadliqProspekti, index);
}

void AzadliqProspekti_to_Dernegul(int index) {
    StationAction("AzadliqProspekti", "Dernegul", AzadliqProspekti_Dernegul, index);
}

void AzadliqProspekti_to_Nasimi(int index) {
    StationAction("AzadliqProspekti", "Nasimi", AzadliqProspekti_Nasimi, index);
}

void Nasimi_to_AzadliqProspekti(int index) {
    StationAction("Nasimi", "AzadliqProspekti", Nasimi_AzadliqProspekti, index);
}

void Nasimi_to_MemarEcemi(int index) {
    StationAction("Nasimi", "MemarEcemi", Nasimi_MemarEcemi, index);
}

void MemarEcemi_to_Nasimi(int index) {
    StationAction("MemarEcemi", "Nasimi", MemarEcemi_Nasimi, index);
}

void MemarEcemi_to_20Yanvar(int index) {
    StationAction("MemarEcemi", "20Yanvar", MemarEcemi_Yanvar, index);
}

void Yanvar20_to_MemarEcemi(int index) {
    StationAction("20Yanvar", "MemarEcemi", Yanvar_MemarEcemi, index);
}

void Yanvar20_to_Insaatcilar(int index) {
    StationAction("20Yanvar", "Insaatcilar", Yanvar_Insaatcilar, index);
}

void Insaatcilar_to_20Yanvar(int index) {
    StationAction("Insaatcilar", "20Yanvar", Insaatcilar_Yanvar, index);
}

void Insaatcilar_to_ElmlerAkademiyasi(int index) {
    StationAction("Insaatcilar", "ElmlerAkademiyasi", Insaatcilar_ElmlerAkademiyasi, index);
}

void ElmlerAkademiyasi_to_Insaatcilar(int index) {
    StationAction("ElmlerAkademiyasi", "Insaatcilar", ElmlerAkademiyasi_Insaatcilar, index);
}

void ElmlerAkademiyasi_to_NizamiGencevi(int index) {
    StationAction("ElmlerAkademiyasi", "NizamiGencevi", ElmlerAkademiyasi_NizamiGencevi, index);
}

void NizamiGencevi_to_ElmlerAkademiyasi(int index) {
    StationAction("NizamiGencevi", "ElmlerAkademiyasi", NizamiGencevi_ElmlerAkademiyasi, index);
}

void NizamiGencevi_to_May28(int index) {
    StationAction("NizamiGencevi", "May28", NizamiGencevi_May28, index);
}

void May28_to_NizamiGencevi(int index) {
    StationAction("May28", "NizamiGencevi", May28_NizamiGencevi, index);
}

void IcheriSheher_to_Sahil(int index) {
    StationAction("IcheriSheher", "Sahil", IcheriSheher_Sahil, index);
}

void Sahil_to_IcheriSheher(int index) {
    StationAction("Sahil", "IcheriSheher", Sahil_IcheriSheher, index);
}

void Sahil_to_May28(int index) {
    StationAction("Sahil", "May28", Sahil_May28, index);
}

void May28_to_Sahil(int index) {
    StationAction("May28", "Sahil", May28_Sahil, index);
}

void May28_to_Genclik(int index) {
    StationAction("May28", "Genclik", May28_Genclik, index);
}

void Genclik_to_May28(int index) {
    StationAction("Genclik", "May28", Genclik_May28, index);
}

void Genclik_to_NarimanNarimanov(int index) {
    StationAction("Genclik", "NarimanNarimanov", Genclik_NarimanNarimanov, index);
}

void NarimanNarimanov_to_Genclik(int index) {
    StationAction("NarimanNarimanov", "Genclik", NarimanNarimanov_Genclik, index);
}

void NarimanNarimanov_to_Bakmil(int index) {
    StationAction("NarimanNarimanov", "Bakmil", NarimanNarimanov_Bakmil, index);
}

void Bakmil_to_NarimanNarimanov(int index) {
    StationAction("Bakmil", "NarimanNarimanov", Bakmil_NarimanNarimanov, index);
}

void NarimanNarimanov_to_Ulduz(int index) {
    StationAction("NarimanNarimanov", "Ulduz", NarimanNarimanov_Ulduz, index);
}

void Ulduz_to_NarimanNarimanov(int index) {
    StationAction("Ulduz", "NarimanNarimanov", Ulduz_NarimanNarimanov, index);
}

void Ulduz_to_Koroglu(int index) {
    StationAction("Ulduz", "Koroglu", Ulduz_Koroglu, index);
}

void Koroglu_to_Ulduz(int index) {
    StationAction("Koroglu", "Ulduz", Koroglu_Ulduz, index);
}

void Koroglu_to_QaraQarayev(int index) {
    StationAction("Koroglu", "QaraQarayev", Koroglu_QaraQarayev, index);
}

void QaraQarayev_to_Koroglu(int index) {
    StationAction("QaraQarayev", "Koroglu", QaraQarayev_Koroglu, index);
}

void QaraQarayev_to_Neftchiler(int index) {
    StationAction("QaraQarayev", "Neftchiler", QaraQarayev_Neftchiler, index);
}

void Neftchiler_to_QaraQarayev(int index) {
    StationAction("Neftchiler", "QaraQarayev", Neftchiler_QaraQarayev, index);
}

void Neftchiler_to_XalqlarDostluqu(int index) {
    StationAction("Neftchiler", "XalqlarDostluqu", Neftchiler_XalqlarDostluqu, index);
}

void XalqlarDostluqu_to_Neftchiler(int index) {
    StationAction("XalqlarDostluqu", "Neftchiler", XalqlarDostluqu_Neftchiler, index);
}

void XalqlarDostluqu_to_Ahmedli(int index) {
    StationAction("XalqlarDostluqu", "Ahmedli", XalqlarDostluqu_Ahmedli, index);
}

void Ahmedli_to_XalqlarDostluqu(int index) {
    StationAction("Ahmedli", "XalqlarDostluqu", Ahmedli_XalqlarDostluqu, index);
}

void Ahmedli_to_HeziAslanov(int index) {
    StationAction("Ahmedli", "HeziAslanov", Ahmedli_HeziAslanov, index);
}

void HeziAslanov_to_Ahmedli(int index) {
    StationAction("HeziAslanov", "Ahmedli", HeziAslanov_Ahmedli, index);
}


void Dvijeniye_green(int index, int amountOfCircles) {
    try {
        train_time_offset[index] = (index-7) * 20;
        
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
        { 
            Bakmil_to_NarimanNarimanov(index);
            sleep_(5);
        }
        { 
            NarimanNarimanov_to_Genclik(index);
            sleep_(5);
        }
        { 
            Genclik_to_May28(index);
            sleep_(5);
        }

        May28_to_NizamiGencevi(index);
        sleep_(5);

        NizamiGencevi_to_ElmlerAkademiyasi(index);
        sleep_(5);

        ElmlerAkademiyasi_to_Insaatcilar(index);
        sleep_(5);

        Insaatcilar_to_20Yanvar(index);
        sleep_(5);

        Yanvar20_to_MemarEcemi(index);
        sleep_(5);

        MemarEcemi_to_Nasimi(index);
        sleep_(5);

        Nasimi_to_AzadliqProspekti(index);
        sleep_(5);

        AzadliqProspekti_to_Dernegul(index);
        sleep_(5);

        logAction(index, "Поезд " + std::to_string(index) + " делает разворот");

        for(int i = 0; i < amountOfCircles; ++i){
            sleep_(10);
            Dernegul_to_AzadliqProspekti(index);
            sleep_(5);
            AzadliqProspekti_to_Nasimi(index);
            sleep_(5);
            Nasimi_to_MemarEcemi(index);
            sleep_(5);
            MemarEcemi_to_20Yanvar(index);
            sleep_(5);
            Yanvar20_to_Insaatcilar(index);
            sleep_(5);
            Insaatcilar_to_ElmlerAkademiyasi(index);
            sleep_(5);
            ElmlerAkademiyasi_to_NizamiGencevi(index);
            sleep_(5);
            NizamiGencevi_to_May28(index);
            sleep_(5);

            { 
                May28_to_Genclik(index);
                sleep_(5);
            }
            { 
                Genclik_to_NarimanNarimanov(index);
                sleep_(5);
            }

            if(i % 5 != 0) {
                // Длинный маршрут
                { 
                    NarimanNarimanov_to_Ulduz(index);
                    sleep_(5);
                }
                { 
                    Ulduz_to_Koroglu(index);
                    sleep_(5);
                }
                { 
                    Koroglu_to_QaraQarayev(index);
                    sleep_(5);
                }
                { 
                    QaraQarayev_to_Neftchiler(index);
                    sleep_(5);
                }
                { 
                    Neftchiler_to_XalqlarDostluqu(index);
                    sleep_(5);
                }
                { 
                    XalqlarDostluqu_to_Ahmedli(index);
                    sleep_(5);
                }
                { 
                    Ahmedli_to_HeziAslanov(index);
                    sleep_(5);
                }

                logAction(index, "Поезд " + std::to_string(index) + " делает разворот");
                sleep_(10);

                { 
                    HeziAslanov_to_Ahmedli(index);
                    sleep_(5);
                }
                { 
                    Ahmedli_to_XalqlarDostluqu(index);
                    sleep_(5);
                }
                { 
                    XalqlarDostluqu_to_Neftchiler(index);
                    sleep_(5);
                }
                { 
                    Neftchiler_to_QaraQarayev(index);
                    sleep_(5);
                }
                { 
                    QaraQarayev_to_Koroglu(index);
                    sleep_(5);
                }
                { 
                    Koroglu_to_Ulduz(index);
                    sleep_(5);
                }
                { 
                    Ulduz_to_NarimanNarimanov(index);
                    sleep_(5);
                }
                { 
                    NarimanNarimanov_to_Genclik(index);
                    sleep_(5);
                }
                { 
                    Genclik_to_May28(index);
                    sleep_(5);
                }
            } else {
                { 
                    NarimanNarimanov_to_Bakmil(index);
                    sleep_(5);
                }
                logAction(index, "Поезд " + std::to_string(index) + " делает разворот");
                sleep_(10);
                { 
                    Bakmil_to_NarimanNarimanov(index);
                    sleep_(5);
                }
                { 
                    NarimanNarimanov_to_Genclik(index);
                    sleep_(5);
                }
                { 
                    Genclik_to_May28(index);
                    sleep_(5);
                }
            }

            May28_to_NizamiGencevi(index);
            sleep_(5);
            NizamiGencevi_to_ElmlerAkademiyasi(index);
            sleep_(5);
            ElmlerAkademiyasi_to_Insaatcilar(index);
            sleep_(5);
            Insaatcilar_to_20Yanvar(index);
            sleep_(5);
            Yanvar20_to_MemarEcemi(index);
            sleep_(5);
            MemarEcemi_to_Nasimi(index);
            sleep_(5);
            Nasimi_to_AzadliqProspekti(index);
            sleep_(5);
            AzadliqProspekti_to_Dernegul(index);
            sleep_(5);
            
            logAction(index, "Поезд " + std::to_string(index) + " делает разворот");
            sleep_(10);
            
            logAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i+1));
        }
        
        logAction(index, "Поезд " + std::to_string(index) + " завершил маршрут зеленой линии");
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в маршруте поезда " << index << " (зеленая линия): " << e.what() << std::endl;
    }
}

void Dvijeniye_krasniy(int index, int amountOfCircles){
    try {
        train_time_offset[index] = (index-17) * 20 + 10;
        
        {
            std::lock_guard<std::mutex> file_guard(files_mutex);
            std::ofstream file("train_" + std::to_string(index) + ".txt");
            if (file.is_open()) {
                file << "=== Лог поезда " << index << " (Красная линия) ===" << std::endl;
                file.close();
            } else {
                std::cerr << "Ошибка: не удалось создать файл для поезда " << index << std::endl;
                return;
            }
        }

        { 
            Bakmil_to_NarimanNarimanov(index);
            sleep_(5);
        }
        { 
            NarimanNarimanov_to_Genclik(index);
            sleep_(5);
        }
        { 
            Genclik_to_May28(index);
            sleep_(5);
        }

        May28_to_Sahil(index);
        sleep_(5);

        Sahil_to_IcheriSheher(index);
        sleep_(5);

        logAction(index, "Поезд " + std::to_string(index) + " делает разворот");

        for(int i = 0; i < amountOfCircles; ++i){
            sleep_(10);
            IcheriSheher_to_Sahil(index);
            sleep_(5);
            Sahil_to_May28(index);
            sleep_(5);

            { 
                May28_to_Genclik(index);
                sleep_(5);
            }
            { 
                Genclik_to_NarimanNarimanov(index);
                sleep_(5);
            }

            if(i % 5 != 0){
                { 
                    NarimanNarimanov_to_Ulduz(index);
                    sleep_(5);
                }
                { 
                    Ulduz_to_Koroglu(index);
                    sleep_(5);
                }
                { 
                    Koroglu_to_QaraQarayev(index);
                    sleep_(5);
                }
                { 
                    QaraQarayev_to_Neftchiler(index);
                    sleep_(5);
                }
                { 
                    Neftchiler_to_XalqlarDostluqu(index);
                    sleep_(5);
                }
                { 
                    XalqlarDostluqu_to_Ahmedli(index);
                    sleep_(5);
                }
                { 
                    Ahmedli_to_HeziAslanov(index);
                    sleep_(5);
                }

                logAction(index, "Поезд " + std::to_string(index) + " делает разворот");
                sleep_(10);

                { 
                    HeziAslanov_to_Ahmedli(index);
                    sleep_(5);
                }
                { 
                    Ahmedli_to_XalqlarDostluqu(index);
                    sleep_(5);
                }
                { 
                    XalqlarDostluqu_to_Neftchiler(index);
                    sleep_(5);
                }
                { 
                    Neftchiler_to_QaraQarayev(index);
                    sleep_(5);
                }
                { 
                    QaraQarayev_to_Koroglu(index);
                    sleep_(5);
                }
                { 
                    Koroglu_to_Ulduz(index);
                    sleep_(5);
                }
                { 
                    Ulduz_to_NarimanNarimanov(index);
                    sleep_(5);
                }
                { 
                    NarimanNarimanov_to_Genclik(index);
                    sleep_(5);
                }
                { 
                    Genclik_to_May28(index);
                    sleep_(5);
                }
            } else {
                { 
                    NarimanNarimanov_to_Bakmil(index);
                    sleep_(5);
                }
                logAction(index, "Поезд " + std::to_string(index) + " делает разворот");
                sleep_(10);
                { 
                    Bakmil_to_NarimanNarimanov(index);
                    sleep_(5);
                }
                { 
                    NarimanNarimanov_to_Genclik(index);
                    sleep_(5);
                }
                { 
                    Genclik_to_May28(index);
                    sleep_(5);
                }
            }

            May28_to_Sahil(index);
            sleep_(5);
            Sahil_to_IcheriSheher(index);
            sleep_(5);
            
            logAction(index, "Поезд " + std::to_string(index) + " делает разворот");
            sleep_(10);
            
            logAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i+1));
        }
        
        logAction(index, "Поезд " + std::to_string(index) + " завершил маршрут красной линии");
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в маршруте поезда " << index << " (красная линия): " << e.what() << std::endl;
    }
}