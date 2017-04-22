#pragma once

#include <cstdint>

#include <glm/glm.hpp>

class Block;

class Chunk
{
public:
    Chunk();
    ~Chunk();

    void draw();
    void update();

    glm::ivec2 getPosition();

    void setBlock(int32_t _x, int32_t _y, int32_t _block);
    void setBlocks(int32_t (&_blocks)[16][128][16]);
private:
    uint32_t mVAO, mVBO, mShader, mVert, mFrag;
    int32_t mBlocks[16][128][16];
    bool mChanged;

    glm::ivec2 mMapPosition;
    glm::mat4 mTransformation;
};