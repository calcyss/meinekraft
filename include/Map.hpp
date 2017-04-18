#pragma once

#include <vector>
#include <cstdint>
#include <string>

class Chunk;

class Map
{
public:
    Map();
    ~Map();

    void draw();
    void update();

    void load(std::string _filename);
    void save(std::string _filename);
private:
    std::vector<Chunk*> mChunks;
};