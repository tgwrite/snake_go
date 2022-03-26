#include "./include/Menu.h"

Menu::Menu(const char * name){
    int size = strlen(name) + 1;
    this->name = new char[size];
    strcpy_s(this->name,size, name);
}

Menu::~Menu(){
    
}

void Menu::setMenuName(const char * name){
    int size = strlen(name) + 1;
    this->name = new char[size];
    strcpy_s(this->name, size, name);
}

void Menu::setSelected(bool selected){
    this->selected = selected;
}