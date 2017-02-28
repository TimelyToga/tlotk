//
// Created by Timothy Blumberg on 28/02/17.
//

#include "Camera.h"

Camera::Camera(float width, float height, float x, float y, float s_zoom)
{
    this->screenWidth = width;
    this->screenHeight = height;
    this->position = glm::vec3(x, y, STARTING_Z_COORD);
    this->zoom = s_zoom;

    regenPerspectiveMatrix();
    regenViewMatrix();
}

Camera::~Camera()
{

}

glm::vec3 Camera::getPosition()
{
    return glm::vec3();
}

void Camera::setPosition(glm::vec3 newPos)
{
    position = newPos;

    regenViewMatrix();
}

void Camera::translateCamera(float xDelta, float yDelta)
{
    position.x += xDelta;
    position.y += yDelta;

    regenViewMatrix();
}

void Camera::setZoom(float newZoom)
{
    zoom = newZoom;
    regenPerspectiveMatrix();
}

void Camera::relativeZoom(float percentage)
{
    // Don't let zoom become negative
    if(zoom < 0.0f){
        zoom *= -1.0f;
        return;
    }

    if(orthoCamera)
    {
        // Don't zoom if too zoomed in
        if(zoom <= MIN_ZOOM && percentage < 1) return;
        if(zoom >= MAX_ZOOM && percentage > 1) return;

        zoom *= percentage;
        std::cout << zoom << std::endl;
    } else {
        float tempVal = position.z * percentage;
        if(tempVal <= MIN_ZCOORD && percentage < 1) return;
        if(tempVal >= MAX_ZCOORD && percentage > 1) return;

        position.z = tempVal;

    #ifdef PRINT_CAMERA_ZCOORD
        std::cout << position.z << std::endl;
    #endif
    }

    regenPerspectiveMatrix();
}

float Camera::getZoom()
{
    return 0;
}

void Camera::useOrthoCamera()
{

}

void Camera::usePerspectiveCamera()
{

}

glm::mat4 Camera::getVPMatrix()
{
    return perspectiveMatrix * viewMatrix;
}

glm::mat4 &Camera::getPerspectiveMatrix()
{
    return perspectiveMatrix;
}

glm::mat4 &Camera::getViewMatrix()
{
    return viewMatrix;
}

void Camera::regenPerspectiveMatrix()
{
    if(orthoCamera)
    {
        perspectiveMatrix = glm::ortho(-(screenWidth / 2) * zoom,
                                       (screenWidth / 2) * zoom,
                                       -(screenHeight / 2) * zoom,
                                       (screenHeight / 2) * zoom,
                                       NEAR,
                                       FAR);
    } else
    {
        perspectiveMatrix = glm::perspectiveFov(FOV, screenWidth, screenHeight, NEAR, FAR);
    }
}

void Camera::regenViewMatrix()
{
    viewMatrix = glm::lookAt(
            glm::vec3(position.x, position.y, position.z), // Camera position in World Space
            glm::vec3(position.x, position.y, 0.0f), // Should look directly under its position
            glm::vec3(0.0f, -1.0f, 0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void Camera::update()
{
//    // Update position
//    glm::vec3 targetPosition = trackingObject->getPosition();
//
//    position += calcDeltaCameraPos(targetPosition);
    regenViewMatrix();
}
