#pragma once
#pragma execution_character_set("utf-8")
#include "./include/GameWelcome.h"

//show image below
/*

   _____ _   _____    __ __ ______   __________     __
  / ___// | / /   |  / //_// ____/  / ____/ __ \   / /
  \__ \/  |/ / /| | / ,<  / __/    / / __/ / / /  / /
 ___/ / /|  / ___ |/ /| |/ /___   / /_/ / /_/ /  /_/
/____/_/ |_/_/  |_/_/ |_/_____/   \____/\____/  (_)


*/
extern void hideCursor();
extern void writeChar(short x, short y, const char* pStr, WORD color = 1 / 8);

bool GameWelcome::show() {
	system("cls");

    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

    std::ifstream ifs(GAME_WELCOME_IMAGE_PATH);
    int lineFlag = 0;
    while (!ifs.eof())
    {
        std::string line;
        std::getline(ifs, line);
        std::wstring wb = conv.from_bytes(line);
        std::wcout.imbue(std::locale("chs"));			//更改区域设置 只为控制台输出显示
        writeChar(CONSOLE_WEIGHT / 2 - 27
            , CONSOLE_HIGH / 2 - 2 + lineFlag
            , "", FOREGROUND_GREEN);
        std::wcout << wb << std::endl;
        lineFlag++;
    }
    Sleep(3000);//展示三秒钟
    return true;
	
}