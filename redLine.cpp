#include "metro.h"

std::mutex IcheriSheherRight;
std::mutex IcheriSheherLeft;
std::mutex SahilRight;
std::mutex SahilLeft;
std::mutex May28Right;
std::mutex May28Left;
std::mutex GenclikRight;
std::mutex GenclikLeft;
std::mutex NarimanNarimanovRight;
std::mutex NarimanNarimanovLeft;
std::mutex BakmilRight;
std::mutex BakmilLeft;
std::mutex UlduzRight;
std::mutex UlduzLeft;
std::mutex KorogluRight;
std::mutex KorogluLeft;
std::mutex QaraQarayevRight;
std::mutex QaraQarayevLeft;
std::mutex NeftchilerRight;
std::mutex NeftchilerLeft;
std::mutex XalqlarDostluquRight;
std::mutex XalqlarDostluquLeft;
std::mutex AhmedliRight;
std::mutex AhmedliLeft;

void IcheriSheher(int index){
    { 
        std::lock_guard<std::mutex> guard(IcheriSheherRight);
        std::cout << "IcheriSheher -> " << index << " -> Sahil\n";
    }
    sleep_(3);
}

void Sahil(int index){
    { 
        std::lock_guard<std::mutex> guard(SahilRight);
        std::cout << "Sahil-> " << index << " -> May28\n";
    }
    sleep_(3);
}

void May28(int index){
    { 
        std::lock_guard<std::mutex> guard(May28Right);
        std::cout << "May28-> " << index << " -> Genclik\n";
    }
    sleep_(3);
}

void Genclik(int index){
    { 
        std::lock_guard<std::mutex> guard(GenclikRight);
        std::cout << "Genclik-> " << index << " -> NarimanNarimanov\n";
    }
    sleep_(3);
}

void NarimanNarimanov(int index){
    { 
        std::lock_guard<std::mutex> guard(NarimanNarimanovRight);
        std::cout << "NarimanNarimanov-> " << index << " -> Bakmil\n";
    }
    sleep_(3);
}

void Bakmil(int index){
    { 
        std::lock_guard<std::mutex> guard(BakmilRight);
        std::cout << "Bakmil-> " << index << " -> Ulduz\n";
    }
    sleep_(3);
}

void Ulduz(int index){
    { 
        std::lock_guard<std::mutex> guard(UlduzRight);
        std::cout << "Ulduz-> " << index << " -> Koroglu\n";
    }
    sleep_(3);
}

void Koroglu(int index){
    { 
        std::lock_guard<std::mutex> guard(KorogluRight);
        std::cout << "Koroglu-> " << index << " -> QaraQarayev\n";
    }
    sleep_(3);
}

void QaraQarayev(int index){
    { 
        std::lock_guard<std::mutex> guard(QaraQarayevRight);
        std::cout << "QaraQarayev-> " << index << " -> Neftchiler\n";
    }
    sleep_(3);
}

void Neftchiler(int index){
    { 
        std::lock_guard<std::mutex> guard(NeftchilerRight);
        std::cout << "Neftchiler-> " << index << " -> XalqlarDostluqu\n";
    }
    sleep_(3);
}

void XalqlarDostluqu(int index){
    { 
        std::lock_guard<std::mutex> guard(XalqlarDostluquRight);
        std::cout << "XalqlarDostluqu-> " << index << " -> Ahmedli\n";
    }
    sleep_(3);
}

void Ahmedli(int index){
    { 
        std::lock_guard<std::mutex> guard(AhmedliRight);
        std::cout << "Ahmedli-> " << index << " -> HeziAslanov\n";
    }
    sleep_(3);
}


void HeziAslanov_(int index){
    { 
        std::lock_guard<std::mutex> guard(AhmedliLeft);
        std::cout << "HeziAslanov-> " << index << " -> Ahmedli\n";
    }
    sleep_(3);
}

void Ahmedli_(int index){
    { 
        std::lock_guard<std::mutex> guard(XalqlarDostluquLeft);
        std::cout << "Ahmedli-> " << index << " -> XalqlarDostluqu\n";
    }
    sleep_(3);
}

void XalqlarDostluqu_(int index){
    { 
        std::lock_guard<std::mutex> guard(NeftchilerLeft);
        std::cout << "XalqlarDostluqu-> " << index << " -> Neftchiler\n";
    }
    sleep_(3);
}

void Neftchiler_(int index){
    { 
        std::lock_guard<std::mutex> guard(QaraQarayevLeft);
        std::cout << "Neftchiler-> " << index << " -> QaraQarayev\n";
    }
    sleep_(3);
}

void QaraQarayev_(int index){
    { 
        std::lock_guard<std::mutex> guard(KorogluLeft);
        std::cout << "QaraQarayev-> " << index << " -> Koroglu\n";
    }
    sleep_(3);
}

void Koroglu_(int index){
    { 
        std::lock_guard<std::mutex> guard(UlduzLeft);
        std::cout << "Koroglu-> " << index << " -> Ulduz\n";
    }
    sleep_(3);
}

void Ulduz_(int index){
    { 
        std::lock_guard<std::mutex> guard(BakmilLeft);
        std::cout << "Ulduz-> " << index << " -> Bakmil\n";
    }
    sleep_(3);
}

void Bakmil_(int index){
    { 
        std::lock_guard<std::mutex> guard(NarimanNarimanovLeft);
        std::cout << "Bakmil-> " << index << " -> NarimanNarimanov\n";
    }
    sleep_(3);
}

void NarimanNarimanov_(int index){
    { 
        std::lock_guard<std::mutex> guard(GenclikLeft);
        std::cout << "NarimanNarimanov-> " << index << " -> Genclik\n";
    }
    sleep_(3);
}

void Genclik_(int index){
    { 
        std::lock_guard<std::mutex> guard(May28Left);
        std::cout << "Genclik-> " << index << " -> May28\n";
    }
    sleep_(3);
}

void May28_(int index){
    { 
        std::lock_guard<std::mutex> guard(SahilLeft);
        std::cout << "May28-> " << index << " -> Sahil\n";
    }
    sleep_(3);
}

void Sahil_(int index){
    { 
        std::lock_guard<std::mutex> guard(IcheriSheherLeft);
        std::cout << "Sahil-> " << index << " -> IcheriSheher\n";
    }
    sleep_(3);
}

void Dvijeniye_krasniy(int index){
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

    for(int i=1; ; i++){
        IcheriSheher(index);
        sleep_(1);
        Sahil(index);
        if( i%5 == 0){

        }
    }

}