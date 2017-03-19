//
// Created by Timothy Blumberg on 28/02/17.
//

#ifndef TLOTK_MESH_H
#define TLOTK_MESH_H


#include "Model.h"
#include "../state/Square.h"
#include <vector>


class Mesh : public Model
{
    public:
        static constexpr float MESH_SIZE = 100.0f;

        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
             const glm::vec3 &centerOffset, const std::vector<Square> squares);

        static Mesh* createMesh(const int xSize, const int ySize);
        static Mesh* createMeshFromArray(const bool *objectDesign, const float squareSize,
                                         int gridX, int gridY, float xPos, float yPos, glm::vec3 color);

        void update() override;


        bool collideWithRay(glm::vec2 direction, glm::vec2 startingPoint, float maxRange);

    private:
        static int meshVertIndex(int x, int y, int height);
        static void createSquare(float xPos, float yPos, float zPos, glm::vec3 color, std::vector<Vertex> *vertices);
        static Resource generateResource();

        std::vector<Square> squares;
        float squareSize;
};


#endif //TLOTK_MESH_H
