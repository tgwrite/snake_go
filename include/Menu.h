#pragma once
#pragma execution_character_set("utf-8")
#pragma comment(lib, "winmm.lib")
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <codecvt>
#include <windows.h>
#include<mmsystem.h>

using std::vector;
#include "./MenuAssemble.h"
#include "./Show.h"

#define CONSOLE_HIGH 50
#define CONSOLE_WEIGHT 135

#define READ "r"
#define READ_BINARY "rb"
#define WRITE_BINARY "wb"
#define WRITE_AND_READ_BINARY "wb+"
#define WRITE_ADD_TO_BINARY "ab+"


class MenuAssemble;



class Menu:virtual public Show{
    public:
        char * name;
        vector<Menu *> nextLevelVector = vector<Menu *>();
        vector<Menu* > mainMenuEvector;
        bool selected = false;
    private:
        int menuSerialNumber;
    public:
        Menu(){}
        Menu(const char * name);
        virtual ~Menu();
        virtual void show(){
            std::cout << this->name << std::endl;            
        }
        virtual vector<Menu * > initMenu(MenuAssemble * menuAssemble){
            mainMenuEvector = menuAssemble->assembleMenu();
            return mainMenuEvector;
        }
        virtual void execute(){};
        void setMenuName(const char * name);
        void setSelected(bool selected);
        void setMenuSerialNumber(int serialNumber) {
            this->menuSerialNumber = serialNumber;
        };
        int getMenuSerialNumber() {
            return this->menuSerialNumber;
        }
};

