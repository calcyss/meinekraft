#pragma once

#include <cstdint>
#include <glm/glm.hpp>

class Block
{
public:
    Block();
    virtual ~Block();

    int32_t getType();

    virtual void update();
private:
    int32_t mType;
};