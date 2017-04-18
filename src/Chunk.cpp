#include <Chunk.hpp>

#include <GL/glew.h>

Chunk::Chunk()
{
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mIBO);
    glGenVertexArrays(1, &mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    uint32_t block_bytesize = (6 * sizeof(glm::vec4)) * 6;
    uint32_t chunk_bytesize = (32 * 256 * 32) * block_bytesize;

    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)chunk_bytesize, NULL, GL_STATIC_DRAW);
    
}

Chunk::~Chunk()
{

}