#pragma once

#include <glm/glm.hpp>

#include <string>
#include <cstdint>

class Shader
{
public:
    Shader();
    ~Shader();

    void loadVertexShader(std::string _filename);
    void loadFragmentShader(std::string _filename);
    void link();
    void use();

    int getUniformLocation(std::string _name);
    int getAttributeLocation(std::string _name);
    void uploadUniform(std::string _name, glm::mat4 _mat);
    void uploadUniform(std::string _name, int32_t _int);
    void uploadUniform(std::string _name, glm::vec4 _vec);
private:
    uint32_t mProgram, mVert, mFrag;
    bool mLinked, mVertLoaded, mFragLoaded;
};