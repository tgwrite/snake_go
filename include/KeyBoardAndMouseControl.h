#pragma once
#pragma execution_character_set("utf-8")
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string>


using std::cout;

    //清空按键缓冲区，防止之前的残留按键行为的影响
inline   void kbhit_remove()
    {
        while (_kbhit())
            _getch();
    }
    //等待按键并读取按下按键的 ASC码
    inline   int kbhit_wait_getasc()
    {
        int num;
        do
        {
            num = _getch();
        } while (_kbhit());
        return num;
    }
    /*光标移动函数
    * x为横坐标，y为纵坐标
    */
    inline void light_gotoxy(int x, int y)
    {
        COORD pos = { (short)x,(short)y };
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOut, pos);
        ShowCursor(false);//控制光标闪烁
    }


    /*获取光标位置
    * 同时获取xy，需要传入接受的xy变量引用
    * x为横坐标，y为纵坐标
    */
    inline void light_getxy(int& x, int& y)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
        ShowCursor(false);//控制光标闪烁
    }


    /*选择函数
* 返回选择的content_str[]的位置，默认1开始
* case_num:contentstr的数组大小；contentstr[]:选项内容
* >支持偏移<
*/
    template<typename T>
    int switch_case(int case_num, const T* content_str)
    {
        int nowi = 1, nowx, nowy;//nowi 记录选择的选项编号
        light_getxy(nowx, nowy);
        cout << "<--请用上下键选择 | Enter键确定-->";
        light_gotoxy(nowx, nowy + 1);
        const T* p = content_str;
        cout << ">>> " << *(p++);
        for (int i = 2; i <= case_num; ++i)  //先打印选项内容
        {
            light_gotoxy(nowx, nowy + i);
            cout << "    " << *(p++);
        }
        light_gotoxy(nowx, nowy + case_num + 1);
        kbhit_remove();//清除残留按键
        for (int getnum;;) //等待按键按下，getnum记录按键asc
        {
            getnum = kbhit_wait_getasc();
            light_gotoxy(nowx, nowy + nowi); //移动到原来的编号选项前
            cout << "   ";  //覆盖掉它的">>>"
            switch (getnum) //获取按下的按键的ask2值
            {
            case 72: //上
            {
                if (nowi > 1)   //在第一个再按上键会到最后一个
                    --nowi;
                else
                    nowi = case_num;
            }break;
            case 80: //下
            {
                if (nowi < case_num)  //在最后一个按下键会到第一个
                    ++nowi;
                else
                    nowi = 1;
            }break;
            case 13:  //Enter键确定
            {
                light_gotoxy(nowx, nowy + nowi);
                cout << "-->";
                light_gotoxy(nowx, nowy + case_num + 1);
                return nowi;  //返回当前选项编号
            }break;
            }
            light_gotoxy(nowx, nowy + nowi);//移动到修改后的位置
            cout << ">>>";
            light_gotoxy(nowx, nowy + case_num + 1); //把光标移动回输出的最后
        }
        return 0;
    }