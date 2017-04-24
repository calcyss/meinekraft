#pragma once

#include <cstdint>
#include <string>

class Handle;

class GameWindow
{
public:
    GameWindow(int32_t _width, int32_t _height, std::string _title);
    ~GameWindow();

    void show();
    void hide();
    void update();
    void swapBuffers();
    void resize(int32_t _width, int32_t _height);
    void setFullscreen(bool _fullscreen);
    void makeCurrent();
    bool getShouldClose();
    void setClearColor(float _r, float _g, float _b);
    void clear();
private:
    Handle* mHandle;
};