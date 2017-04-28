#include <core/VertexBuffer.hpp>

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &mVBO);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &mVBO);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
}
void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::uploadData(uint32_t _size, void* _data, VertexBufferUsage _usage)
{
    bind();
    switch(_usage)
    {
        case StaticDraw:
            glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW);
            break;
        case DynamicDraw:
            glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_DYNAMIC_DRAW);
            break;
        case StreamDraw:
            glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_STREAM_DRAW);
            break;
        default:
            break;
    }
    unbind();
}
void VertexBuffer::uploadSubData(uint32_t _offset, uint32_t _size, void* _data)
{
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, _offset, _size, _data);
    unbind();
}
void VertexBuffer::uploadData(std::vector<glm::vec3> _data, VertexBufferUsage _usage)
{
    bind();
    switch(_usage)
    {
        case StaticDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _data.size(), glm::value_ptr(_data[0]), GL_STATIC_DRAW);
            break;
        case DynamicDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _data.size(), glm::value_ptr(_data[0]), GL_DYNAMIC_DRAW);
            break;
        case StreamDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _data.size(), glm::value_ptr(_data[0]), GL_STREAM_DRAW);
            break;
        default:
            break;
    }
    unbind();
}
void VertexBuffer::uploadData(std::vector<glm::vec4> _data, VertexBufferUsage _usage)
{
    bind();
    switch(_usage)
    {
        case StaticDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * _data.size(), glm::value_ptr(_data[0]), GL_STATIC_DRAW);
            break;
        case DynamicDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * _data.size(), glm::value_ptr(_data[0]), GL_DYNAMIC_DRAW);
            break;
        case StreamDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * _data.size(), glm::value_ptr(_data[0]), GL_STREAM_DRAW);
            break;
        default:
            break;
    }
    unbind();
}
void VertexBuffer::uploadData(std::vector<glm::vec2> _data, VertexBufferUsage _usage)
{
    bind();
    switch(_usage)
    {
        case StaticDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * _data.size(), glm::value_ptr(_data[0]), GL_STATIC_DRAW);
            break;
        case DynamicDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * _data.size(), glm::value_ptr(_data[0]), GL_DYNAMIC_DRAW);
            break;
        case StreamDraw:
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * _data.size(), glm::value_ptr(_data[0]), GL_STREAM_DRAW);
            break;
        default:
            break;
    }
    unbind();
}