#include "./include/GameSetting.h"

GameSetting::GameSetting(){

}

GameSetting::~GameSetting(){
   delete []name;
   name = nullptr;
}

void GameSetting::execute(){
	
}