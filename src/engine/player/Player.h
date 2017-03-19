//
// Created by Timothy Blumberg on 27/12/16.
//

#ifndef OPENGL_TEST1_PLAYER_H
#define OPENGL_TEST1_PLAYER_H

#include <array>

#include "../graphics/Window.h"
#include "../state/GameObject.h"

class Player : public GameObject
{
    public:
        static constexpr float PLAYER_SIZE      = 20.0f;
        static constexpr float THRUST           = 0.01f;
        static constexpr float SHIP_MASS        = 100.0f;
        static constexpr float SPEED_DECAY      = 0.985;
        static constexpr float FORWARD_COEF     = 1.0f;
        static constexpr float BACKWARD_COEF    = -0.5f;
#ifdef FAST_SHIP
        static constexpr float ROTATION_SPEED   = 0.1f;
        static constexpr float THRUSTER_POWER   = 1000.0f;
#else
        static constexpr float ROTATION_SPEED   = 0.1f;
        static constexpr float THRUSTER_POWER   = 1000.0f;
#endif


        Player(const float xPos, const float yPos, std::shared_ptr<Window> window);

        void update() override;
        Model* getModel();

        void setUniforms(GLint m_h) override;

        // Resource actions
//        void addResource(const ResourceBundle &other);
//        void removeResource(const ResourceBundle &other);

    private:
        Model *laser;

        std::shared_ptr<Window> mWindow;
        bool laserEngaged = false;

        // Player model methods
        void createModel();
        std::vector<Vertex> createPlayerVertices(float size);

        void powerThrusters(bool forward, float power);
        void engageLaser(bool engaged);

        // Physics
        glm::vec2 force;
        glm::vec2 acceleration;
        glm::vec2 velocity;

        glm::vec2 laserPositionOffset;

        // Light variables
        float lightCutoffAngle = 0.26f;
        float lightZAngle = -0.05f;
        float LIGHT_POS_Z = 46.0f;
        glm::vec3 lightPos;
        glm::vec3 lightColor;
        GLint lightPos_h;
        GLint lightAttenuation_h;
        GLint lightColor_h;
        GLint lightCutoffAngle_h;
        GLint lightDirection_h;
};


#endif //OPENGL_TEST1_PLAYER_H
