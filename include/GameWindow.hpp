#pragma once

#include <cstdint>
#include <string>

class GameWindow
{
public:
    GameWindow(int32_t _width, int32_t _height, std::string _title);
    ~GameWindow();

    static void update();

private:
};