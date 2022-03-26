#pragma once
#pragma execution_character_set("utf-8")
#include "./StageProperty.h"

class NormalFood:virtual public StageProperty{
    public:

    public:
        NormalFood();
        ~NormalFood();
        void init();
        void trigger(SnakeGo & snakeGo);
        void show();
        virtual void saveToFile(FILE* filePointer);
        virtual void readFromFile(FILE* filePointer);
};
#define SCORE_FOR_ONE_FOOD 10