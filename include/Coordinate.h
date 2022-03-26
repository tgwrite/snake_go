#pragma once
#pragma execution_character_set("utf-8")
#include <map>
using namespace std;


class Coordinate{
    private:
        int X;
        int Y;
    public:
        Coordinate(int X, int Y):X(X), Y(Y){

        }
        Coordinate() {};
        void setX(int X);
        void setY(int Y);
        int getX();
        int getY();
    bool  operator < ( const Coordinate &c1)  const 
    { 
        if (this->X< c1.X) {
            return true;
        }if (this->X == c1.X) {
            if (this->Y < c1.Y) {
                return true;
            }
        }
        return false;
    }
};