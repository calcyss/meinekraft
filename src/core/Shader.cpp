#include <core/Shader.hpp>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

Shader::Shader()
{
    mProgram = glCreateProgram();
    mVert = glCreateShader(GL_VERTEX_SHADER);
    mFrag = glCreateShader(GL_FRAGMENT_SHADER);
    mVertLoaded = false;
    mFragLoaded = false;
}
Shader::~Shader()
{
    glDeleteShader(mVert);
    glDeleteShader(mFrag);
    glDeleteProgram(mProgram);
}

void Shader::loadVertexShader(std::string _filename)
{
    std::ifstream file(_filename);
    std::string content, line;
    while(std::getline(file, line))
    {
        content += line + "\n";
    }
    const char* source = content.c_str();

    glShaderSource(mVert, 1, &source, 0);
    glCompileShader(mVert);
    glAttachShader(mProgram, mVert);
    mVertLoaded = true;
}
void Shader::loadFragmentShader(std::string _filename)
{
    std::ifstream file(_filename);
    std::string content, line;
    while(std::getline(file, line))
    {
        content += line + "\n";
    }
    const char* source = content.c_str();

    glShaderSource(mFrag, 1, &source, 0);
    glCompileShader(mFrag);
    glAttachShader(mProgram, mFrag);
    mFragLoaded = true;
}
void Shader::link()
{
    if(mVertLoaded && mFragLoaded)
    {
        glLinkProgram(mProgram);
        glDetachShader(mProgram, mVert);
        glDetachShader(mProgram, mFrag);
        mLinked = true;
    }
}
void Shader::use()
{
    glUseProgram(mProgram);
}

int32_t Shader::getUniformLocation(std::string _name)
{
    return glGetUniformLocation(mProgram, _name.c_str());
}
int32_t Shader::getAttributeLocation(std::string _name)
{
    return glGetAttribLocation(mProgram, _name.c_str());
}
void Shader::uploadUniform(std::string _name, glm::mat4 _mat)
{
    glUniformMatrix4fv(glGetUniformLocation(mProgram, _name.c_str()), 1, GL_FALSE, glm::value_ptr(_mat));
}
void Shader::uploadUniform(std::string _name, int32_t _int)
{
    glUniform1i(glGetUniformLocation(mProgram, _name.c_str()), _int);
}
void Shader::uploadUniform(std::string _name, glm::vec4 _vec)
{
    glUniform4fv(glGetUniformLocation(mProgram, _name.c_str()), 1, glm::value_ptr(_vec));
}