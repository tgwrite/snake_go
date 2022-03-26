#pragma once
#pragma execution_character_set("utf-8")
#include "./Menu.h"
#include<stdio.h>
#include <graphics.h>
#include<conio.h>
#include <string.h>

#define READ "r"
#define WRITE "w"
#define PATH "C:\\workspace_cpp\\game_snake\\resource\\custom-draw-map.txt"

#define WRITE_AND_READ_BINARY "wb+"


class GameSettingMap:public virtual Menu{
    public:
        GameSettingMap();
        ~GameSettingMap();
        void execute();
};