#pragma once

class MapGenerator; //Forward declaration.

class Map
{
public:
    Map();
    ~Map();
private:
    friend class MapGenerator;
};