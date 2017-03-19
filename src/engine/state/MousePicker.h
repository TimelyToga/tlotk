//
// Created by Timothy Blumberg on 06/02/17.
//

#ifndef OPENGL_TEST1_MOUSEPICKER_H
#define OPENGL_TEST1_MOUSEPICKER_H


#include "../graphics/Window.h"

class MousePicker: public IUpdatable
{
    public:
        MousePicker(graphics::Window *p_window, std::shared_ptr<graphics::Camera> p_camera);

        void update() override;

        Model* getSelected();

        glm::vec3 getMouseCoords();

    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::vec3 currentRay;

        Model *selectedRenderable;

        graphics::Window *window;
        std::shared_ptr<graphics::Camera> camera;

        // Calculating World Space MouseRay
        void recalculateCurRay();
        glm::vec2 calcNormDeviceCoords(glm::vec2 mousePos, glm::vec2 screenSize);
        glm::vec4 calcClipSpace(glm::vec2 normDeviceCoords);
        glm::vec4 calcEyeSpace(glm::vec4 clipSpace);
        glm::vec4 calcWorldSpace(glm::vec4 eyeSpace);

        // MouseRay intersection with World Plane
        glm::vec3 mouseCoords;
};


#endif //OPENGL_TEST1_MOUSEPICKER_H
