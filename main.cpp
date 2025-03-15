/*void Xodjasan(int index){
    std::lock_guard<std::mutex> guard(mtx);
    sleep_(3);
    std::cout << "Xodjasan -> " << index << " -> Avtovogzal\n";
}

void Avtovogzal(int index){
    std::lock_guard<std::mutex> guard(mtx);
    sleep_(3);
    std::cout << "Avtovogzal -> " << index << " -> MemarAdjemi\n";
}

void MemarAdjemi(int index){
    std::lock_guard<std::mutex> guard(mtx);
    sleep_(3);
    std::cout << "MemarAdjemi -> " << index << " -> 8Noyabr\n";
}

void Noyabr8(int index){
    std::lock_guard<std::mutex> guard(mtx);
    sleep_(3);
    std::cout << "8Noyabr -> " << index << " -> MemarAdjemi\n";
}

void MemarAdjemi_(int index){
    std::lock_guard<std::mutex> guard(mtx);
    sleep_(3);
    std::cout << "MemarAdjemi -> " << index << " -> Avtovogzal\n";
}

void Avtovogzal_(int index){
    std::lock_guard<std::mutex> guard(mtx);
    sleep_(3);
    std::cout << "Avtovogzal -> " << index << " -> Xodjasan\n";
}*/



#include "metro.h"

int main(){
    std::vector<std::thread> Trains;

    Trains.push_back(std::thread(Dvijeniye_violete, 3));
    sleep_(3);
    Trains.push_back(std::thread(Dvijeniye_violete, 2));
    sleep_(3);
    Trains.push_back(std::thread(Dvijeniye_violete, 1));

    for (auto& train : Trains) {
        train.join();
    }

    return 0;
}