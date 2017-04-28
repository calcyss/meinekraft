#pragma once

#include <glm/glm.hpp>
#include <vector>

enum VertexBufferUsage
{
    StaticDraw = 0,
    DynamicDraw,
    StreamDraw
};

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void bind();
    void unbind();

    void uploadData(uint32_t _size, void* _data, VertexBufferUsage _usage);
    void uploadData(std::vector<glm::vec3> _data);
    void uploadData(std::vector<glm::vec4> _data);
    void uploadData(std::vector<glm::vec2> _data);
    void uploadSubData(uint32_t _offset, uint32_t _size, void* _data);
private:
    uint32_t mVBO;
};