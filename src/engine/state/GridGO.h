//
// Created by Timothy Blumberg on 18/03/17.
//

#ifndef TLOTK_GRIDGO_H
#define TLOTK_GRIDGO_H

#include "GridSquare.h"
#include <queue>
#include <vector>
#include <glm/vec3.hpp>
#include "GameObject.h"

/*
 * GridGOs is the base class for any Objects that are aligned on Grids. This
 * includes asteroids and any ships that would be built.
 *
 * IMPORTANT: GridGO should never have a model associated with it.
 */
class GridSquare;

class GridGO : public GameObject
{
    public:
        GridGO(const float p_squareSize);
        ~GridGO();

        void addSquare(GridSquare gsquare);
        void addSquares(std::vector<GridSquare> gsquares);
        void clearSquares();
        GridSquare squareClosestTo(float x, float y);

        static GridGO createFromArray(std::vector<bool> vertices, int xDim, int yDim, float sSize, glm::vec3 pos);

        void update() override;
        void render() override;

    private:
        // Position used by all squares
        glm::vec3 basePos;
        float squareSize;

        std::vector<GridSquare> squares;
        std::vector<GridSquare> updateList;

        void addToUpdateList(GridSquare gsquare);

};


#endif //TLOTK_GRIDGO_H
