#include "./MapGo.h"
#pragma execution_character_set("utf-8")

class NormalMap:virtual public MapGo, virtual public Menu{
    
    public:
        NormalMap();
        ~NormalMap();
        bool init();
        bool inLocalArea(Coordinate & coordinate);
        void putFilledThingInLocalArea(Coordinate * coordinate, int flag);
        void eraseFilledThingFromLocaleArea(Coordinate Coordinate);
        bool checkCoordinateScopeInLocale(Coordinate coordinate);
        void show();
        void execute();
        virtual void saveMapToFile(FILE* filePointer);
        virtual void readMapFromFile(FILE* filePointer);
};

