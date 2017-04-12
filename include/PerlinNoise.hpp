#pragma once

#include <cstdint>

class PerlinNoise
{
public:
    PerlinNoise();
    ~PerlinNoise();

    void init(int32_t _seed);
    double noise(int32_t _x, int32_t _y);
private:
};