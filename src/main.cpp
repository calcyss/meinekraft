#include <iostream>

#include <SimplexNoise.h>

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
}