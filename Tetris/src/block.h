#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
    Block();
    void Draw();
    void Move(int rows, int colums);
    std::vector<Position> GetCellPosistions();
    void Rotate();
    void UndoRotation();
    int id;
    std::map<int, std::vector<Position>> cells;

private:
    int cellsize;
    int rotation_state;
    std::vector<Color> colors;
    int rowoffset;
    int columnoffset;
};