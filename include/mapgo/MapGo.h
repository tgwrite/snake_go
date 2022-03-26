#pragma once
#pragma execution_character_set("utf-8")
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include "../Coordinate.h"
#include "../GameStartMenu.h"
#include "../Show.h"
using std::vector;
using std::map;

#define NORMAL_MAP 0
#define CUSTOMS_MAP 1

class MapGo:virtual public Show{
    public:
        char * name;
        
        char * describe;
        int describeLength;
        int mapSerialNumber;
        
        map<Coordinate, int> localeArea;
    private:
        Coordinate coordinate{0,0};
        int xLength;
        int yLength;
    public:
        MapGo();
        virtual ~MapGo();
        virtual bool init();
        virtual bool inLocalArea(Coordinate & coordinate);
        virtual void setCoordinate(Coordinate & coordinate);
        Coordinate getCoordinate();
        virtual void setXLength(int xLength);
        virtual int getXLength();
        virtual void setYLength(int yLength);
        virtual int getYLength();
        virtual void assembleMap();
        virtual void putFilledThingInLocalArea(Coordinate * coordinate ,int flag);  
        virtual void eraseFilledThingFromLocaleArea(Coordinate Coordinate);
        virtual bool checkCoordinateScopeInLocale(Coordinate coordinate);
        virtual void saveMapToFile(FILE* filePointer);
        virtual void readMapFromFile(FILE* filePointer);
};
extern vector<MapGo*> wholeMapVector;

