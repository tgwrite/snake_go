#pragma once
#pragma execution_character_set("utf-8")
#include "./include/GameReadLoad.h"
#include "./include/SnakeGo.h"
#include "./include/filled_thing/SnakeNode.h"
#include "./include/filled_thing/FilledThing.h"
#include "./include/filled_thing/NormalFood.h"
#include "./include/mapgo/MapGo.h"
#include "./include/mapgo/NormalMap.h"
#include "./include/mapgo/CustomMaps.h"
#include "./include/Coordinate.h"
#include "./include/GameMusicEffect.h"

extern GameMusicEffect gameMusicEffectObj;

GameReadLoad::GameReadLoad() {

}

GameReadLoad::~GameReadLoad(){
	delete []name;
	name = nullptr;
}




void saveWholeMapVectorToFile() {
	//wholeMapVector
	FILE* filePointer = nullptr;
	fopen_s(&filePointer, MAP_VECTOR_SAVE_PATH, WRITE_AND_READ_BINARY);
	int mapCount = wholeMapVector.size();
	//表示有几个地图
	fwrite(&mapCount, sizeof(int), 1, filePointer);
	
	for (int mapIndex = 0; mapIndex < wholeMapVector.size(); mapIndex++) {
		//这里存储地图的序列号信息描述和名字在映射表里面匹配
		int mapSerialNumber = wholeMapVector[mapIndex]->mapSerialNumber;
		fwrite(&mapSerialNumber, sizeof(int), 1, filePointer);
		wholeMapVector[mapIndex]->saveMapToFile(filePointer);
	}
	fclose(filePointer);
}

MapGo* matchSpecificMap(int mapSerialNumber) {
	switch (mapSerialNumber) {
	case NORMAL_MAP:
		return new NormalMap();
	case CUSTOMS_MAP:
		return new CustomMaps();
	default:
		break;
	}
}
bool readWhloeMapVectorFromFile() {
	//wholeMapVector
	FILE* filePointer = nullptr;
	fopen_s(&filePointer, MAP_VECTOR_SAVE_PATH, READ_BINARY);
	if (filePointer == nullptr) {
		return false;
	}
	int mapCount = 0;
	//表示有几个地图
	fread(&mapCount, sizeof(int), 1, filePointer);
	for (int mapIndex = 0; mapIndex < mapCount; mapIndex++) {
		//这里存储地图的序列号信息描述和名字在映射表里面匹配
		int mapSerialNumber = 0;
		fread(&mapSerialNumber, sizeof(int), 1, filePointer);

		MapGo* mapgo = matchSpecificMap(mapSerialNumber);
		mapgo->mapSerialNumber = mapSerialNumber;

		mapgo->readMapFromFile(filePointer);
		wholeMapVector.push_back(mapgo);
	}
	fclose(filePointer);
	return true;
}



void saveFilledThingVectorToFile() {
	FILE* filePointer = nullptr;
	fopen_s(&filePointer, FILLING_THING_VECTOR_SAVE_PATH, WRITE_AND_READ_BINARY);
	int filledCount = filledThingVector.size();

	fwrite(&filledCount, sizeof(int), 1, filePointer);

	for (int index = 0; index < filledCount; index++) {
		fwrite(&filledThingVector[index]->filledThingSerialNumber, sizeof(int), 1, filePointer);
		filledThingVector[index]->saveToFile(filePointer);
	}

	fclose(filePointer);
}

FilledThing* matchSpecificFilledThing(int filledThingSerialNumber) {
	switch (filledThingSerialNumber){
	case NORMAL_FOOD:
		return new NormalFood();
	default:
		break;
	}

}

bool readFilledThingVectorToFile() {
	FILE* filePointer = nullptr;
	fopen_s(&filePointer, FILLING_THING_VECTOR_SAVE_PATH, READ_BINARY);
	int filledCount = 0;
	if (filePointer==nullptr) {
		return false;
	}
	fread(&filledCount, sizeof(int), 1, filePointer);

	for (int index = 0; index < filledCount; index++) {
		int filledThingSerialNumber = 0;
		fread(&filledThingSerialNumber, sizeof(int), 1, filePointer);

		FilledThing* filledThing = nullptr;
		filledThing = matchSpecificFilledThing(filledThingSerialNumber);
		filledThing->filledThingSerialNumber = filledThingSerialNumber;
		filledThing->readFromFile(filePointer);
		
		filledThingVector.push_back(filledThing);
	}

	fclose(filePointer);
	return true;
}

void GameReadLoad::gameSave(SnakeGo * snakeGo) {
	
	snakeGo->saveSnakeNodeVectorToFile();
	snakeGo->saveGameScore(WRITE_AND_READ_BINARY, GAME_SCORE_FOR_LOAD_PATH);

	saveWholeMapVectorToFile();

	saveFilledThingVectorToFile();
}

bool GameReadLoad::gameReadLoad(SnakeGo* snakeGo) {
	filledThingVector.clear();
	wholeMapVector.clear();
	bool readOk = readFilledThingVectorToFile();
	if (!readOk) {
		return false;
	}
	for (int filledThingIndex = 0; filledThingIndex < filledThingVector.size(); filledThingIndex++) {
		filledThingVector[filledThingIndex]->show();
	}
	bool readMapOk = readWhloeMapVectorFromFile();
	if (!readMapOk) {
		return false;
	}
	for (int mapIndex = 0; mapIndex < wholeMapVector.size(); mapIndex++) {
		wholeMapVector[mapIndex]->show();
	}
	bool readSnakeNodeOk = snakeGo->readSnakeNodeVectorFromFile();
	if (!readSnakeNodeOk) {
		return false;
	}
	bool loadGameScore = snakeGo->loadGameScore(READ_BINARY, GAME_SCORE_FOR_LOAD_PATH);
	if (!loadGameScore) {
		return false;
	}
}
void GameReadLoad::execute() {
	system("cls");
	filledThingVector.clear();
	wholeMapVector.clear();
	SnakeGo* snakeGo = new SnakeGo();
	bool gameReadLoadOk = gameReadLoad(snakeGo);
	if (!gameReadLoadOk) {
		return;
	}
	gameMusicEffectObj.playBackGroundMusic(MUSIC_MODE_GAMING);
	snakeGo->show();
	snakeGo->showGameScore();
	snakeGo->goGoGo();
	delete snakeGo;
}