#include "block.h"

Block::Block()
{
    cellsize = 30;
    rotation_state = 0;
    colors = GetCellColors();
    rowoffset = 0;
    columnoffset = 0;
}

void Block::Draw()
{
    std::vector<Position> tiles = GetCellPosistions();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellsize + 1, item.row * cellsize + 1, cellsize - 1, cellsize - 1, colors[id]);
    }
}

void Block::Move(int rows, int colums)
{
    rowoffset += rows;
    columnoffset += colums;
}

std::vector<Position> Block::GetCellPosistions()
{
    std::vector<Position> tiles = cells[rotation_state];
    std::vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowoffset, item.column + columnoffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotation_state ++;
    if(rotation_state == (int)cells.size())
    {
        rotation_state = 0;
    }
}

void Block::UndoRotation()
{
    rotation_state --;
    if(rotation_state == -1)
    {
        rotation_state = cells.size() - 1;
    }
}
