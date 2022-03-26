#pragma once
#pragma execution_character_set("utf-8")

#include "./Menu.h"

class GameLevel:virtual public Menu{
public:
	int levelMode;
public:
	GameLevel();
	GameLevel(int levelMode);
	~GameLevel();
	void execute();
	int getLevelMode();
	
};

#define SIMPLE_LEVEL_MODE 1
#define HARD_LEVEL_MODE 2

#define GAME_LEVEL_FILE_PATH "C:\\workspace_cpp\\game_snake\\resource\\game_level.txt"