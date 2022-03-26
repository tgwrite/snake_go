#pragma once
#pragma execution_character_set("utf-8")
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include "./filled_thing/SnakeNode.h"
#include "./mapgo/MapGo.h"
#include "./filled_thing/FilledThing.h"

using std::vector;

#define INIT_SNAKE_LENGTH 3
//control direction define
#define LEFT 97
#define RIGHT 100
#define UP 119
#define DOWN 115

#define SAVE 1
// 119 w
// 97 a
// 115 s
// 100 d
class SnakeNode;

#define SNAKE_SPEED 150

class SnakeGo{
    public:
        vector<SnakeNode*> snakeNodePointerVector;
    private:
        int gameLevel=-1;
        int gameScore = -1;
        int snakeSpeed = SNAKE_SPEED;
    public:
        SnakeGo();
        ~SnakeGo();
        void init();
        void show();
        void goGoGo();
        bool scanDirectionFromKeyBoard(vector<SnakeNode*> snakeNodePointerVector);
        void saveSnakeNodeVectorToFile();
        bool readSnakeNodeVectorFromFile();
        int getGameLevel();
        int getGameScore();
        void setGameScore(int gameScore);
        void saveGameScore(std::string readWriteMode, std::string path);
        bool loadGameScore(std::string readWriteMode, std::string path);
        void showGameScore();
        int getSnakeSpeed();
        void setSnakeSpeed(int speed);
        int snakeSpeedUp(int gameScore);
};


#define GAME_SCORE_FILE_PATH "C:\\workspace_cpp\\game_snake\\resource\\game_score.txt"
#define GAME_SCORE_FOR_LOAD_PATH "C:\\workspace_cpp\\game_snake\\resource\\game_score_for_load.txt"

