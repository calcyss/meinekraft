#include <core/VertexArray.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &mVAO);
}
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mVAO);
}

template<> void VertexArray::createVertexPointer<glm::vec4>(uint32_t _index, uint32_t _stride, uint32_t _offset)
{
    glEnableVertexAttribArray(_index);
    glVertexAttribPointer(_index, 4, GL_FLOAT, GL_FALSE, _stride, (const void*)_offset);
}
template<> void VertexArray::createVertexPointer<glm::vec3>(uint32_t _index, uint32_t _stride, uint32_t _offset)
{
    glEnableVertexAttribArray(_index);
    glVertexAttribPointer(_index, 3, GL_FLOAT, GL_FALSE, _stride, (const void*)_offset);
}
template<> void VertexArray::createVertexPointer<glm::vec2>(uint32_t _index, uint32_t _stride, uint32_t _offset)
{
    glEnableVertexAttribArray(_index);
    glVertexAttribPointer(_index, 2, GL_FLOAT, GL_FALSE, _stride, (const void*)_offset);
}

void VertexArray::disableVertexPointer(uint32_t _index)
{
    glDisableVertexAttribArray(_index);
}

void VertexArray::bind()
{
    glBindVertexArray(mVAO);
}
void VertexArray::unbind()
{
    glBindVertexArray(0);
}