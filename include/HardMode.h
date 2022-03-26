#pragma once
#pragma execution_character_set("utf-8")

#include "./Menu.h"

class HardMode:public virtual Menu {
public:
	HardMode();
	~HardMode();
	void execute();
};