//
// Created by Timothy Blumberg on 05/03/17.
//

#ifndef TLOTK_ABLAYER_H
#define TLOTK_ABLAYER_H


#include "../state/GameObject.h"
#include "../state/GameState.h"
#include "Shader.h"
#include "Camera.h"

class AbLayer : public IUpdatable, public IRenderable
{
    public:
        AbLayer(const char *vertexShaderFilename, const char *fragmentShaderFilename,
                std::shared_ptr<Camera> _camera);
        AbLayer(std::shared_ptr<Shader> _shader, std::shared_ptr<Camera> _camera);
        ~AbLayer();

        void bind() const;
        void unbind() const;
        void addGameObject(GameObject* go);

        void render() override;
        void update() override;

    private:
        std::vector<GameObject*> objects;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Camera> camera;

        GLint vp_h;
        GLint m_h;
        GLint t_h;
        GLint lightPos_h;
        GLint viewPos_h;
        GLint texSample_h;

};


#endif //TLOTK_ABLAYER_H
