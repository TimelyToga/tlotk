//
// Created by Timothy Blumberg on 18/03/17.
//

#include "GridGO.h"

GridGO::GridGO(const float p_squareSize)
    : updateList()
{
    this->squareSize = p_squareSize;
}

GridGO::~GridGO()
{
    // TODO: Make sure all GridSquares are torn down
}

void GridGO::render()
{
    for(GridSquare g : squares)
    {
        g.render();
    }
}

void GridGO::update()
{
    GameObject::update();

    while(!updateList.empty())
    {
        GridSquare curSquare = updateList.back();
        curSquare.update();
        updateList.pop_back();
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

GridGO GridGO::createFromArray(std::vector<bool> vertices, int xDim, int yDim, float sSize, glm::vec3 pos)
{
    GridGO owner(sSize);

    for(int x = 0; x < xDim; x++)
    {
        for(int y = 0; y < yDim; y++)
        {
            if(vertices[x + y * yDim])
            {
                GridSquare curSquare(x, y, &owner);
            }
        }
    }

    return owner;
}
