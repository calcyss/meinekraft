#include <Chunk.hpp>

#include <GL/glew.h>
#include <fstream>
#include <iostream>

Chunk::Chunk()
{
    glGenBuffers(1, &mVBO);
    glGenVertexArrays(1, &mVAO);

    mChanged = false;

    mVert = glCreateShader(GL_VERTEX_SHADER);
    mFrag = glCreateShader(GL_FRAGMENT_SHADER);
    mShader = glCreateProgram();

    std::ifstream vert_file("./shaders/chunk.vert.glsl");
    std::string vert_source, vert_line;
    const char* vert_source_c = vert_source.c_str();

    while(std::getline(vert_file, vert_line))
    {
        vert_source.append(vert_line + "\n");
    }
    vert_file.close();

    glShaderSource(mVert, 1, &vert_source_c, 0);
    glCompileShader(mVert);

    std::ifstream frag_file("./shaders/chunk.frag.glsl");
    std::string frag_source, frag_line;
    const char* frag_source_c = frag_source.c_str();

    while(std::getline(frag_file, frag_line))
    {
        vert_source.append(frag_line + "\n");
    }
    frag_file.close();

    glShaderSource(mFrag, 1, &frag_source_c, 0);
    glCompileShader(mFrag);

    glAttachShader(mShader, mVert);
    glAttachShader(mShader, mFrag);

    glLinkProgram(mShader);

    int32_t isLinked = 0;
    glGetProgramiv(mShader, GL_LINK_STATUS, (int32_t *)&isLinked);
    if(isLinked == GL_FALSE) std::cout << "Failed to link program!" << std::endl;

    glDetachShader(mShader, mVert);
    glDetachShader(mShader, mFrag);
    glDeleteShader(mVert);
    glDeleteShader(mFrag);
}

Chunk::~Chunk()
{
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteProgram(mShader);
}