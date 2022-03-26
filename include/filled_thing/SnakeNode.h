#pragma once
#pragma execution_character_set("utf-8")
class SnakeNode{
    public:
        short currentX;
        short currentY;
        short nextX;
        short nextY;
    public:
        SnakeNode();
        ~SnakeNode();
};