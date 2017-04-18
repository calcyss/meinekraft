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
    void setBlocks(int32_t &_blocks[32][256][32]);
private:
    uint32_t mVAO, mVBO, mIBO, mShader, mVert, mFrag;
    glm::ivec2 mMapPosition;
    int32_t mBlocks[32][256][32];


};