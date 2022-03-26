#pragma once
#pragma execution_character_set("utf-8")
#include "./include/GameLevel.h"

GameLevel::GameLevel() {
}

GameLevel::~GameLevel() {
}
GameLevel::GameLevel(int levelMode) :levelMode(levelMode) {
}


int GameLevel::getLevelMode() {
	FILE* filePointer = nullptr;
	fopen_s(&filePointer, GAME_LEVEL_FILE_PATH, READ_BINARY);
	if (filePointer == nullptr) {
		return -1;
	}

	int levelMode = this->levelMode;
	fread(&levelMode, sizeof(int), 1, filePointer);
	fclose(filePointer);
	return levelMode;
}

void GameLevel::execute() {
	//保存选择的模式:
	FILE* filePointer = nullptr;
	fopen_s(&filePointer, GAME_LEVEL_FILE_PATH, WRITE_AND_READ_BINARY);
	if (filePointer == nullptr) {
		return;
	}

	int levelMode = this->levelMode;
	fwrite(&levelMode, sizeof(int), 1, filePointer);

	fclose(filePointer);
}