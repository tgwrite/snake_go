#include "../include/filled_thing/NormalFood.h"
#include "../include/mapgo/MapGo.h"
#include "../include/SnakeGo.h"
#include "../include/GameReadLoad.h"
#include "../include/GameMusicEffect.h"
#include <stdio.h>

extern void hideCursor();
extern GameMusicEffect gameMusicEffectObj;

extern void writeChar(short x, short y, const char * pStr,WORD color = 1 / 8);

NormalFood::NormalFood(){

}

NormalFood::~NormalFood(){

}

void NormalFood::init(){
    Coordinate * coordinate = this->generateRandomGoordinate(CONSOLE_WEIGHT, CONSOLE_HIGH);
    this->filledThingSerialNumber = NORMAL_FOOD;
    this->setCoordinate(*coordinate);
    delete coordinate;
}

void NormalFood::trigger(SnakeGo & snakeGo){
    //音效:
    gameMusicEffectObj.playBackGroundMusic(MUSIC_MODE_EAT_FOOD);
    //添加蛇身体的长度 ,更新坐标:
    SnakeNode * snakeNode = new SnakeNode();
    snakeNode->currentX = snakeGo.snakeNodePointerVector.at(snakeGo.snakeNodePointerVector.size()-1)->currentX;
    snakeNode->currentY = snakeGo.snakeNodePointerVector.at(snakeGo.snakeNodePointerVector.size()-1)->currentY;
    snakeGo.snakeNodePointerVector.push_back(snakeNode);
    //把当前食物符号抹去 打印空字符
    writeChar(this->getCurrentX(), this->getCurrentY(), " ");
    //碰到一个食物加10分
    snakeGo.setGameScore(snakeGo.getGameScore() + SCORE_FOR_ONE_FOOD);
    snakeGo.showGameScore();
}

void NormalFood::show() {
    writeChar(this->getCurrentX()
        , this->getCurrentY()
        , "$", BACKGROUND_RED);
}

void NormalFood::saveToFile(FILE* filePointer) {
    if (filePointer == 0) {
        return;
    }
	fwrite(this, sizeof(NormalFood), 1, filePointer);
}

void NormalFood::readFromFile(FILE* filePointer) {
    if (filePointer == nullptr) {
        return;
    }
	fread(this, sizeof(NormalFood), 1, filePointer);
}

