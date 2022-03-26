#include "./include/MenuAssemble.h"
#include "./include/GameStartMenu.h"
#include "./include/GameSetting.h"
#include "./include/GameSettingMap.h"
#include "./include/mapgo/NormalMap.h"
#include "./include/mapgo/CustomMaps.h"
#include "./include/GameReadLoad.h"
#include "./include/GameScoreSort.h"
#include "./include/GameExit.h"
#include "./include/tinystr.h"
#include "./include/tinyxml.h"
#include "./include/KeyBoardAndMouseControl.h"
#include "./include/HardMode.h"
#include "./include/GameLevel.h"
class AbstractMenu;

/**
#define START_GAME 1
#define GAME_SETTING 3
#define GAME_SETTING_MAP 301 
#define GAME_SETTING_MAP_SNOW 30101
 * 
 * @param serialNumber 
 * @return AbstractMenu* 
 */


extern void writeChar(short x, short y, const char* pStr, WORD color = 1 / 8);

int currentMenuLevelShowMenuAndSelected(vector<Menu* > & menuPointerVector) {
    system("cls");
    writeChar(CONSOLE_WEIGHT / 2 - 20, CONSOLE_HIGH / 2, "  ", 0xF);
    std::string str[10] = { "" };
    for (int flag = 0; flag < menuPointerVector.size(); flag++) {
        str[flag] = menuPointerVector[flag]->name;
    }
    int selected = switch_case(menuPointerVector.size(), str);
    return selected;
}

static Menu * match(long long serialNumber){
    switch (serialNumber)
    {
    case START_GAME:
        return new GameStartMenu();
        break;
    case GAME_SETTING:
        return new GameSetting();
        break;
    case GAME_SETTING_MAP:
        return new GameSettingMap();
        break;
    case GAME_READ_LOAD:
        return new GameReadLoad();
        break; 
    case GAME_SCORE_SORT:
        return new GameScoreSort();
    case GAME_EXIT:
        return new GameExit();
    case NORMAL_MAP_MODE: 
        return new NormalMap();
    case CUSTOM_MAP_MODE:
        return new CustomMaps();
    case HARD_MODE:
        return new GameLevel(HARD_LEVEL_MODE);
    case SIMPLE_MODE:
        return new GameLevel(SIMPLE_LEVEL_MODE);
    case GAME_LEVEL:
        return new GameLevel();
    default:
        return nullptr;
        break;
    }
}

static void assemble(TiXmlElement * rootElement,  vector<Menu *> & nextLevelVector){

    for(TiXmlElement* tmpElement = rootElement->FirstChildElement()
                ;tmpElement != NULL
                ; tmpElement = tmpElement->NextSiblingElement()){

        if( NULL != tmpElement->Value()){
            TiXmlAttribute * pAttr = tmpElement->FirstAttribute();
            Menu * menu = nullptr;
            while(NULL != pAttr){
                //用作菜单打印输出调试用
               // std::cout << pAttr->Name() << "=" << pAttr->Value() << ";";
                if(!strcmp("serialNumber", pAttr->Name()) ){
                   
                    menu = match(std::stoi(pAttr->Value()));
                    if(menu != nullptr){
                        menu->setMenuSerialNumber(std::stoi(pAttr->Value()));
                        nextLevelVector.push_back(menu);
                        if(NULL != tmpElement->FirstChild()){
                            assemble(tmpElement, menu->nextLevelVector);
                        }
                    }
                }
                if(!strcmp("name", pAttr->Name()) && menu != nullptr){
                            menu->setMenuName(pAttr->Value());
                }
                pAttr = pAttr->Next();
            }
        }
    }
}

static void xmlparse(vector<Menu *> & menuPointerVector){
    TiXmlDocument doc;
    bool loadOK = doc.LoadFile( "C:\\workspace_cpp\\game_snake\\resource\\MenuList.xml");
    if(loadOK){
        assemble(doc.RootElement(), menuPointerVector);
    }
}



vector<Menu *>  MenuAssemble::assembleMenu(){
    abstractMenuPointerVector = vector<Menu *>();
    xmlparse(abstractMenuPointerVector);   
    return abstractMenuPointerVector;
}

MenuAssemble::~MenuAssemble(){
    delete menuAssemble;
    menuAssemble = nullptr;
}
