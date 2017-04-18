#pragma once

#include <cstdint>
#include <array>

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
    void setBlocks(int32_t (&_blocks)[16][256][16]);
private:
    uint32_t mVAO, mVBO, mIBO, mShader, mVert, mFrag;
    glm::ivec2 mMapPosition;
    int32_t mBlocks[16][256][16];
    glm::mat4 mTransformation;


};