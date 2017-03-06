//
// Created by Timothy Blumberg on 28/02/17.
//

#ifndef TLOTK_MESH_H
#define TLOTK_MESH_H


#include "Model.h"

class Mesh : public Model
{
    public:
        static constexpr float MESH_SIZE = 10.0f;

        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
             const glm::vec3 &centerOffset);

        static Mesh* createMesh(const int xSize, const int ySize);

        void update() override;

    private:
        static int meshVertIndex(int x, int y, int height);
        static glm::vec3 calculateNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
};


#endif //TLOTK_MESH_H
