//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_MODEL_H
#define TLOTK_MODEL_H

#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../state/IRenderable.h"
#include "Vertex.h"
#include "Shader.h"
#include "../state/IUpdatable.h"


class Model : public IRenderable, public IUpdatable
{
    protected:
        glm::vec2 direction = glm::vec2(1.0f, 0.0f);
        float rotation;
        glm::vec3 position;

    public:
        Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 centerOffset);
        ~Model();

        void easyDraw();      // binds, renders, then unbinds
        virtual void bind();
        virtual void draw();
        virtual void unbind();

        glm::mat4 &getModelMatrix();
        glm::vec3 getPosition();
        glm::vec2 getDirection();

        // Matrix Creation
        void regenModelMatrix();
        void regenRotationMatrix();
        void regenTranslationMatrix();

        // Translation
        void setPosition(float p_x, float p_y);
        void translatePosition(float xDelta, float yDelta);
        void translatePosition(glm::vec2 delta);
        void setZCoord(float p_z);

        // Rotation
        void setDirection(glm::vec2 directionVec);
        void setRotation(float newAngle);
        void initializeRotation(float initialAngle);
        void rotate(float angleDelta);

        void update() override;

    private:
        GLuint vao;
        GLuint vbo;
        GLuint ebo;
        unsigned long numElements;
        unsigned long numVertices;

        std::vector<Vertex> mVertices;

        // Model matrices
        glm::mat4 modelMatrix;
        glm::mat4 rotationMatrix;
        glm::mat4 translationMatrix;
        glm::vec3 centerOffset;
};


#endif //TLOTK_MODEL_H
