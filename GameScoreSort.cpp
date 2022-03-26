#pragma once
#pragma execution_character_set("utf-8")
#include "./include/GameScoreSort.h"
#include "./include/SnakeGo.h"


extern void hideCursor();

extern void writeChar(short x, short y, const char* pStr, WORD color = 1 / 8);

GameScoreSort::GameScoreSort() {
}

GameScoreSort::~GameScoreSort() {
	delete[]name;
	name = nullptr;
}

void GameScoreSort::execute() {
    handleGameScoreFileSortAndShow(true);
}

void GameScoreSort::handleGameScoreFileSortAndShow(bool isShow=false) {
    gameScoreVector.clear();
    //读取整个分数文件，进行排序然后 将文件内容重写  目的是为了防止分数文件过大
    FILE* filePointer = nullptr;
    fopen_s(&filePointer, GAME_SCORE_FILE_PATH, READ_BINARY);
    if (filePointer == nullptr) {
        return;
    }
    
    for (int flag = 1; flag != 0; ) {
        int score = 0;
        flag = fread(&score, sizeof(int), 1, filePointer);
        if (flag==0) {
            break;
        }
        this->gameScoreVector.push_back(score);
    }
    fclose(filePointer);
    std::sort(this->gameScoreVector.begin(), this->gameScoreVector.end(), greater<int>());

    fopen_s(&filePointer, GAME_SCORE_FILE_PATH, WRITE_AND_READ_BINARY);
    if (filePointer == nullptr) {
        return;
    }
    
    for (int index = 0; index < GAME_SCORE_TOP_COUNT_LIMIT && index<gameScoreVector.size(); index++) {
        int scoreTemp = gameScoreVector[index];
        fwrite(&scoreTemp, sizeof(int), 1, filePointer);
    }
    fclose(filePointer);

    //输出展示前五名 然后按任意键继续
    if (isShow) {
        this->show();
    }
}

void GameScoreSort::show() {
    system("cls");
    writeChar(CONSOLE_WEIGHT / 2 - 3
        , CONSOLE_HIGH/2 - 2
        , "", FOREGROUND_GREEN);
    std::cout << "HIGH SCORES TOP " << GAME_SCORE_TOP_COUNT_LIMIT;
    for (int index = 0; index < GAME_SCORE_TOP_COUNT_LIMIT && index < gameScoreVector.size(); index++) {
        //对x和y的运算主要是调整输出位置 在 HIGH SCORES TOP 5中间
        writeChar(CONSOLE_WEIGHT / 2 + 3
            , CONSOLE_HIGH / 2 + index
            , "", FOREGROUND_GREEN);
        std::cout << index + 1 << ". " << gameScoreVector[index];
    }
    writeChar(CONSOLE_WEIGHT / 2 - 9
        , CONSOLE_HIGH / 2 + 1 +GAME_SCORE_TOP_COUNT_LIMIT
        , "", FOREGROUND_GREEN);
    system("pause");
}