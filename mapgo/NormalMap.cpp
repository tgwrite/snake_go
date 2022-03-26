#include "../include/mapgo/NormalMap.h"
#include "../include/SnakeGo.h"
#include "../include/GameMusicEffect.h"

extern void hideCursor();

extern GameMusicEffect gameMusicEffectObj;
extern void writeChar(short x, short y, const char * pStr,WORD color = 1 / 8);

NormalMap::NormalMap(){

}

NormalMap::~NormalMap(){
    
}

bool NormalMap::init(){
    this->localeArea.clear();
    this->mapSerialNumber = NORMAL_MAP;
    this->setXLength(135);
    this->setYLength(50);
    Coordinate* coordinate = new Coordinate(0, 0);
    this->setCoordinate(*coordinate);
    wholeMapVector.push_back(this);
    return true;
}

bool NormalMap::inLocalArea(Coordinate & coordinate){
    map<Coordinate, int>::iterator it;
    it = this->localeArea.find(coordinate);
    if(it == this->localeArea.end()){
        return false;
    }
    return true;
}

void NormalMap::show() {
    for (int index = 0; index < this->getXLength(); index++) {
        writeChar(index, 0, "X", FOREGROUND_BLUE);
      
        writeChar(index, this->getYLength()-1, "X", FOREGROUND_BLUE);
        
    }
    for (int index = 0; index < this->getYLength(); index++) {
        writeChar(0, index, "X", FOREGROUND_BLUE);
       
        writeChar(this->getXLength()-1, index, "X", FOREGROUND_BLUE);
    }
}


void NormalMap::putFilledThingInLocalArea(Coordinate * coordinate , int flag){
    this->localeArea[*coordinate] = 1;
}

void NormalMap::eraseFilledThingFromLocaleArea(Coordinate coordinate){
    this->localeArea.erase(coordinate);
}

//如果复杂布局以及多边形需要重新设计逻辑
bool NormalMap::checkCoordinateScopeInLocale(Coordinate coordinate) {
    if (coordinate.getX()< this->getXLength() && coordinate.getY() < this->getYLength()) {
        return true;
    }
    return false;
}


void NormalMap::saveMapToFile(FILE* filePointer) {
    //这里存储坐标map的元素个数：
    int localMapAreaCoordinateCount = this->localeArea.size();
    fwrite(&localMapAreaCoordinateCount, sizeof(int), 1, filePointer);
    int xLength = this->getXLength();
    fwrite(&xLength, sizeof(int), 1, filePointer);
    int yLength = this->getYLength();
    fwrite(&yLength, sizeof(int), 1, filePointer);
   

    //这里存储每一个坐标信息:
    std::map<Coordinate, int> abc = this->localeArea;
    map<Coordinate, int>::iterator mapsIterator;
    for (mapsIterator = this->localeArea.begin(); mapsIterator != this->localeArea.end(); mapsIterator++) {
        Coordinate cod = mapsIterator->first;
        fwrite(&cod, sizeof(Coordinate), 1, filePointer);
    }

}
void NormalMap::readMapFromFile(FILE* filePointer) {

    int localMapAreaCoordinateCount = 0;
    fread(&localMapAreaCoordinateCount, sizeof(int), 1, filePointer);
    int xLength = 0;
    fread(&xLength, sizeof(int), 1, filePointer);
    this->setXLength(xLength);
    int yLength = 0;
    fread(&yLength, sizeof(int), 1, filePointer);
    this->setYLength(yLength);

    this->localeArea = std::map<Coordinate, int>();
    for (int index = 0; index < localMapAreaCoordinateCount; index++) {
        Coordinate* coordinate = new Coordinate();
        fread(coordinate, sizeof(Coordinate), 1, filePointer);
        this->localeArea[*coordinate] = 1;
    }
}

void NormalMap::execute() {
    system("cls");
    filledThingVector.clear();
    wholeMapVector.clear();
    this->init();
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
