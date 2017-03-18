//
// Created by Timothy Blumberg on 18/03/17.
//

#include "GridGO.h"

GridGO::GridGO(const float p_squareSize)
{
    this->squareSize = p_squareSize;
}

GridGO::~GridGO()
{
    // TODO: Make sure all GridSquares are torn down
}

void GridGO::update()
{
    GameObject::update();

    while(!updateList.empty())
    {
        GridSquare curSquare = updateList.front();
        curSquare.update();
        updateList.pop_front();
    }
}

void GridGO::clearSquares()
{
    squares.clear();
}

void GridGO::addSquare(GridSquare gsquare)
{
    squares.push_back(gsquare);
}

void GridGO::addSquares(std::vector<GridSquare> gsquares)
{
    for(GridSquare g : gsquares)
    {
        squares.push_back(g);
    }
}

void GridGO::addToUpdateList(GridSquare gsquare)
{
    updateList.push_back(gsquare);
}

GridSquare GridGO::squareClosestTo(float x, float y)
{

    return GridSquare();
}
