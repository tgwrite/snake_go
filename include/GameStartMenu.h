#pragma once
#pragma execution_character_set("utf-8")
#include "./Menu.h"
#include <windows.h>
#include <conio.h>


class GameStartMenu:public virtual Menu{
    public:
    public:
        GameStartMenu();
        ~GameStartMenu();
        void execute();
};