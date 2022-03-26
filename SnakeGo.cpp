#include "./include/SnakeGo.h"
#include "./include/filled_thing/SnakeNode.h"
#include "./include/filled_thing/FilledThing.h"
#include "./include/filled_thing/NormalFood.h"
#include "./include/mapgo/MapGo.h"
#include "./include/mapgo/NormalMap.h"
#include "./include/Coordinate.h"
#include "./include/GameExit.h"
#include "./include/GameReadLoad.h"
#include "./include/GameLevel.h"
#include "./include/GameScoreSort.h"
#include "./include/GameMusicEffect.h"


extern vector<StageProperty> stagePropertyVector;
extern vector<FilledThing*> filledThingVector;
extern GameMusicEffect gameMusicEffectObj;

SnakeGo::SnakeGo(){

}


SnakeGo::~SnakeGo(){
    snakeNodePointerVector.clear();
}

//隐藏光标防止闪烁
void hideCursor() {
	CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 1;
    cursor_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void writeChar(short x, short y, const char * pStr, WORD color = 1 / 8){
    COORD pos = {x, y};
    HANDLE hOutStd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutStd, pos);
    SetConsoleTextAttribute(hOutStd, color);
    printf("%s", pStr);
    hideCursor();
    //ShowCursor(false);//控制光标闪烁
}

/*
* #define CONSOLE_HIGH 50
#define CONSOLE_WEIGHT 135
*/
bool touchSideOrSelf(SnakeNode& snakeNode) {
    
    if (snakeNode.nextX == CONSOLE_WEIGHT-1 || snakeNode.nextX < 1
        || snakeNode.nextY == CONSOLE_HIGH-1 || snakeNode.nextY < 1) {
        return true;
    }
    Coordinate coordinate = Coordinate{ snakeNode.nextX, snakeNode.nextY };
    for (int index = 0; index < wholeMapVector.size(); index++) {
        //在正常地图模式中如果坐标存在地图中说明触碰到了自己的身体
        if (wholeMapVector[index]->mapSerialNumber == NORMAL_MAP) {
            bool isInLocalArea = wholeMapVector[index]->inLocalArea(coordinate);
            if (isInLocalArea) {
                return true;
            }
        }
        if (wholeMapVector[index]->mapSerialNumber == CUSTOMS_MAP) {
            //如果是障碍物地图，蛇的节点碰到了障碍物，则游戏结束 不在障碍物区域里面则游戏继续进行
            bool isInObstacleThing = wholeMapVector[index]->inLocalArea(coordinate);
            if (isInObstacleThing) {
                return true;
            }
        }
    }
    return false;
}

void putSnakeNodeToLocaleMap(Coordinate& coordinate, int flag){
    for(int index = 0; index < wholeMapVector.size(); index++){
        bool isInMapScope = wholeMapVector[index]->checkCoordinateScopeInLocale(coordinate);
        if (isInMapScope) {
            bool isInLocalArea = wholeMapVector[index]->inLocalArea(coordinate);
            if (!isInLocalArea) {
                wholeMapVector[index]->putFilledThingInLocalArea(&coordinate, 1);
                break;
            }
        }
    }
}

//随机生成蛇的身体不能碰到障碍物和地图边界以及自己 初始长度3
void SnakeGo::init(){
    this->snakeNodePointerVector = vector<SnakeNode *>();
    FilledThing filledThing = FilledThing();
    Coordinate* coordinate = filledThing.generateRandomGoordinate(CONSOLE_WEIGHT, CONSOLE_HIGH);

    for(int index = 0; index < INIT_SNAKE_LENGTH; index++){
     
        SnakeNode* snakeNode = new SnakeNode();
        snakeNode->currentX = coordinate->getX() + index;
        snakeNode->currentY = coordinate->getY();
        

        snakeNode->nextX = coordinate->getX()+index;
        snakeNode->nextY = coordinate->getY();

        if (index==0) {
            SnakeNode* snakeNodeTail = new SnakeNode();
            snakeNodeTail->nextX = coordinate->getX() + INIT_SNAKE_LENGTH - 1;
            snakeNodeTail->nextY = coordinate->getY();

            while (touchSideOrSelf(*snakeNode) || touchSideOrSelf(*snakeNodeTail)) {
                Coordinate* coordinateTemp = filledThing.generateRandomGoordinate(CONSOLE_WEIGHT, CONSOLE_HIGH);
                snakeNode->nextX = coordinateTemp->getX() + index;
                snakeNode->nextY = coordinateTemp->getY();

                snakeNodeTail->nextX = coordinateTemp->getX() + INIT_SNAKE_LENGTH - 1;
                snakeNodeTail->nextY = coordinateTemp->getY();

                delete coordinateTemp;
            } 
        }
        this->snakeNodePointerVector.push_back(snakeNode);
        Coordinate coor = Coordinate{snakeNode->currentX, snakeNode->currentY};
        putSnakeNodeToLocaleMap(coor, 1);
    }
    delete coordinate;
}

void SnakeGo::show(){
    for(int index = 0; index < this->snakeNodePointerVector.size(); index++){
      
        writeChar(this->snakeNodePointerVector[index]->currentX
            ,this->snakeNodePointerVector[index]->currentY
            , "A", FOREGROUND_GREEN);

    }
    //自身的分数区域:
    for (int index = 0; index < CONSOLE_WEIGHT; index++) {
        writeChar(index, 0, "X", FOREGROUND_BLUE);

        writeChar(index, CONSOLE_HIGH - 1 + 2, "X", FOREGROUND_BLUE);
    }
    for (int index = CONSOLE_HIGH; index < CONSOLE_HIGH + 2; index++) {
        writeChar(0, index, "X", FOREGROUND_BLUE);

        writeChar(CONSOLE_WEIGHT - 1, index, "X", FOREGROUND_BLUE);
    }
}

void SnakeGo::showGameScore() {
    //在分数区域显示 先擦除原来坐标位置上的分数 写入新的分数:
    //先擦除原来的分数:
    writeChar(CONSOLE_WEIGHT / 2 - 2
        , CONSOLE_HIGH
        , "            ");
    //在重新定位输出分数内容
    writeChar(CONSOLE_WEIGHT / 2 - 2
        , CONSOLE_HIGH
        , "", FOREGROUND_GREEN);
    std::string scoreStr = "SCORE: ";
    std::cout << scoreStr << this->getGameScore();
    hideCursor();
}

int waitKey(){
    if(_kbhit()){
        return _getch();
    }else{
        return 0;
    }
}
int reverseDirection(int hitKey) {
    switch (hitKey) {
    case UP:
        return DOWN;
        break;
    case DOWN:
        return UP;
        break;
    case LEFT:
        return RIGHT;
        break;
    case RIGHT:
        return LEFT;
        break;
    default:
        break;
    }
}
void matchDirection(int hitKey, SnakeNode * current){

    switch(hitKey){
        case UP:
            current->nextY = current->currentY -1;
            current->nextX = current->currentX;
            break;
        case DOWN:
            current->nextY = current->currentY + 1;
            current->nextX = current->currentX;
            break;
        case LEFT:
            current->nextY = current->currentY;
            current->nextX = current->currentX - 1;
            break;
        case RIGHT:
            current->nextY = current->currentY;
            current->nextX = current->currentX + 1;
            break;
        default:
            break;
    }
}

bool handleCoordinate(int hitKey, SnakeNode * current, SnakeNode * next, int gameLevel){
    int validKeyHit[3] = {0};
    

    int currentDirection = 0;

    if(current->currentX == next->currentX){
        if(current->currentY > next->currentY){
            validKeyHit[0] = DOWN;
            validKeyHit[1] = LEFT;
            validKeyHit[2] = RIGHT;
            
            currentDirection = DOWN;
        }else{
            validKeyHit[0] = UP;
            validKeyHit[1] = LEFT;
            validKeyHit[2] = RIGHT;
            
            currentDirection = UP;
        }
    }else{
        if(current->currentX > next->currentX){
            validKeyHit[0] = RIGHT;
            validKeyHit[1] = UP;
            validKeyHit[2] = DOWN;

            currentDirection = RIGHT;
        }else{
            validKeyHit[0] = LEFT;
            validKeyHit[1] = UP;
            validKeyHit[2] = DOWN;

            currentDirection = LEFT;
        }
    }

    if (HARD_LEVEL_MODE == gameLevel) {
        hitKey = reverseDirection(hitKey);
    }
    bool hitInValidKey = false;
    for(int index = 0; index < 3; index++){
        if(hitKey == validKeyHit[index]){
            hitInValidKey = true;
        }
    }
    if(!hitInValidKey){
        matchDirection(currentDirection, current);
        return false;
    }else{
        matchDirection(hitKey, current);
        return true;
    }
}

void SnakeGo::saveSnakeNodeVectorToFile() {
    FILE* filePointer = nullptr;
    fopen_s(&filePointer ,SNAKE_NODE_VECTOR_SAVE_PATH, WRITE_AND_READ_BINARY);

    int snakeNodeCount = this->snakeNodePointerVector.size();
    fwrite(&snakeNodeCount, sizeof(int), 1, filePointer);

    for (int index = 0; index < snakeNodeCount; index++) {
        fwrite(snakeNodePointerVector[index],sizeof(SnakeNode), 1, filePointer);
    }
    fclose(filePointer);
}

bool SnakeGo::readSnakeNodeVectorFromFile() {
    FILE* filePointer = nullptr;
    fopen_s(&filePointer, SNAKE_NODE_VECTOR_SAVE_PATH, READ_BINARY);
    if (filePointer == nullptr) {
        return false;
    }
    int snakeNodeCount = 0;
    fread(&snakeNodeCount, sizeof(int), 1, filePointer);

    for (int index = 0; index < snakeNodeCount; index++) {
        SnakeNode * snakeNode = new SnakeNode();
      
        fread(snakeNode, sizeof(SnakeNode), 1, filePointer);
        this->snakeNodePointerVector.push_back(snakeNode);
    }
    fclose(filePointer);
    return true;
}

bool SnakeGo::scanDirectionFromKeyBoard(vector<SnakeNode*> snakeNodePointerVector){
   int hitKey = waitKey();
   if (hitKey == 'p' || hitKey == 'P') {
     
       std::wstring title = TEXT("SNAKE GO!");
       MessageBoxW(nullptr, L"GAME PAUSE ENTER TO CONTINUE", title.c_str(), MB_SETFOREGROUND);
       //MessageBoxW(nullptr, TEXT("游戏暂停，按下回车键继续"), TEXT("贪吃蛇游戏"), MB_SETFOREGROUND);
   }
   if (hitKey == 27) {
       //用户存档
      int isSave = MessageBoxW(nullptr, L"Is to save?", L"SNAKE GO!", MB_OKCANCEL | MB_SETFOREGROUND);
      if (isSave == SAVE) {
          GameReadLoad gameReadLoad = GameReadLoad();
          gameReadLoad.gameSave(this);
      }
   }
   return handleCoordinate(hitKey, snakeNodePointerVector[0], snakeNodePointerVector[1], this->getGameLevel());
}


void randomSetFilledThing(){
    if(filledThingVector.size()==0){
        NormalFood * normalFood = new NormalFood();
        normalFood->init();

        SnakeNode sn = SnakeNode();
        sn.nextX= normalFood->getCurrentX();
        sn.nextY = normalFood->getCurrentY();

        bool isTouchSideOrSnake = touchSideOrSelf(sn);
        while (isTouchSideOrSnake) {
            normalFood->init();
            sn.nextX = normalFood->getCurrentX();
            sn.nextY = normalFood->getCurrentY();
            isTouchSideOrSnake = touchSideOrSelf(sn);
        }
        filledThingVector.push_back(normalFood);
        writeChar(normalFood->getCurrentX()
            , normalFood->getCurrentY()
            , "$", BACKGROUND_RED);
    }
}




void eraseFilledThing(Coordinate coordinate){
    for(int index = 0; index < wholeMapVector.size(); index++){
        bool isInLocalArea = wholeMapVector[index]->inLocalArea(coordinate);
        if(isInLocalArea){
            wholeMapVector[index]->eraseFilledThingFromLocaleArea(coordinate);
            break;
        }
    }
}



bool touchStageProperty(SnakeNode & snakeNode){
   if(filledThingVector.size()==0){
       return false;
   }
   if(filledThingVector[0]->getCurrentX() == snakeNode.nextX
      && filledThingVector[0]->getCurrentY() == snakeNode.nextY){
          return true;
   }
   return false;
}


int SnakeGo::getGameLevel() {
    if (this->gameLevel == -1) {
        GameLevel gameLevel = GameLevel();
        this->gameLevel = gameLevel.getLevelMode();
    }
    return this->gameLevel;
}

void SnakeGo::setGameScore(int gameScore) {
    this->gameScore = gameScore;
}

int SnakeGo::getGameScore() {
    if (this->gameScore==-1) {
        return 0;
    }
    return this->gameScore;
}

bool SnakeGo::loadGameScore(std::string fileReadMode, std::string path) {
    if (this->gameScore != -1) {
        return false;
    }
    FILE* filePointer = nullptr;
    fopen_s(&filePointer, path.c_str(), fileReadMode.c_str());
    if (filePointer == nullptr) {
        return false;
    }

    int score = 0;
    fread(&score, sizeof(int), 1, filePointer);
    this->gameScore = score;
    fclose(filePointer);
    return true;
}

int SnakeGo::snakeSpeedUp(int gameScore) {
    if (gameScore == 0) {
        return this->snakeSpeed;
    }
    
    return this->snakeSpeed - (gameScore / (SCORE_FOR_ONE_FOOD * 1)) * 15;
}

void SnakeGo::setSnakeSpeed(int speed) {
    this->snakeSpeed = speed;
}
int SnakeGo::getSnakeSpeed() {
    return this->snakeSpeed;
}

void SnakeGo::goGoGo() {

    
    while(true){
        int snakeSpeedMillisecond = snakeSpeedUp(this->getGameScore());
        Sleep(snakeSpeedMillisecond); //默认150毫秒 每5个食物减少15毫秒
        writeChar(this->snakeNodePointerVector.at(this->snakeNodePointerVector.size() - 1)->currentX
            , this->snakeNodePointerVector.at(this->snakeNodePointerVector.size() - 1)->currentY, " ");
        //输出填充障碍物:
        randomSetFilledThing();
        //这里使用键盘控制是给头节点的x还是y坐标+1
        //scanDirectionFromKeyBoard(snakeNodePointerVector[0], snakeNodePointerVector[1]);
        scanDirectionFromKeyBoard(snakeNodePointerVector);
        //判断头节点是否触碰到边界(1.地图的边界 2.自己的身体 3.障碍物 如果触碰到则游戏结束)
        bool isTouchSideOrSelf = touchSideOrSelf(*(this->snakeNodePointerVector[0]));
        if(isTouchSideOrSelf){
            //输出游戏结束:
            gameMusicEffectObj.playBackGroundMusic(MUSIC_MODE_GAME_OVER);
            writeChar(CONSOLE_WEIGHT/2-2, CONSOLE_HIGH/2-2, "GAME OVER!", FOREGROUND_GREEN);
            Sleep(2000);//这里画面停一下 等待 音效完成
            break;
        }
        //判断头节点是否触碰到障碍物(1.触碰到食物 把当前位置加到自身的头部 更新坐标) 
        bool isTouchStageProperty = touchStageProperty(*(snakeNodePointerVector[0]));
        if(isTouchStageProperty){
            filledThingVector[0]->trigger(*this);
            filledThingVector.clear();
        }
        for(int index = 0; index < this->snakeNodePointerVector.size(); index++){
            writeChar(snakeNodePointerVector[index]->nextX, snakeNodePointerVector[index]->nextY, "A", FOREGROUND_GREEN);
            if(index+1 != this->snakeNodePointerVector.size()){
                
                snakeNodePointerVector[index+1]->nextY = snakeNodePointerVector[index]->currentY;
                snakeNodePointerVector[index+1]->nextX = snakeNodePointerVector[index]->currentX;
            }
            //将尾节点从地图中删除
            if(index == this->snakeNodePointerVector.size()-1){
                eraseFilledThing(Coordinate(snakeNodePointerVector[index]->currentX,snakeNodePointerVector[index]->currentY));
            }
            snakeNodePointerVector[index]->currentX = snakeNodePointerVector[index]->nextX;
            snakeNodePointerVector[index]->currentY = snakeNodePointerVector[index]->nextY;
             //将节点添加到地图中
            Coordinate coordinateSnakeNode = Coordinate{snakeNodePointerVector[index]->currentX, snakeNodePointerVector[index]->currentY};
            putSnakeNodeToLocaleMap(coordinateSnakeNode, 1);
        }
    }

    if (this->gameScore>0) {
        this->saveGameScore(WRITE_ADD_TO_BINARY, GAME_SCORE_FILE_PATH);
        GameScoreSort gameScoreSort = GameScoreSort();
        gameScoreSort.handleGameScoreFileSortAndShow(false);
    }
}

void SnakeGo::saveGameScore(std::string readWriteMode, std::string path) {
    FILE* filePointer = nullptr;
    fopen_s(&filePointer, path.c_str(), readWriteMode.c_str());
    if (filePointer == nullptr) {
        return;
    }

    int score = this->gameScore;
    fwrite(&score, sizeof(int), 1, filePointer);
    fclose(filePointer);
}