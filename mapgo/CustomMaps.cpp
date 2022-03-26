#pragma once
#pragma execution_character_set("utf-8")
#include "../include/mapgo/CustomMaps.h"
#include "../include/GameSettingMap.h"
#include "../include/SnakeGo.h"
#include "../include/mapgo/NormalMap.h"
#include "../include/GameMusicEffect.h"

extern void hideCursor();
extern class MapGo;
extern GameMusicEffect gameMusicEffectObj;
extern void writeChar(short x, short y, const char * pStr, WORD color = 1 / 8);
CustomMaps::CustomMaps() {
}

CustomMaps::~CustomMaps(){

}
bool CustomMaps::init() {
	//从文件中读取自定义地图坐标，并且将坐标放入该地图map容器中
    
    this->mapSerialNumber = CUSTOMS_MAP;
    FILE* filePointer = NULL;
    fopen_s(&filePointer, PATH, READ);

    if (filePointer==nullptr) {
        return false;
    }

    int endFlag = 1;
    for (; endFlag!=-1; ) {
        int X = 0;
        int Y = 0;
        endFlag = fscanf_s(filePointer, "%d %d\n", &X, &Y);
        Coordinate coordinate = Coordinate(X, Y);
        this->localeArea[coordinate] = 1;
    }
    Coordinate coordinateTemp = Coordinate(0, 0);
    localeArea.erase(coordinateTemp);
    fclose(filePointer);
    return true;
}

bool CustomMaps::inLocalArea(Coordinate& coordinate) {
    map<Coordinate, int>::iterator it;
    it = this->localeArea.find(coordinate);
    if (it == this->localeArea.end()) {
        return false;
    }
    return true;
}

void CustomMaps::putFilledThingInLocalArea(Coordinate* coordinate, int flag) {
    this->localeArea[*coordinate] = flag;
}

void CustomMaps::eraseFilledThingFromLocaleArea(Coordinate coordinate) {
    this->localeArea.erase(coordinate);
}

bool CustomMaps::checkCoordinateScopeInLocale(Coordinate coordinate) {
	return false;
}

void CustomMaps::show() {
    map<Coordinate, int>::iterator customapsIterator;
    for (customapsIterator = this->localeArea.begin(); customapsIterator != this->localeArea.end(); customapsIterator++) {
        Coordinate cod = customapsIterator->first;
        //Sleep(5);
        writeChar(cod.getX(), cod.getY(), "T", FOREGROUND_BLUE);
    }
}

void CustomMaps::saveMapToFile(FILE* filePointer) {
    //这里存储坐标map的元素个数：
    int localMapAreaCoordinateCount = this->localeArea.size();
    fwrite(&localMapAreaCoordinateCount, sizeof(int), 1, filePointer);
    //这里存储每一个坐标信息:
    std::map<Coordinate, int> abc = this->localeArea;
    map<Coordinate, int>::iterator mapsIterator;
    for (mapsIterator = this->localeArea.begin(); mapsIterator != this->localeArea.end(); mapsIterator++) {
        Coordinate cod = mapsIterator->first;
        fwrite(&cod, sizeof(Coordinate), 1, filePointer);
    }
}

void CustomMaps::readMapFromFile(FILE* filePointer) {
    int localMapAreaCoordinateCount = 0;
    fread(&localMapAreaCoordinateCount, sizeof(int), 1, filePointer);

    this->localeArea = std::map<Coordinate, int>();
    for (int index = 0; index < localMapAreaCoordinateCount; index++) {
        Coordinate* coordinate = new Coordinate();

        fread(coordinate, sizeof(Coordinate), 1, filePointer);
        this->localeArea[*coordinate] = 1;
    }
}

void CustomMaps::execute() {
    system("cls");
    wholeMapVector.clear();
    filledThingVector.clear();
    NormalMap normalMap = NormalMap();
    normalMap.init();
    this->localeArea.clear();
    bool mapInitOk = this->init();
    if (!mapInitOk) {
        return;
    }
    wholeMapVector.push_back(this);

    for (int mapIndex = 0; mapIndex < wholeMapVector.size(); mapIndex++) {
        wholeMapVector[mapIndex]->show();
    }
    gameMusicEffectObj.playBackGroundMusic(MUSIC_MODE_GAMING);
    // init snake
    SnakeGo* snakeGo = new SnakeGo();
    snakeGo->init();
    snakeGo->show();
    snakeGo->showGameScore();
    snakeGo->goGoGo();
    delete snakeGo;
}