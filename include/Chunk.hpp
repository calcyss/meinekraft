#pragma once

#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

class Chunk
{
public:
    Chunk(glm::ivec2 _mapPosition);
    ~Chunk();

    void draw();
    void update();

    glm::ivec2 getPosition();

    int32_t*** getBlocksPointer();
    void setBlock(int32_t _x, int32_t _y, int32_t _block);
private:
    uint32_t mVAO, mVBO, mShader, mVert, mFrag;
    int32_t*** mBlocks;
    size_t mVertexCount;
    bool mChanged;

    static bool sInit;
    static std::vector<glm::vec4> sBlockGeometry;

    glm::ivec2 mMapPosition;
    glm::mat4 mTransformation;


    std::vector<int32_t> getNeighbors(int32_t _x, int32_t _y, int32_t _z);
};