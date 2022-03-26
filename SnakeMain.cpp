#include <stdio.h>
#include <stdlib.h>
#include "./include/MenuAssemble.h"
#include "./include/Menu.h"
#include "./include/SnakeGo.h"
#include "./include/KeyBoardAndMouseControl.h"
#include "./include/GameWelcome.h"
#include "./include/GameMusicEffect.h"

extern Coordinate messageLoop();

extern void hideCursor();

extern GameMusicEffect gameMusicEffectObj;

map<Coordinate, Menu *> menuLocalArea;

extern void writeChar(short x, short y, const char* pStr, WORD color = 1 / 8);
extern int currentMenuLevelShowMenuAndSelected(vector<Menu* >& menuPointerVector);

void controlFont() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 25;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = 700;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


void showMenu(vector<Menu *> & menuPointerVector){
    controlFont();
    for (int index = 0; index < menuPointerVector.size(); index++){
        
        writeChar(CONSOLE_WEIGHT / 2 - 20, CONSOLE_HIGH / 2 + index, menuPointerVector[index]->name, 0xF);
        //将菜单区域内对应的所有坐标放在map中，匹配对应的鼠标点击事件：
        for (int flag = 0; flag < strlen(menuPointerVector[index]->name); flag++) {
            Coordinate coordinate = Coordinate{ (CONSOLE_WEIGHT / 2 - 20)+flag , CONSOLE_HIGH/2 +index};
            menuLocalArea[coordinate] = menuPointerVector[index];
        }
        //将光标位置设置为此处，且文字背景为灰色表示当前选中的意思 回车表示确认执行
        writeChar(CONSOLE_WEIGHT / 2 - 20, CONSOLE_HIGH / 2 , menuPointerVector[0]->name, BACKGROUND_GREEN);
	}
}

int recursionExecuteMultipleMenuLevel(vector<Menu* >& menuPointerVector) {
    int selected = currentMenuLevelShowMenuAndSelected(menuPointerVector);
    if (menuPointerVector[selected - 1]->nextLevelVector.size()==0) {
        menuPointerVector[selected - 1]->execute();
        return selected;
    }else {
        return recursionExecuteMultipleMenuLevel(menuPointerVector[selected - 1]->nextLevelVector);
    }
}

int main(void){
    //设置控制台编码为utf-8格式:
    system("chcp 65001");
    system("cls");
    system("title tanchishe ");
    system("mode con cols=135 lines=103");
   
    //欢迎画面
    GameWelcome gameWelcomeObj = GameWelcome();
    gameWelcomeObj.show();
    Menu abstractMenu;
    MenuAssemble * menuAssemble = nullptr;
    MenuAssemble * mas = menuAssemble->getMenuAssemble();
    abstractMenu.initMenu(mas);
  
    while (true) {
        system("cls");
        //背景音乐:
        gameMusicEffectObj.playBackGroundMusic(MUSIC_MODE_MENU);
        int selected = recursionExecuteMultipleMenuLevel(abstractMenu.mainMenuEvector);
        if (abstractMenu.mainMenuEvector[selected - 1]->getMenuSerialNumber() == GAME_EXIT) {
            break;
        }
    }
    return 0;
}