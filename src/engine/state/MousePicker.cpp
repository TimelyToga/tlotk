//
// Created by Timothy Blumberg on 06/02/17.
//

#include "MousePicker.h"

MousePicker::MousePicker(std::shared_ptr<Window> p_window, std::shared_ptr<Camera> p_camera) :
    currentRay(0, 0, 0),
    mouseCoords(0, 0, 0)
{
    window = p_window;
    camera = p_camera;

    projectionMatrix = camera->getPerspectiveMatrix();
    viewMatrix = camera->getViewMatrix();
}

void MousePicker::update()
{
    // Camera may have moved since last frame
    viewMatrix = camera->getViewMatrix();

    recalculateCurRay();

    glm::vec3 surfaceNormal = glm::vec3(0, 0, -1);
    glm::vec3 objectPos = glm::vec3(0, 0, 0);
    float radius = 10;

    float t = glm::dot(objectPos - camera->getPosition(), surfaceNormal) / glm::dot(currentRay, surfaceNormal);

    glm::vec3 interPoint = camera->getPosition() + currentRay * t;

    glm::vec3 v = interPoint - objectPos;
    float d2 = dot(v, v);

    if(std::sqrt(d2) <= 100)
    {
        std::cout << "IN THE CIRLE" << std::endl;
    }

//    std::cout << "curRay: (" << currentRay.x << " , " << currentRay.y << " , " << currentRay.z << ") t: " << t << std::endl;
    std::cout << "interPoint: (" << interPoint.x << " , " << interPoint.y << " , " << interPoint.z << ") t: " << t << std::endl;

    mouseCoords = interPoint;
}

void MousePicker::recalculateCurRay()
{
    // Viewport space --> Normalized Device Space
    glm::vec2 normCoords = calcNormDeviceCoords(window->getMousePosition(), window->getWindowSize());
    glm::vec4 clipSpace = calcClipSpace(normCoords);
    glm::vec4 eyeSpace = calcEyeSpace(clipSpace);
    glm::vec4 worldSpace = calcWorldSpace(eyeSpace);

    currentRay = glm::vec3(worldSpace.x, worldSpace.y, worldSpace.z);
    currentRay = glm::normalize(currentRay);
}

glm::vec2 MousePicker::calcNormDeviceCoords(glm::vec2 mousePos, glm::vec2 screenSize)
{
    float normX = (2.0f * mousePos.x) / screenSize.x - 1.0f;
    float normY = 1.0f - (2.0f * mousePos.y) / screenSize.y;

    // Ensure the output is in the range [-1, 1]
    normX = std::min(std::max(-1.0f, normX), 1.0f);
    normY = std::min(std::max(-1.0f, normY), 1.0f);

    return glm::vec2(normX, normY);
}

glm::vec4 MousePicker::calcClipSpace(glm::vec2 normDeviceCoords)
{
    return glm::vec4(normDeviceCoords.x, normDeviceCoords.y, -1.0f, 0.0f);
}

glm::vec4 MousePicker::calcEyeSpace(glm::vec4 clipSpace)
{
    glm::vec4 eyeSpace = glm::inverse(projectionMatrix) * clipSpace;
    return glm::vec4(eyeSpace.x, eyeSpace.y, -1.0f, 0.0f);
}

glm::vec4 MousePicker::calcWorldSpace(glm::vec4 eyeSpace)
{
    return glm::inverse(viewMatrix) * eyeSpace;
}

Model* MousePicker::getSelected()
{
    return selectedRenderable;
}

glm::vec3 MousePicker::getMouseCoords()
{
    return mouseCoords;
}
