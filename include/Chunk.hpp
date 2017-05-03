#pragma once

#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

#include <core/VertexBuffer.hpp>
#include <core/VertexArray.hpp>
#include <core/Shader.hpp>

class Chunk
{
public:
    Chunk(glm::ivec2 _mapPosition);
    ~Chunk();

    void draw();
    void update();

    glm::ivec2 getPosition();

    int32_t*** getBlocksPointer();
    void markChange();
    void setBlock(int32_t _x, int32_t _y, int32_t z, int32_t _block);
private:
    VertexBuffer mVertexBuffer;
    VertexArray mVAO;
    Shader mShader;
    int32_t*** mBlocks;
    size_t mVertexCount;
    bool mChanged;

    static bool sInit;
    static std::vector<glm::vec3> sBlockGeometry;

    glm::ivec2 mMapPosition;
    glm::mat4 mTransformation;


    std::vector<int32_t> getNeighbors(int32_t _x, int32_t _y, int32_t _z);
};