//
// Created by Timothy Blumberg on 26/02/17.
//

#include "Shader.h"

Shader::Shader(const char *vertexShaderFilename, const char *fragmentShaderFilename)
{
    this->vertexFile = vertexShaderFilename;
    this->fragmentFile = fragmentShaderFilename;

    m_Shader = initializeShader();
}

GLuint Shader::initializeShader()
{
    GLuint program          = glCreateProgram();

    GLuint vertexShader     = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader   = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexShaderContent = utils::loadFile(vertexFile);
    const char* vertexSrc = vertexShaderContent.c_str();

    glShaderSource(vertexShader, 1, &vertexSrc, NULL);

    glCompileShader(vertexShader);

    GLint vertCompSuccess;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertCompSuccess);
    if(vertCompSuccess == GL_FALSE)
    {
        checkShaderErrorMessage(vertexShader);
    }

    std::string fragmentShaderContent = utils::loadFile(fragmentFile);
    const char* fragmentSrc = fragmentShaderContent.c_str();

    glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);

    glCompileShader(fragmentShader);

    GLint fragCompSuccess;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragCompSuccess);
    if(fragCompSuccess == GL_FALSE)
    {
        checkShaderErrorMessage(fragmentShader);
    }

    // Attach the shaders
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Custom attributes locations
    getAttributeLocations(program);

    glLinkProgram(program);

    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);

        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        //Use the infoLog as you see fit.
        for (auto i = infoLog.begin(); i != infoLog.end(); ++i)
        {
            std::cout << *i << ' ';
        }

        //In this simple program, we'll just leave
        exit(FUCKED_UP_SHADER_LINKING);
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint Shader::getShaderProgram()
{
    return m_Shader;
}

GLint Shader::getShaderUniform(const GLchar* name)
{
    GLint location = glGetUniformLocation(m_Shader, name);
    if(location < 0)
    {
        #ifdef SHADER_UNIFORM_ERROR_PRINT
                std::cout << "ERROR: Can't find uniform " << name << " in shaders:\n"
                          << "location: " << location << "\n"
                          << "V: " << vertexFile << "\n"
                          << "F: " << fragmentFile << std::endl;
        #endif
    }

    return location;
}

void Shader::bind() const
{
    glUseProgram(m_Shader);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::getAttributeLocations(GLuint curProgram)
{
    // Specify attribute locations
    glBindAttribLocation(curProgram, POSITION_ATTR_INDEX,  "vertex_position_model_space");
    glBindAttribLocation(curProgram, COLOR_ATTR_INDEX,   "v_color");
    glBindAttribLocation(curProgram, TEXTURE_ATTR_INDEX, "tex_coord");
    glBindAttribLocation(curProgram, NORMAL_ATTR_INDEX,  "normal");
}

void Shader::checkShaderErrorMessage(GLuint shader)
{
    // How long is the error message?
    GLint logSize = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);

    // Allocate a buffer that size
    char* failureLog = new char[logSize];


    glGetShaderInfoLog(shader, logSize, NULL, failureLog);

    std::cout << "ERROR while compiling fragment shader " << fragmentFile
              << " with message: " << failureLog << std::endl;

    // Don't leak the shader
    glDeleteShader(shader);

    // TODO: Do something more useful than panic quitting?
    exit(FUCKED_UP_SHADER_COMPILATION);
}
