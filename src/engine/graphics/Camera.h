//
// Created by Timothy Blumberg on 28/02/17.
//

#ifndef TLOTK_CAMERA_H
#define TLOTK_CAMERA_H

#include <iostream>
#include "math.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <OpenGL/gl3.h>


#include "../state/IUpdatable.h"

class Camera : public IUpdatable
{
    public:
        static constexpr float MIN_ZOOM = 0.10f;
        static constexpr float MAX_ZOOM = 2.69794e+09;
        static constexpr float MIN_ZCOORD = 10.0f;
        static constexpr float MAX_ZCOORD = 2.69794e+09;

        static constexpr float CAMERA_ZOOM_FACTOR = 0.005f;

        const float NEAR = -100.1f;
        const float FAR = 25.0f;
        static constexpr float STARTING_Z_COORD  = 80;

        // CC --> Camera Clench
        static constexpr float CC_ALPHA = 0.02f;
        static constexpr float CC_BETA = 0.045f;

        static constexpr float FOV = 120.f;


        Camera(float width, float height, float x, float y, float s_zoom);
        ~Camera();

        // Camera position
        glm::vec3 getPosition();
        void setPosition(glm::vec3 newPos);
        void translateCamera(float xDelta, float yDelta);

        // Camera zoom
        void setZoom(float newZoom);
        void relativeZoom(float percentage); // 1.0 == 100%
        float getZoom();

        // Camera type
        void useOrthoCamera();
        void usePerspectiveCamera();

        // Camera Matrices
        glm::mat4 getVPMatrix();
        glm::mat4& getPerspectiveMatrix();
        glm::mat4& getViewMatrix();

        void update() override;

        void handleMouseScroll(float offset);
        void setViewPos(GLint viewPos_h);

    private:
        float screenWidth;
        float screenHeight;
        float zoom;
        bool orthoCamera = false;

        glm::vec3 position;
        glm::mat4 perspectiveMatrix;
        glm::mat4 viewMatrix;


        // Generating Matrices
        void regenPerspectiveMatrix();
        void regenViewMatrix();

};


#endif //TLOTK_CAMERA_H
