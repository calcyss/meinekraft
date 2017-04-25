#include <iostream>
#include <string>

#include <GameWindow.hpp>
#include <Camera.hpp>
#include <Chunk.hpp>
#include <unistd.h>

/*
int main(int argc, char** argv)
{
    std::cout << "Simplex noise image:" << std::endl;
    SimplexNoise sn;
    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 20; x++)
        {
            std::cout << sn.noise(x, y) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Finished." << std::endl;
    return 0;
}*/

int main()
{
    GameWindow gw(1280, 720, "meinekraft");

    Chunk c(glm::ivec2(0, 0));

    Camera cam;
    cam.setCurrent();

    c.setBlock(0, 5, 5, 1);
    c.setBlock(1, 5, 5, 1);
    c.setBlock(2, 5, 5, 1);
    c.setBlock(3, 5, 4, 1);
    c.setBlock(3, 6, 4, 1);

    gw.makeCurrent();
    gw.show();

    while(!gw.getShouldClose())
    {
        usleep(16666);
        gw.update();
        gw.clear();

        c.update();
        c.draw();

        gw.swapBuffers();
    }

    return 0;
}