#pragma once

#include <cstdint>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();
    void draw(uint32_t _begin, uint32_t _count);


    template<typename T> void createVertexPointer(uint32_t _index, uint32_t _stride, uint32_t _offset);
    void disableVertexPointer(uint32_t _index);
private:
    uint32_t mVAO;
};