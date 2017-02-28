//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_MODEL_H
#define TLOTK_MODEL_H


#include <OpenGL/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <vector>
#include "../state/IRenderable.h"
#include "Vertex.h"
#include "Shader.h"


class Model : public IRenderable
{
    public:
        Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 centerOffset);
        ~Model();

        void easyDraw();      // binds, renders, then unbinds
        virtual void bind();
        virtual void draw();
        virtual void unbind();

    private:
        GLuint vao;
        GLuint vbo;
        GLuint ebo;
        unsigned long numElements;
        unsigned long numVertices;

        std::vector<Vertex> mVertices;
};


#endif //TLOTK_MODEL_H
