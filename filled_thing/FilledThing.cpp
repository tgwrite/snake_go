#include "../include/filled_thing/FilledThing.h"

vector<FilledThing*> filledThingVector = vector<FilledThing*>();


vector<StageProperty> stagePropertyVector = vector<StageProperty>();


FilledThing::~FilledThing(){

}

int FilledThing::getCurrentX(){
    return this->coordinate.getX();
}

int FilledThing::getCurrentY(){
    return this->coordinate.getY();
}

void FilledThing::setCoordinate(Coordinate coordinate){
    this->coordinate = coordinate;
}
Coordinate FilledThing::getCoordinate(){
    return this->coordinate;
}

Coordinate * FilledThing::generateRandomGoordinate(int xLength, int yLength){
    srand((unsigned)time(NULL));
    int x = rand()%(xLength-2)+1; 
    int y = rand()%(yLength-2)+1;
    Coordinate * coordinate = new Coordinate(x, y);
    return coordinate;
}
