#pragma once
#pragma execution_character_set("utf-8")
#include "./include/GameExit.h"

GameExit::GameExit() {
}

GameExit::~GameExit() {
	delete[]name;
	name = nullptr;
}

void GameExit::execute() {

}