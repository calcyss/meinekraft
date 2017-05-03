#include <Chunk.hpp>

#include <Camera.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <algorithm>

std::string getInfoLog(int id)
{
    GLint infoLogLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

    GLchar *infoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(id, infoLogLength, NULL, infoLog);


    // Convert the info log to a string
    std::string infoLogString(infoLog);

    // Delete the char array version of the log
    delete[] infoLog;

    // Finally, return the string version of the info log
    return infoLogString;
}

bool Chunk::sInit = true;
std::vector<glm::vec3> Chunk::sBlockGeometry = std::vector<glm::vec3>();

Chunk::Chunk(glm::ivec2 _mapPosition)
{
    if(sInit)
    {
        //Front
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

        //Back
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 1.0f, -1.0f));

        //Top
        sBlockGeometry.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 1.0f, -1.0f));

        //Bottom
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, -1.0f));
        
        //Left
        sBlockGeometry.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

        //Right
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
        sBlockGeometry.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
    }

    mMapPosition = _mapPosition;
    mTransformation = glm::translate(glm::mat4(), glm::vec3(mMapPosition.x, 0.0f, mMapPosition.y));

    mBlocks = new int32_t**[16];
    for(int x = 0; x < 16; x++)
    {
        mBlocks[x] = new int32_t*[128];
        for(int y = 0; y < 128; y++)
        {
            mBlocks[x][y] = new int32_t[16];
            for(int z = 0; z < 16; z++)
            {
                mBlocks[x][y][z] = 0;
            }
        }
    }

    mShader.loadVertexShader("./shaders/chunk.vert.glsl");
    mShader.loadFragmentShader("./shaders/chunk.frag.glsl");
    mShader.link();

    mVAO.bind();
    mVertexBuffer.bind();
    mVAO.createVertexPointer<glm::vec3>((uint32_t)mShader.getAttributeLocation("vPosition"), 0, 0);
    mVertexBuffer.unbind();
    mVAO.unbind();
}

Chunk::~Chunk()
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 128; y++)
        {
            delete[] mBlocks[x][y];
        }
        delete[] mBlocks[x];
    }
    delete[] mBlocks;
}

void Chunk::update() {
    if (mChanged)
    {
        double msnow = glfwGetTime();
        mChanged = false;
        std::cout << "Chunk update. Updating chunk geometry." << std::endl;
        //Generate chunk data here, check for necessary blocks.
        std::vector<glm::vec3> chunk_geometry;
        for (int32_t y = 0; y < 128; y++) {
            for (int32_t z = 0; z < 16; z++) {
                for (int32_t x = 0; x < 16; x++) {
                    if (mBlocks[x][y][z] == 0) continue; //We dont have to check air blocks.
                    std::cout << "Found non air block." << std::endl;
                    std::vector<int32_t> neighbors = getNeighbors(x, y, z);
                    if (std::find(neighbors.begin(), neighbors.end(), 0) != neighbors.end()) //Block has an air block as neighbor --> VISIBLE/DRAW IT!
                    {
                        std::cout << "This block is visible!" << std::endl;
                        glm::vec3 block_offset = glm::vec3(x, y, -z);
                        std::cout << "Vertices of this block:" << std::endl << "---" << std::endl;
                        for (glm::vec3 block_vertex : sBlockGeometry)
                        {
                            glm::vec3 block_ver = block_offset + block_vertex;
                            std::cout << "glm::vec4(" << block_ver.x << ", " << block_ver.y << ", " << block_ver.z << ");" << std::endl;
                            chunk_geometry.push_back(block_ver);
                        }
                        std::cout << "---" << std::endl;
                    }
                }
            }
        }
        mVertexCount = chunk_geometry.size();

        std::cout << "Vertex count: " << chunk_geometry.size() << std::endl;
        mVertexBuffer.bind();
        mVertexBuffer.uploadData(chunk_geometry, StaticDraw);
        mVertexBuffer.unbind();

        double mslater = glfwGetTime();
        std::cout << "The chunk update process just took " << (mslater - msnow)*1000 << "ms!" << std::endl;
    }
}

std::vector<int32_t> Chunk::getNeighbors(int32_t _x, int32_t _y, int32_t _z)
{
    std::vector<int32_t> ret;
    if(_y +1 <= 127) ret.push_back(mBlocks[_x][_y +1][_z]);
    if(_y -1 >= 0) ret.push_back(mBlocks[_x][_y -1][_z]);
    if(_x +1 <= 15) ret.push_back(mBlocks[_x +1][_y][_z]);
    if(_x -1 >= 0) ret.push_back(mBlocks[_x -1][_y][_z]);
    if(_z +1 <= 15) ret.push_back(mBlocks[_x][_y][_z +1]);
    if(_z -1 >= 0) ret.push_back(mBlocks[_x][_y][_z -1]);
    return ret;
}

void Chunk::draw()
{
    Camera* cam = Camera::getCurrent();
    if(cam == 0)
    {
        std::cerr << "No current camera set! Cannot draw chunk!" << std::endl;
        return;
    }

    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 proj = cam->getProjectionMatrix();
    glm::mat4 mvp = proj * view * mTransformation;

    glm::vec4 vec(1.0f, 1.0f, 1.0f, 1.0f);
    vec = mvp * vec;
    std::cout << "vec(1.0f, 1.0f, 1.0f, 1.0f) after MVP: vec(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ");" << std::endl;

    mShader.use();
    mShader.uploadUniform("uMVP", mvp);
    mVAO.bind();
    mVAO.draw(0, mVertexCount);
    mVAO.unbind();
}

int32_t*** Chunk::getBlocksPointer()
{
    return mBlocks;
}
void Chunk::markChange()
{
    mChanged = true;
}
void Chunk::setBlock(int32_t _x, int32_t _y, int32_t _z, int32_t _block)
{
    mBlocks[_x][_y][_z] = _block;
    mChanged = true;
}