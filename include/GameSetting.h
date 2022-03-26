#pragma once
#pragma execution_character_set("utf-8")
#include "./Menu.h"
class GameSetting:public virtual Menu{
    public:
        GameSetting();
        ~GameSetting();
        void execute();
};
