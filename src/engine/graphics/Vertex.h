//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_VERTEX_H
#define TLOTK_VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 v;     // position
    glm::vec3 c;     // color
    glm::vec2 t;     // texture
    glm::vec3 n;     // normal

    Vertex(float vx, float vy, float vz, float cx, float cy, float cz)
    {
        this->v = glm::vec3(vx, vy, vz);
        this->c = glm::vec3(cx, cy, cz);
        this->t = glm::vec2(0.0f, 0.0f);
        this->n = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    Vertex(glm::vec3 p_v, glm::vec3 p_c)
    {
        this->v = p_v;
        this->c = p_c;
        this->t = glm::vec2(0.0f, 0.0f);
        this->n = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    Vertex(glm::vec3 p_v, glm::vec3 p_c, glm::vec2 p_t, glm::vec3 p_n)
    {
        this->v = p_v;
        this->c = p_c;
        this->t = p_t;
        this->n = p_n;
    }
};
#endif //TLOTK_VERTEX_H
