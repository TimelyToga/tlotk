//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_SHADER_H
#define TLOTK_SHADER_H

#include <OpenGL/gl.h>
#include <string>
#include <iostream>
#include <vector>
#include "../utils/debug.h"

#include "../utils/utils.h"

#define FUCKED_UP_SHADER_COMPILATION -101
#define FUCKED_UP_SHADER_LINKING -104

class Shader
{
    public:
        static const GLuint POSITION_ATTR_INDEX  = 0;
        static const GLuint COLOR_ATTR_INDEX   = 1;
        static const GLuint TEXTURE_ATTR_INDEX = 2;
        static const GLuint NORMAL_ATTR_INDEX  = 3;


        Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename);

        // Engage for next draw call etc
        void bind() const;
        void unbind() const;
        GLuint getShaderProgram();

        GLint getShaderUniform(const GLchar* name);

    protected:
        virtual void getAttributeLocations(GLuint curProgram);

    private:
        GLuint m_Shader;

        const char* vertexFile;
        const char* fragmentFile;

        GLuint initializeShader();

        void checkShaderErrorMessage(GLuint shader);
};


#endif //TLOTK_SHADER_H
