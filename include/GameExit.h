#pragma once
#pragma execution_character_set("utf-8")
#include "./Menu.h"

class GameExit:public virtual Menu {
public:
	GameExit();
	~GameExit();
	void execute();

};