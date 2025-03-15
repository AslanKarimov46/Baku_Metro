#include "metro.h"

std::mutex XodjasanRight;
std::mutex XodjasanLeft;
std::mutex AvtovogzalRight;
std::mutex AvtovogzalLeft;
std::mutex VioleteMemarAdjemiRight;
std::mutex VioleteMemarAdjemiLeft; 

void sleep_(int seconds){
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Xodjasan(int index){
    { 
        std::lock_guard<std::mutex> guard(XodjasanRight);
        std::cout << "Xodjasan -> " << index << " -> Avtovogzal\n";
    }
    sleep_(3);
    std::cout<< index <<" доехал\n";
}

void Avtovogzal(int index){
    { 
        std::lock_guard<std::mutex> guard(AvtovogzalRight);
        std::cout << "Avtovogzal -> " << index << " -> VioleteMemarAdjemi\n";
    }
    sleep_(3);
    std::cout<< index <<" доехал\n";
}

void VioleteMemarAdjemi(int index){
    { 
        std::lock_guard<std::mutex> guard(VioleteMemarAdjemiRight);
        std::cout << "VioleteMemarAdjemi -> " << index << " -> 8Noyabr\n";
    }
    sleep_(3);
    std::cout<< index <<" доехал\n";
}
    
void Noyabr8(int index){
    {     
        std::lock_guard<std::mutex> guard(VioleteMemarAdjemiLeft);
        std::cout << "8Noyabr -> " << index << " -> VioleteMemarAdjemi\n";
    }
    sleep_(3);
    std::cout<< index <<" доехал\n";
}    

void VioleteMemarAdjemi_(int index){
    { 
        std::lock_guard<std::mutex> guard(AvtovogzalLeft);
        std::cout << "VioleteMemarAdjemi -> " << index << " -> Avtovogzal\n";
    }
    sleep_(3);
    std::cout<< index <<" доехал\n";
}

void Avtovogzal_(int index){
    { 
        std::lock_guard<std::mutex> guard(XodjasanLeft);
        std::cout << "Avtovogzal -> " << index << " -> Xodjasan\n";
    }
    sleep_(3);
    std::cout<< index <<" доехал\n";
}

void Dvijeniye_violete(int index){
    for(int i = 0; i < 5; ++i){
        {
            std::lock_guard<std::mutex> guard(XodjasanLeft);
            std::cout << "Мужик гуляет\n";
        }
        sleep_(2);
        Xodjasan(index);
        sleep_(1);
        Avtovogzal(index);
        sleep_(1);
        VioleteMemarAdjemi(index);
        {
            std::lock_guard<std::mutex> guard(VioleteMemarAdjemiLeft);
            std::cout << "Мужик гуляет и крутится\n";
        }
        sleep_(4);
        Noyabr8(index);
        sleep_(1);
        VioleteMemarAdjemi_(index);
        sleep_(1);
        Avtovogzal_(index);
    }
}