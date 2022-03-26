#pragma once
#pragma execution_character_set("utf-8")
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string>


using std::cout;

    //��հ�������������ֹ֮ǰ�Ĳ���������Ϊ��Ӱ��
inline   void kbhit_remove()
    {
        while (_kbhit())
            _getch();
    }
    //�ȴ���������ȡ���°����� ASC��
    inline   int kbhit_wait_getasc()
    {
        int num;
        do
        {
            num = _getch();
        } while (_kbhit());
        return num;
    }
    /*����ƶ�����
    * xΪ�����꣬yΪ������
    */
    inline void light_gotoxy(int x, int y)
    {
        COORD pos = { (short)x,(short)y };
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOut, pos);
        ShowCursor(false);//���ƹ����˸
    }


    /*��ȡ���λ��
    * ͬʱ��ȡxy����Ҫ������ܵ�xy��������
    * xΪ�����꣬yΪ������
    */
    inline void light_getxy(int& x, int& y)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
        ShowCursor(false);//���ƹ����˸
    }


    /*ѡ����
* ����ѡ���content_str[]��λ�ã�Ĭ��1��ʼ
* case_num:contentstr�������С��contentstr[]:ѡ������
* >֧��ƫ��<
*/
    template<typename T>
    int switch_case(int case_num, const T* content_str)
    {
        int nowi = 1, nowx, nowy;//nowi ��¼ѡ���ѡ����
        light_getxy(nowx, nowy);
        cout << "<--�������¼�ѡ�� | Enter��ȷ��-->";
        light_gotoxy(nowx, nowy + 1);
        const T* p = content_str;
        cout << ">>> " << *(p++);
        for (int i = 2; i <= case_num; ++i)  //�ȴ�ӡѡ������
        {
            light_gotoxy(nowx, nowy + i);
            cout << "    " << *(p++);
        }
        light_gotoxy(nowx, nowy + case_num + 1);
        kbhit_remove();//�����������
        for (int getnum;;) //�ȴ��������£�getnum��¼����asc
        {
            getnum = kbhit_wait_getasc();
            light_gotoxy(nowx, nowy + nowi); //�ƶ���ԭ���ı��ѡ��ǰ
            cout << "   ";  //���ǵ�����">>>"
            switch (getnum) //��ȡ���µİ�����ask2ֵ
            {
            case 72: //��
            {
                if (nowi > 1)   //�ڵ�һ���ٰ��ϼ��ᵽ���һ��
                    --nowi;
                else
                    nowi = case_num;
            }break;
            case 80: //��
            {
                if (nowi < case_num)  //�����һ�����¼��ᵽ��һ��
                    ++nowi;
                else
                    nowi = 1;
            }break;
            case 13:  //Enter��ȷ��
            {
                light_gotoxy(nowx, nowy + nowi);
                cout << "-->";
                light_gotoxy(nowx, nowy + case_num + 1);
                return nowi;  //���ص�ǰѡ����
            }break;
            }
            light_gotoxy(nowx, nowy + nowi);//�ƶ����޸ĺ��λ��
            cout << ">>>";
            light_gotoxy(nowx, nowy + case_num + 1); //�ѹ���ƶ�����������
        }
        return 0;
    }