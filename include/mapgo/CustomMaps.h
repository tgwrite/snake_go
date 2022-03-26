#pragma once
#pragma execution_character_set("utf-8")
#include "./MapGo.h"



class CustomMaps :virtual public MapGo , virtual public Menu {
public:
public:
	CustomMaps();
	~CustomMaps();
    bool init();
    bool inLocalArea(Coordinate& coordinate);
    void putFilledThingInLocalArea(Coordinate* coordinate, int flag);
    void eraseFilledThingFromLocaleArea(Coordinate Coordinate);
    bool checkCoordinateScopeInLocale(Coordinate coordinate);
    void show();
    void execute();
    virtual void saveMapToFile(FILE* filePointer);
    virtual void readMapFromFile(FILE* filePointer);
};