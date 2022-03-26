#include "../include/mapgo/MapGo.h"
#include "../include/mapgo/NormalMap.h"
#include "../include/Coordinate.h"
#include "../include/mapgo/CustomMaps.h"


vector<MapGo*> wholeMapVector;

MapGo::MapGo(){

}

MapGo::~MapGo(){

}

bool MapGo::init(){
    return true;
}

void MapGo::setCoordinate(Coordinate & coordinate){
    this->coordinate = coordinate;
}

Coordinate MapGo::getCoordinate(){
    return this->coordinate;
}

void MapGo::setXLength(int xLength){
    this->xLength = xLength;
}

int MapGo::getXLength(){
    return this->xLength;
}

void MapGo::setYLength(int yLength){
    this->yLength = yLength;
}

int MapGo::getYLength(){
    return this->yLength;
}

void MapGo::assembleMap(){
   
    


}
bool MapGo::inLocalArea(Coordinate & coordinate){
    return false;
}

void MapGo::putFilledThingInLocalArea(Coordinate * coordinate, int falg){

}

void MapGo::eraseFilledThingFromLocaleArea(Coordinate coordinate) {
}

bool MapGo::checkCoordinateScopeInLocale(Coordinate coordinate) {
    return false;
}

void MapGo::saveMapToFile(FILE* filePointer) {

}

void MapGo::readMapFromFile(FILE* filePointer) {
}