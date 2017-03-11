/*
 * Created by Timothy Blumberg on 05/03/17.
 *
 * AbLayers are the groups of GameObjects that can be rendered together with a unified Shader. A GO
 * will belong to only one AbLayer, and special behavior can be defined in a subclass. This AbLayer
 * will correctly set Uniforms and make sure any special calculations for the groups are kicked off.
 *
 * The general case is correctly implemented in AbLayer, that is updating all GO's and correctly setting
 * the uniforms necessary to provide basic lighting / temporal calculations on the GPU.
 */


#include "AbLayer.h"

AbLayer::AbLayer(const char *vertexShaderFilename, const char *fragmentShaderFilename, std::shared_ptr<Camera> _camera)
    : objects()
{
    this->shader = std::make_shared<Shader> (vertexShaderFilename, fragmentShaderFilename);
    this->camera = _camera;

    // Initialize Uniforms
    m_h             = shader->getShaderUniform("M");
    vp_h            = shader->getShaderUniform("VP");
    lightPos_h      = shader->getShaderUniform("lightPos");
    viewPos_h       = shader->getShaderUniform("viewPos");
    t_h             = glGetUniformLocation(shader->getShaderProgram(), "t");
//    texSample_h     = shader->getShaderUniform("tex");
}

AbLayer::AbLayer(std::shared_ptr<Shader> _shader, std::shared_ptr<Camera> _camera)
    : objects()
{
    this->shader = _shader;
    this->camera = _camera;
}

AbLayer::~AbLayer()
{
    // Shader needs to be disassembled
}

void AbLayer::bind() const
{
    shader->bind();
}

void AbLayer::unbind() const
{
    shader->unbind();
}

void AbLayer::addGameObject(GameObject *go)
{
    objects.push_back(go);
}

//
void AbLayer::render()
{
    // Update camera
    glm::mat4 vpMatrix = camera->getVPMatrix();

    // Set global uniforms


    for(GameObject* go : objects)
    {
        glUniformMatrix4fv(vp_h, 1, GL_FALSE, &vpMatrix[0][0]);
        camera->setViewPos(viewPos_h);
        glUniform3f(lightPos_h, 0, 0, 25 * (float) sin(GameState::get()->getGLFWTime()) + 30);
        glUniform1f(t_h, (float) GameState::get()->getGLFWTime());
//        glUniform1i(texSample_h, 0); // This just needs to be reset to 0 for every GO?

        // Render current GO
        go->setUniforms(m_h);
        go->render();
    }
}

void AbLayer::update()
{
    for(GameObject* go : objects)
    {
        go->update();
    }
}
