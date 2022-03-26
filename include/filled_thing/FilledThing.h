#pragma once
#pragma execution_character_set("utf-8")
#include "../Coordinate.h"
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "../SnakeGo.h"

using std::vector;

class SnakeGo;

class FilledThing{
    public:
        Coordinate coordinate{0,0};
        int filledThingSerialNumber;
    public:
        virtual ~FilledThing();
        int getCurrentX();
        int getCurrentY();
        void setCoordinate(Coordinate coordinate);
        Coordinate getCoordinate();
        Coordinate * generateRandomGoordinate(int xLength, int yLength);
        virtual void trigger(SnakeGo & snakeGo){}
        virtual void saveToFile(FILE* filePointer) {}
        virtual void readFromFile(FILE* filePointer) {}
        virtual void show() {}
};

extern vector<FilledThing*> filledThingVector;
 




#define NORMAL_FOOD 0
#define SNAKE_NODE 1

class StageProperty :virtual public FilledThing {
public:
    char* name;
    char* describe;
  
public:
    virtual ~StageProperty() {}
    virtual void init() {}
    virtual void saveToFile(FILE* filePointer) {};
    virtual void readFromFile(FILE* filePointer) {};
    virtual void show() {}
};
extern vector<StageProperty> stagePropertyVector;


