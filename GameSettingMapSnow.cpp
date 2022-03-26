#include "./include/GameSettingMapSnow.h"

GameSettingMapSnow::GameSettingMapSnow(){

}

GameSettingMapSnow::~GameSettingMapSnow(){
    delete [] name;
    name = nullptr;
}

void GameSettingMapSnow::execute(){
    std::cout << "gamesettingmapsnow execute " << std::endl;
}