#pragma once
#pragma execution_character_set("utf-8")
#include "./tinystr.h"
#include "./tinyxml.h"
#include <string>

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <conio.h>

using std::vector;

class Menu;

class MenuAssemble{
    public:
        vector<Menu *> abstractMenuPointerVector;
    private:
        MenuAssemble * menuAssemble;
        MenuAssemble():menuAssemble(){}
    public:
       
        vector<Menu *> assembleMenu();

        static MenuAssemble * getMenuAssemble(){
                static MenuAssemble instance;
                return &instance;
        }
        ~MenuAssemble();
        COORD handleMouseMoveAndClick();
};

#define START_GAME 1
    #define NORMAL_MAP_MODE 101
    #define CUSTOM_MAP_MODE 102

#define GAME_READ_LOAD 2

#define GAME_SETTING 3
    #define GAME_LEVEL 305
        #define SIMPLE_MODE 30501
        #define HARD_MODE 30502

#define GAME_SCORE_SORT 4
#define GAME_EXIT 0




#define GAME_SETTING_MAP 301 
#define GAME_SETTING_MAP_SNOW 30101
