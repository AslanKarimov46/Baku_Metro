#include "metro.h"

// Общие мьютексы для обеих линий
std::mutex May28_Interchange; // Мьютекс для пересадки на станции May28

// Мьютексы для перегонов общего участка
std::mutex May28_Genclik_Segment;
std::mutex Genclik_NarimanNarimanov_Segment;
std::mutex NarimanNarimanov_Bakmil_Segment;
std::mutex NarimanNarimanov_Ulduz_Segment;

// Мьютексы для перегонов на участке NarimanNarimanov - HeziAslanov
std::mutex Ulduz_Koroglu_Segment;
std::mutex Koroglu_QaraQarayev_Segment;
std::mutex QaraQarayev_Neftchiler_Segment;
std::mutex Neftchiler_XalqlarDostluqu_Segment;
std::mutex XalqlarDostluqu_Ahmedli_Segment;
std::mutex Ahmedli_HeziAslanov_Segment;

// Мьютексы для станций
std::mutex May28_Station;
std::mutex Genclik_Station;
std::mutex NarimanNarimanov_Station;
std::mutex Bakmil_Station;

// Мьютексы для красной линии
std::mutex IcheriSheherRight, IcheriSheherLeft;
std::mutex SahilRight, SahilLeft;
std::mutex May28Right, May28Left;

// Мьютексы для зеленой линии
std::mutex DernegulRight, DernegulLeft;
std::mutex AzadliqProspektiRight, AzadliqProspektiLeft;
std::mutex NasimiRight, NasimiLeft;
std::mutex MemarEcemiRight, MemarEcemiLeft;
std::mutex YanvarRight, YanvarLeft;
std::mutex InsaatcilarRight, InsaatcilarLeft;
std::mutex ElmlerAkademiyasiRight, ElmlerAkademiyasiLeft;
std::mutex NizamiGenceviRight, NizamiGenceviLeft;
std::mutex May28GreenRight, May28GreenLeft;

// Остальные общие мьютексы для остальных станций и перегонов
std::mutex UlduzRight, UlduzLeft;
std::mutex KorogluRight, KorogluLeft;
std::mutex QaraQarayevRight, QaraQarayevLeft;
std::mutex NeftchilerRight, NeftchilerLeft;
std::mutex XalqlarDostluquRight, XalqlarDostluquLeft;
std::mutex AhmedliRight, AhmedliLeft;
std::mutex HeziAslanovRight, HeziAslanovLeft;
std::mutex GenclikRight, GenclikLeft;
std::mutex NarimanNarimanovRight, NarimanNarimanovLeft;
std::mutex BakmilRight, BakmilLeft;

//---------------------- ФУНКЦИИ КРАСНОЙ ЛИНИИ ----------------------//

// Функция для действий на станции красной линии
void RedLineStationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index) {
    try {
        std::unique_lock<std::mutex> lock(station_mutex);
        
        std::string start_time = getFormattedTime(index);
        
        train_time_offset[index] += REAL_TRAVEL_TIME_MIN;
        
        std::string arrival_time = getFormattedTime(index);
        
        std::string travel_message = from + " -> " + to + " " + start_time + " - " + arrival_time;
        logToFile(index, travel_message);
        
        sleep_(TRAVEL_TIME_MS * 5);
        
        logToFile(index, "Поезд " + std::to_string(index) + " прибыл на станцию " + to);
        logToFile(index, "Поезд " + std::to_string(index) + " делает остановку на станции " + to);
        
        train_time_offset[index] += 1;
        
        std::string departure_time = getFormattedTime(index);
        logToFile(index, "Поезд " + std::to_string(index) + " отправляется со станции " + to + " в " + departure_time);
        
        sleep_(5);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при обработке станции " << to << " для поезда " << index << ": " << e.what() << std::endl;
    }
}

void GreenLineStationAction(const std::string& from, const std::string& to, std::mutex& station_mutex, int index) {
    try {
        std::unique_lock<std::mutex> lock(station_mutex);
        
        std::string start_time = getFormattedTime(index);
        
        train_time_offset[index] += REAL_TRAVEL_TIME_MIN;
        
        std::string arrival_time = getFormattedTime(index);
        
        std::string travel_message = from + " -> " + to + " " + start_time + " - " + arrival_time;
        logToFile(index, travel_message);
        
        sleep_(TRAVEL_TIME_MS * 5);
        
        logToFile(index, "Поезд " + std::to_string(index) + " прибыл на станцию " + to);
        logToFile(index, "Поезд " + std::to_string(index) + " делает остановку на станции " + to);
        
        train_time_offset[index] += 1;
        
        std::string departure_time = getFormattedTime(index);
        logToFile(index, "Поезд " + std::to_string(index) + " отправляется со станции " + to + " в " + departure_time);
        
        sleep_(5);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при обработке станции " << to << " для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для логирования действий красной линии
void logRedLineAction(int index, const std::string& action) {
    try {
        std::string time = getFormattedTime(index);
        logToFile(index, time + " - " + action);
        
        train_time_offset[index] += 2;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при логировании действия красной линии: " << e.what() << std::endl;
    }
}

// Функция для логирования действий зеленой линии
void logGreenLineAction(int index, const std::string& action) {
    try {
        std::string time = getFormattedTime(index);
        logToFile(index, time + " - " + action);
        
        train_time_offset[index] += 2;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при логировании действия зеленой линии: " << e.what() << std::endl;
    }
}

// Перегон: Bakmil → NarimanNarimanov (общий участок)
void Bakmil_to_NarimanNarimanov(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(NarimanNarimanov_Bakmil_Segment);
        std::unique_lock<std::mutex> station_lock(NarimanNarimanov_Station);
        
        if (isRed) {
            RedLineStationAction("Bakmil", "NarimanNarimanov", NarimanNarimanovLeft, index);
        } else {
            GreenLineStationAction("Bakmil", "NarimanNarimanov", NarimanNarimanovLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Bakmil → NarimanNarimanov: " << e.what() << std::endl;
    }
}

// Перегон: NarimanNarimanov → Genclik (общий участок)
void NarimanNarimanov_to_Genclik(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Genclik_NarimanNarimanov_Segment);
        std::unique_lock<std::mutex> station_lock(Genclik_Station);
        
        if (isRed) {
            RedLineStationAction("NarimanNarimanov", "Genclik", GenclikLeft, index);
        } else {
            GreenLineStationAction("NarimanNarimanov", "Genclik", GenclikLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне NarimanNarimanov → Genclik: " << e.what() << std::endl;
    }
}

// Перегон: Genclik → May28 (общий участок)
void Genclik_to_May28(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(May28_Genclik_Segment);
        std::unique_lock<std::mutex> station_lock(May28_Station);
        
        if (isRed) {
            RedLineStationAction("Genclik", "May28", May28Left, index);
        } else {
            GreenLineStationAction("Genclik", "May28", May28Left, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Genclik → May28: " << e.what() << std::endl;
    }
}

// Перегон: May28 → Genclik (общий участок)
void May28_to_Genclik(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(May28_Genclik_Segment);
        std::unique_lock<std::mutex> station_lock(Genclik_Station);
        
        if (isRed) {
            RedLineStationAction("May28", "Genclik", GenclikRight, index);
        } else {
            GreenLineStationAction("May28", "Genclik", GenclikRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне May28 → Genclik: " << e.what() << std::endl;
    }
}

// Перегон: Genclik → NarimanNarimanov (общий участок)
void Genclik_to_NarimanNarimanov(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Genclik_NarimanNarimanov_Segment);
        std::unique_lock<std::mutex> station_lock(NarimanNarimanov_Station);
        
        if (isRed) {
            RedLineStationAction("Genclik", "NarimanNarimanov", NarimanNarimanovRight, index);
        } else {
            GreenLineStationAction("Genclik", "NarimanNarimanov", NarimanNarimanovRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Genclik → NarimanNarimanov: " << e.what() << std::endl;
    }
}

// Перегон: NarimanNarimanov → Bakmil (общий участок)
void NarimanNarimanov_to_Bakmil(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(NarimanNarimanov_Bakmil_Segment);
        std::unique_lock<std::mutex> station_lock(Bakmil_Station);
        
        if (isRed) {
            RedLineStationAction("NarimanNarimanov", "Bakmil", BakmilRight, index);
        } else {
            GreenLineStationAction("NarimanNarimanov", "Bakmil", BakmilRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне NarimanNarimanov → Bakmil: " << e.what() << std::endl;
    }
}

// Перегон: NarimanNarimanov → Ulduz (длинный маршрут)
void NarimanNarimanov_to_Ulduz(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(NarimanNarimanov_Ulduz_Segment);
        
        if (isRed) {
            RedLineStationAction("NarimanNarimanov", "Ulduz", UlduzRight, index);
        } else {
            GreenLineStationAction("NarimanNarimanov", "Ulduz", UlduzRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне NarimanNarimanov → Ulduz: " << e.what() << std::endl;
    }
}

// Перегон: Ulduz → Koroglu (длинный маршрут)
void Ulduz_to_Koroglu(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Ulduz_Koroglu_Segment);
        
        if (isRed) {
            RedLineStationAction("Ulduz", "Koroglu", KorogluRight, index);
        } else {
            GreenLineStationAction("Ulduz", "Koroglu", KorogluRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Ulduz → Koroglu: " << e.what() << std::endl;
    }
}

// Перегон: Koroglu → QaraQarayev (длинный маршрут)
void Koroglu_to_QaraQarayev(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Koroglu_QaraQarayev_Segment);
        
        if (isRed) {
            RedLineStationAction("Koroglu", "QaraQarayev", QaraQarayevRight, index);
        } else {
            GreenLineStationAction("Koroglu", "QaraQarayev", QaraQarayevRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Koroglu → QaraQarayev: " << e.what() << std::endl;
    }
}

// Перегон: QaraQarayev → Neftchiler (длинный маршрут)
void QaraQarayev_to_Neftchiler(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(QaraQarayev_Neftchiler_Segment);
        
        if (isRed) {
            RedLineStationAction("QaraQarayev", "Neftchiler", NeftchilerRight, index);
        } else {
            GreenLineStationAction("QaraQarayev", "Neftchiler", NeftchilerRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне QaraQarayev → Neftchiler: " << e.what() << std::endl;
    }
}

// Перегон: Neftchiler → XalqlarDostluqu (длинный маршрут)
void Neftchiler_to_XalqlarDostluqu(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Neftchiler_XalqlarDostluqu_Segment);
        
        if (isRed) {
            RedLineStationAction("Neftchiler", "XalqlarDostluqu", XalqlarDostluquRight, index);
        } else {
            GreenLineStationAction("Neftchiler", "XalqlarDostluqu", XalqlarDostluquRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Neftchiler → XalqlarDostluqu: " << e.what() << std::endl;
    }
}

// Перегон: XalqlarDostluqu → Ahmedli (длинный маршрут)
void XalqlarDostluqu_to_Ahmedli(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(XalqlarDostluqu_Ahmedli_Segment);
        
        if (isRed) {
            RedLineStationAction("XalqlarDostluqu", "Ahmedli", AhmedliRight, index);
        } else {
            GreenLineStationAction("XalqlarDostluqu", "Ahmedli", AhmedliRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне XalqlarDostluqu → Ahmedli: " << e.what() << std::endl;
    }
}

// Перегон: Ahmedli → HeziAslanov (длинный маршрут)
void Ahmedli_to_HeziAslanov(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Ahmedli_HeziAslanov_Segment);
        
        if (isRed) {
            RedLineStationAction("Ahmedli", "HeziAslanov", HeziAslanovRight, index);
        } else {
            GreenLineStationAction("Ahmedli", "HeziAslanov", HeziAslanovRight, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Ahmedli → HeziAslanov: " << e.what() << std::endl;
    }
}

// Перегоны в обратном направлении (используют те же мьютексы)
void HeziAslanov_to_Ahmedli(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Ahmedli_HeziAslanov_Segment);
        
        if (isRed) {
            RedLineStationAction("HeziAslanov", "Ahmedli", AhmedliLeft, index);
        } else {
            GreenLineStationAction("HeziAslanov", "Ahmedli", AhmedliLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне HeziAslanov → Ahmedli: " << e.what() << std::endl;
    }
}

void Ahmedli_to_XalqlarDostluqu(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(XalqlarDostluqu_Ahmedli_Segment);
        
        if (isRed) {
            RedLineStationAction("Ahmedli", "XalqlarDostluqu", XalqlarDostluquLeft, index);
        } else {
            GreenLineStationAction("Ahmedli", "XalqlarDostluqu", XalqlarDostluquLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Ahmedli → XalqlarDostluqu: " << e.what() << std::endl;
    }
}

void XalqlarDostluqu_to_Neftchiler(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Neftchiler_XalqlarDostluqu_Segment);
        
        if (isRed) {
            RedLineStationAction("XalqlarDostluqu", "Neftchiler", NeftchilerLeft, index);
        } else {
            GreenLineStationAction("XalqlarDostluqu", "Neftchiler", NeftchilerLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне XalqlarDostluqu → Neftchiler: " << e.what() << std::endl;
    }
}

void Neftchiler_to_QaraQarayev(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(QaraQarayev_Neftchiler_Segment);
        
        if (isRed) {
            RedLineStationAction("Neftchiler", "QaraQarayev", QaraQarayevLeft, index);
        } else {
            GreenLineStationAction("Neftchiler", "QaraQarayev", QaraQarayevLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Neftchiler → QaraQarayev: " << e.what() << std::endl;
    }
}

void QaraQarayev_to_Koroglu(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Koroglu_QaraQarayev_Segment);
        
        if (isRed) {
            RedLineStationAction("QaraQarayev", "Koroglu", KorogluLeft, index);
        } else {
            GreenLineStationAction("QaraQarayev", "Koroglu", KorogluLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне QaraQarayev → Koroglu: " << e.what() << std::endl;
    }
}

void Koroglu_to_Ulduz(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(Ulduz_Koroglu_Segment);
        
        if (isRed) {
            RedLineStationAction("Koroglu", "Ulduz", UlduzLeft, index);
        } else {
            GreenLineStationAction("Koroglu", "Ulduz", UlduzLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Koroglu → Ulduz: " << e.what() << std::endl;
    }
}

void Ulduz_to_NarimanNarimanov(int index, bool isRed) {
    try {
        std::unique_lock<std::mutex> segment_lock(NarimanNarimanov_Ulduz_Segment);
        
        if (isRed) {
            RedLineStationAction("Ulduz", "NarimanNarimanov", NarimanNarimanovLeft, index);
        } else {
            GreenLineStationAction("Ulduz", "NarimanNarimanov", NarimanNarimanovLeft, index);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Ulduz → NarimanNarimanov: " << e.what() << std::endl;
    }
}

// Перегоны уникальные для красной линии
void May28_to_Sahil(int index) {
    try {
        // Используем May28_Interchange для пересадки
        std::unique_lock<std::mutex> interchange_lock(May28_Interchange);
        RedLineStationAction("May28", "Sahil", SahilLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне May28 → Sahil: " << e.what() << std::endl;
    }
}

void Sahil_to_IcheriSheher(int index) {
    try {
        RedLineStationAction("Sahil", "IcheriSheher", IcheriSheherLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Sahil → IcheriSheher: " << e.what() << std::endl;
    }
}

void IcheriSheher_to_Sahil(int index) {
    try {
        RedLineStationAction("IcheriSheher", "Sahil", SahilRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне IcheriSheher → Sahil: " << e.what() << std::endl;
    }
}

void Sahil_to_May28(int index) {
    try {
        // Используем May28_Interchange для пересадки
        std::unique_lock<std::mutex> interchange_lock(May28_Interchange);
        RedLineStationAction("Sahil", "May28", May28Right, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Sahil → May28: " << e.what() << std::endl;
    }
}

// Функции для зеленой линии (уникальные участки)
void May28_to_NizamiGencevi(int index) {
    try {
        // Используем May28_Interchange для пересадки
        std::unique_lock<std::mutex> interchange_lock(May28_Interchange);
        GreenLineStationAction("May28", "NizamiGencevi", NizamiGenceviLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне May28 → NizamiGencevi: " << e.what() << std::endl;
    }
}

void NizamiGencevi_to_ElmlerAkademiyasi(int index) {
    try {
        GreenLineStationAction("NizamiGencevi", "ElmlerAkademiyasi", ElmlerAkademiyasiLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне NizamiGencevi → ElmlerAkademiyasi: " << e.what() << std::endl;
    }
}

void ElmlerAkademiyasi_to_Insaatcilar(int index) {
    try {
        GreenLineStationAction("ElmlerAkademiyasi", "Insaatcilar", InsaatcilarLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне ElmlerAkademiyasi → Insaatcilar: " << e.what() << std::endl;
    }
}

void Insaatcilar_to_20Yanvar(int index) {
    try {
        GreenLineStationAction("Insaatcilar", "20Yanvar", YanvarLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Insaatcilar → 20Yanvar: " << e.what() << std::endl;
    }
}

void Yanvar20_to_MemarEcemi(int index) {
    try {
        GreenLineStationAction("20Yanvar", "MemarEcemi", MemarEcemiLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне 20Yanvar → MemarEcemi: " << e.what() << std::endl;
    }
}

void MemarEcemi_to_Nasimi(int index) {
    try {
        GreenLineStationAction("MemarEcemi", "Nasimi", NasimiLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне MemarEcemi → Nasimi: " << e.what() << std::endl;
    }
}

void Nasimi_to_AzadliqProspekti(int index) {
    try {
        GreenLineStationAction("Nasimi", "AzadliqProspekti", AzadliqProspektiLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Nasimi → AzadliqProspekti: " << e.what() << std::endl;
    }
}

void AzadliqProspekti_to_Dernegul(int index) {
    try {
        GreenLineStationAction("AzadliqProspekti", "Dernegul", DernegulLeft, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне AzadliqProspekti → Dernegul: " << e.what() << std::endl;
    }
}

void Dernegul_to_AzadliqProspekti(int index) {
    try {
        GreenLineStationAction("Dernegul", "AzadliqProspekti", AzadliqProspektiRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Dernegul → AzadliqProspekti: " << e.what() << std::endl;
    }
}

void AzadliqProspekti_to_Nasimi(int index) {
    try {
        GreenLineStationAction("AzadliqProspekti", "Nasimi", NasimiRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне AzadliqProspekti → Nasimi: " << e.what() << std::endl;
    }
}

void Nasimi_to_MemarEcemi(int index) {
    try {
        GreenLineStationAction("Nasimi", "MemarEcemi", MemarEcemiRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Nasimi → MemarEcemi: " << e.what() << std::endl;
    }
}

void MemarEcemi_to_20Yanvar(int index) {
    try {
        GreenLineStationAction("MemarEcemi", "20Yanvar", YanvarRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне MemarEcemi → 20Yanvar: " << e.what() << std::endl;
    }
}

void Yanvar20_to_Insaatcilar(int index) {
    try {
        GreenLineStationAction("20Yanvar", "Insaatcilar", InsaatcilarRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне 20Yanvar → Insaatcilar: " << e.what() << std::endl;
    }
}

void Insaatcilar_to_ElmlerAkademiyasi(int index) {
    try {
        GreenLineStationAction("Insaatcilar", "ElmlerAkademiyasi", ElmlerAkademiyasiRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне Insaatcilar → ElmlerAkademiyasi: " << e.what() << std::endl;
    }
}

void ElmlerAkademiyasi_to_NizamiGencevi(int index) {
    try {
        GreenLineStationAction("ElmlerAkademiyasi", "NizamiGencevi", NizamiGenceviRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне ElmlerAkademiyasi → NizamiGencevi: " << e.what() << std::endl;
    }
}

void NizamiGencevi_to_May28(int index) {
    try {
        // Используем May28_Interchange для пересадки
        std::unique_lock<std::mutex> interchange_lock(May28_Interchange);
        GreenLineStationAction("NizamiGencevi", "May28", May28GreenRight, index);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка на перегоне NizamiGencevi → May28: " << e.what() << std::endl;
    }
}

// Начальное движение красной линии от Bakmil до IcheriSheher
void RedLineInitialRoute(int index) {
    try {
        logRedLineAction(index, "Поезд " + std::to_string(index) + " начинает начальное движение от Bakmil до IcheriSheher");
        
        // Bakmil → NarimanNarimanov → Genclik → May28 (общий участок с зеленой линией)
        Bakmil_to_NarimanNarimanov(index, true);
        sleep_(5);
        NarimanNarimanov_to_Genclik(index, true);
        sleep_(5);
        Genclik_to_May28(index, true);
        sleep_(5);
        
        // May28 → Sahil → IcheriSheher (уникальные станции красной линии)
        May28_to_Sahil(index);
        sleep_(5);
        Sahil_to_IcheriSheher(index);
        
        logRedLineAction(index, "Поезд " + std::to_string(index) + " завершил начальное движение и прибыл на IcheriSheher");
    } catch (const std::exception& e) {
        std::cerr << "Ошибка в начальном маршруте красной линии для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для длинного маршрута красной линии (IcheriSheher до HeziAslanov) - циклы 1-4
void RedLineLongRoute(int index) {
    try {
        logRedLineAction(index, "Поезд " + std::to_string(index) + " следует по полному маршруту до HeziAslanov");
        
        // IcheriSheher → Sahil → May28 (уникальные станции красной линии)
        IcheriSheher_to_Sahil(index);
        sleep_(5);
        Sahil_to_May28(index);
        sleep_(5);
        
        // May28 → Genclik → NarimanNarimanov (общий участок с зеленой линией)
        May28_to_Genclik(index, true);
        sleep_(5);
        Genclik_to_NarimanNarimanov(index, true);
        sleep_(5);
        
        // NarimanNarimanov → Ulduz → ... → HeziAslanov (общий для длинных маршрутов)
        NarimanNarimanov_to_Ulduz(index, true);
        sleep_(5);
        Ulduz_to_Koroglu(index, true);
        sleep_(5);
        Koroglu_to_QaraQarayev(index, true);
        sleep_(5);
        QaraQarayev_to_Neftchiler(index, true);
        sleep_(5);
        Neftchiler_to_XalqlarDostluqu(index, true);
        sleep_(5);
        XalqlarDostluqu_to_Ahmedli(index, true);
        sleep_(5);
        Ahmedli_to_HeziAslanov(index, true);
        
        logRedLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную HeziAslanov и делает разворот");
        train_time_offset[index] += 5; // Пять минут на разворот
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка в длинном маршруте красной линии для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для короткого маршрута красной линии (IcheriSheher до Bakmil) - цикл 5
void RedLineShortRoute(int index) {
    try {
        logRedLineAction(index, "Поезд " + std::to_string(index) + " следует по короткому маршруту до Bakmil");
        
        // IcheriSheher → Sahil → May28 (уникальные станции красной линии)
        IcheriSheher_to_Sahil(index);
        sleep_(5);
        Sahil_to_May28(index);
        sleep_(5);
        
        // May28 → Genclik → NarimanNarimanov → Bakmil (общий участок с зеленой линией)
        May28_to_Genclik(index, true);
        sleep_(5);
        Genclik_to_NarimanNarimanov(index, true);
        sleep_(5);
        NarimanNarimanov_to_Bakmil(index, true);
        
        logRedLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Bakmil и делает разворот");
        train_time_offset[index] += 5; // Пять минут на разворот
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка в коротком маршруте красной линии для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для возвращения красной линии от HeziAslanov до IcheriSheher - циклы 1-4
void RedLineReturnFromHeziAslanov(int index) {
    try {
        // HeziAslanov → ... → NarimanNarimanov (общий для длинных маршрутов)
        HeziAslanov_to_Ahmedli(index, true);
        sleep_(5);
        Ahmedli_to_XalqlarDostluqu(index, true);
        sleep_(5);
        XalqlarDostluqu_to_Neftchiler(index, true);
        sleep_(5);
        Neftchiler_to_QaraQarayev(index, true);
        sleep_(5);
        QaraQarayev_to_Koroglu(index, true);
        sleep_(5);
        Koroglu_to_Ulduz(index, true);
        sleep_(5);
        Ulduz_to_NarimanNarimanov(index, true);
        sleep_(5);
        
        // NarimanNarimanov → Genclik → May28 (общий участок с зеленой линией)
        NarimanNarimanov_to_Genclik(index, true);
        sleep_(5);
        Genclik_to_May28(index, true);
        sleep_(5);
        
        // May28 → Sahil → IcheriSheher (уникальные станции красной линии)
        May28_to_Sahil(index);
        sleep_(5);
        Sahil_to_IcheriSheher(index);
        
        logRedLineAction(index, "Поезд " + std::to_string(index) + " завершил полный маршрут и вернулся к IcheriSheher");
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при возвращении от HeziAslanov для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для возвращения красной линии от Bakmil до IcheriSheher - цикл 5
void RedLineReturnFromBakmil(int index) {
    try {
        // Bakmil → NarimanNarimanov → Genclik → May28 (общий участок с зеленой линией)
        Bakmil_to_NarimanNarimanov(index, true);
        sleep_(5);
        NarimanNarimanov_to_Genclik(index, true);
        sleep_(5);
        Genclik_to_May28(index, true);
        sleep_(5);
        
        // May28 → Sahil → IcheriSheher (уникальные станции красной линии)
        May28_to_Sahil(index);
        sleep_(5);
        Sahil_to_IcheriSheher(index);
        
        logRedLineAction(index, "Поезд " + std::to_string(index) + " завершил короткий маршрут и вернулся к IcheriSheher");
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при возвращении от Bakmil для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Начальное движение зеленой линии от Bakmil до Dernegul
void GreenLineInitialRoute(int index) {
    try {
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " начинает начальное движение от Bakmil до Dernegul");
        
        // Bakmil → NarimanNarimanov → Genclik → May28 (общий участок с красной линией)
        Bakmil_to_NarimanNarimanov(index, false);
        sleep_(5);
        NarimanNarimanov_to_Genclik(index, false);
        sleep_(5);
        Genclik_to_May28(index, false);
        sleep_(5);
        
        // May28 → ... → Dernegul (уникальные станции зеленой линии)
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
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " завершил начальное движение и прибыл на Dernegul");
    } catch (const std::exception& e) {
        std::cerr << "Ошибка в начальном маршруте зеленой линии для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для длинного маршрута зеленой линии (Dernegul до HeziAslanov) - циклы 1-4
void GreenLineLongRoute(int index) {
    try {
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " следует по полному маршруту до HeziAslanov");
        
        // Уникальные станции зеленой линии от Dernegul до May28
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
        
        // May28 → Genclik → NarimanNarimanov (общий участок с красной линией)
        May28_to_Genclik(index, false);
        sleep_(5);
        Genclik_to_NarimanNarimanov(index, false);
        sleep_(5);
        
        // NarimanNarimanov → Ulduz → ... → HeziAslanov (общий для длинных маршрутов)
        NarimanNarimanov_to_Ulduz(index, false);
        sleep_(5);
        Ulduz_to_Koroglu(index, false);
        sleep_(5);
        Koroglu_to_QaraQarayev(index, false);
        sleep_(5);
        QaraQarayev_to_Neftchiler(index, false);
        sleep_(5);
        Neftchiler_to_XalqlarDostluqu(index, false);
        sleep_(5);
        XalqlarDostluqu_to_Ahmedli(index, false);
        sleep_(5);
        Ahmedli_to_HeziAslanov(index, false);
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную HeziAslanov и делает разворот");
        train_time_offset[index] += 5; // Пять минут на разворот
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка в длинном маршруте зеленой линии для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для короткого маршрута зеленой линии (Dernegul до Bakmil) - цикл 5
void GreenLineShortRoute(int index) {
    try {
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " следует по короткому маршруту до Bakmil");
        
        // Уникальные станции зеленой линии от Dernegul до May28
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
        
        // May28 → Genclik → NarimanNarimanov → Bakmil (общий участок с красной линией)
        May28_to_Genclik(index, false);
        sleep_(5);
        Genclik_to_NarimanNarimanov(index, false);
        sleep_(5);
        NarimanNarimanov_to_Bakmil(index, false);
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " прибыл на конечную Bakmil и делает разворот");
        train_time_offset[index] += 5; // Пять минут на разворот
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка в коротком маршруте зеленой линии для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для возвращения зеленой линии от HeziAslanov до Dernegul - циклы 1-4
void GreenLineReturnFromHeziAslanov(int index) {
    try {
        // HeziAslanov → ... → NarimanNarimanov (общий для длинных маршрутов)
        HeziAslanov_to_Ahmedli(index, false);
        sleep_(5);
        Ahmedli_to_XalqlarDostluqu(index, false);
        sleep_(5);
        XalqlarDostluqu_to_Neftchiler(index, false);
        sleep_(5);
        Neftchiler_to_QaraQarayev(index, false);
        sleep_(5);
        QaraQarayev_to_Koroglu(index, false);
        sleep_(5);
        Koroglu_to_Ulduz(index, false);
        sleep_(5);
        Ulduz_to_NarimanNarimanov(index, false);
        sleep_(5);
        
        // NarimanNarimanov → Genclik → May28 (общий участок с красной линией)
        NarimanNarimanov_to_Genclik(index, false);
        sleep_(5);
        Genclik_to_May28(index, false);
        sleep_(5);
        
        // May28 → ... → Dernegul (уникальные станции зеленой линии)
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
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " вернулся на станцию Dernegul");
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при возвращении от HeziAslanov для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Функция для возвращения зеленой линии от Bakmil до Dernegul - цикл 5
void GreenLineReturnFromBakmil(int index) {
    try {
        // Bakmil → NarimanNarimanov → Genclik → May28 (общий участок с красной линией)
        Bakmil_to_NarimanNarimanov(index, false);
        sleep_(5);
        NarimanNarimanov_to_Genclik(index, false);
        sleep_(5);
        Genclik_to_May28(index, false);
        sleep_(5);
        
        // May28 → ... → Dernegul (уникальные станции зеленой линии)
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
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " вернулся на станцию Dernegul");
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при возвращении от Bakmil для поезда " << index << ": " << e.what() << std::endl;
    }
}

// Основная функция движения поезда красной линии
void Dvijeniye_krasniy(int index) {
    try {
        // Установка интервала между поездами
        train_time_offset[index] = (index - 4) * 10;
        
        // Начальное движение: Bakmil → IcheriSheher
        RedLineInitialRoute(index);
        
        // Выполнение 5 кругов
        for (int i = 1; i <= 5; i++) {
            logRedLineAction(index, "Поезд " + std::to_string(index) + " начинает круг " + std::to_string(i));
            
            if (i % 5 == 0) {
                // Короткий маршрут (до Bakmil) каждый 5-й круг
                RedLineShortRoute(index);
                RedLineReturnFromBakmil(index);
            } else {
                // Полный маршрут (до HeziAslanov) в циклах 1-4
                RedLineLongRoute(index);
                RedLineReturnFromHeziAslanov(index);
            }
            
            logRedLineAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i));
        }
        
        logRedLineAction(index, "Поезд " + std::to_string(index) + " завершил маршрут красной линии");
        
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в маршруте поезда " << index << " красной линии: " << e.what() << std::endl;
    }
}

// Основная функция движения поезда зеленой линии
void Dvijeniye_zeleniy(int index) {
    try {
        // Установка интервала между поездами
        train_time_offset[index] = (index - 7) * 10;
        
        // Начальное движение: Bakmil → Dernegul
        GreenLineInitialRoute(index);
        
        // Выполнение 5 кругов
        for (int i = 1; i <= 5; i++) {
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " начинает круг " + std::to_string(i));
            
            if (i % 5 == 0) {
                // Короткий маршрут (до Bakmil) каждый 5-й круг
                GreenLineShortRoute(index);
                GreenLineReturnFromBakmil(index);
            } else {
                // Полный маршрут (до HeziAslanov) в циклах 1-4
                GreenLineLongRoute(index);
                GreenLineReturnFromHeziAslanov(index);
            }
            
            // Пауза перед следующим кругом
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " делает длинную остановку на станции Dernegul");
            train_time_offset[index] += 5;
            
            logGreenLineAction(index, "Поезд " + std::to_string(index) + " завершил круг " + std::to_string(i));
        }
        
        logGreenLineAction(index, "Поезд " + std::to_string(index) + " завершил маршрут зеленой линии");
        
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка в маршруте поезда " << index << " зеленой линии: " << e.what() << std::endl;
    }
}