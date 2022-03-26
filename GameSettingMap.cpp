#include "./include/GameSettingMap.h"
#include "./include/SnakeGo.h"

extern int waitKey();
GameSettingMap::GameSettingMap(){

}

GameSettingMap::~GameSettingMap(){
   delete []name;
   name = nullptr;
}

void pen(FILE* filePointer)
{
    int x0, y0;
    //MOUSEMSG m;
    ExMessage m;// ���������Ϣ
    while (true)
    {
    flag:                //���ÿ�ʼ
        int hitKey = waitKey();
        if (hitKey!=0) {
            if (hitKey == 27) {
                break;
            }
        }
        m = getmessage(EM_MOUSE| EM_KEY);
        switch (m.message)

        {
        case WM_LBUTTONDOWN:
            x0 = m.x; y0 = m.y;    //����һ�ΰ���ʱ���õ����꣨x0,y0��
            while (true)
            { 
                        // ����������ͬʱ������ Ctrl ��
                if (m.ctrl) {
                    // ��һ���󷽿�
                    solidrectangle(m.x - 10*10, m.y - 10*15, m.x + 10*10, m.y + 10*15);
                    //���÷������������д���ļ�
                    for (int xIndex = m.x/10-10; xIndex < m.x/10 + 10; xIndex++) {
                        for (int yIndex = m.y/15 - 10; yIndex < m.y/15 + 10; yIndex++) {
                            if (xIndex <= 0 || xIndex >= CONSOLE_WEIGHT-1) {
                                continue;
                            }
                            if (yIndex <= 0 || yIndex >= CONSOLE_HIGH-1) {
                                continue;
                            }
                            fprintf_s(filePointer, "%d %d\n", xIndex, yIndex);
                        }
                    }
                               
                } else {
                    // ��һ��С����
                    solidrectangle(m.x - 5*10, m.y - 5*15, m.x + 5*10, m.y + 5*15);
                    for (int xIndex = m.x/10 - 5; xIndex < m.x/10 + 5; xIndex++) {
                        for (int yIndex = m.y/15 - 5; yIndex < m.y/15 + 5; yIndex++) {
                            if (xIndex <= 0 || xIndex >= CONSOLE_WEIGHT - 1) {
                                continue;
                            }
                            if (yIndex <= 0 || yIndex >= CONSOLE_HIGH - 1) {
                                continue;
                            }
                            fprintf_s(filePointer, "%d %d\n", xIndex, yIndex);
                        }
                    }                
                }   
                break;         
            }
            break;
        case WM_KEYDOWN:
            if (m.vkcode == VK_ESCAPE)
                return;	// �� ESC ���˳�����
        }
    }
}


void GameSettingMap::execute(){
  
    FILE* filePointer = NULL;
    fopen_s(&filePointer, PATH, WRITE_AND_READ_BINARY);

    if (filePointer == NULL) {
        printf("open file Failed!");
    }

    initgraph(CONSOLE_WEIGHT*10, CONSOLE_HIGH*15);
    setcolor(YELLOW);
    pen(filePointer);
    fclose(filePointer);
    closegraph();
  
    system("cls");
   
}
