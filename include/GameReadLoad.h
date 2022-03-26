#pragma once
#pragma execution_character_set("utf-8")
#include "./Menu.h"
#include "./SnakeGo.h"
#include <stdio.h>
#include <stdlib.h>





#define SNAKE_NODE_VECTOR_SAVE_PATH "C:\\workspace_cpp\\game_snake\\resource\\snakeNodeVector.txt"
#define MAP_VECTOR_SAVE_PATH "C:\\workspace_cpp\\game_snake\\resource\\mapVector.txt"
#define FILLING_THING_VECTOR_SAVE_PATH  "C:\\workspace_cpp\\game_snake\\resource\\fillingThingVector.txt"




class GameReadLoad:public virtual Menu {

public:
	GameReadLoad();
	~GameReadLoad();
	void execute();
	void gameSave(SnakeGo * snakeGo);
	bool gameReadLoad(SnakeGo* snakeGo);
};
