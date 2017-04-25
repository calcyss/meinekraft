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
std::vector<glm::vec4> Chunk::sBlockGeometry = std::vector<glm::vec4>();

Chunk::Chunk(glm::ivec2 _mapPosition)
{
    if(sInit)
    {
        //Front
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

        //Back
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        //Top
        sBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        //Bottom
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

        //Left
        sBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

        //Right
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        sBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    }

    mMapPosition = _mapPosition;
    mTransformation = glm::translate(glm::mat4(1.0f), glm::vec3(mMapPosition.x, mMapPosition.y, 0.0f));

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

    glGenBuffers(1, &mVBO);
    glGenVertexArrays(1, &mVAO);

    mChanged = false;

    mVert = glCreateShader(GL_VERTEX_SHADER);
    mFrag = glCreateShader(GL_FRAGMENT_SHADER);
    mShader = glCreateProgram();

    std::ifstream vert_file("./shaders/chunk.vert.glsl");
    std::string vert_source, vert_line;

    while(std::getline(vert_file, vert_line))
    {
        vert_source.append(vert_line + "\n");
    }
    const char* vert_source_c = vert_source.c_str();

    vert_file.close();

    glShaderSource(mVert, 1, &vert_source_c, 0);
    glCompileShader(mVert);

    std::ifstream frag_file("./shaders/chunk.frag.glsl");
    std::string frag_source, frag_line;

    while(std::getline(frag_file, frag_line))
    {
        frag_source.append(frag_line + "\n");
    }
    const char* frag_source_c = frag_source.c_str();

    frag_file.close();

    glShaderSource(mFrag, 1, &frag_source_c, 0);
    glCompileShader(mFrag);

    /*
    std::cout << "Vert source: " << std::endl;
    std::cout << "--" << std::endl;
    std::cout << vert_source << std::endl;
    std::cout << "--" << std::endl;
    //std::cout << getInfoLog(mVert) << std::endl;
    //std::cout << "--" << std::endl;

    std::cout << "Frag source: " << std::endl;
    std::cout << "--" << std::endl;
    std::cout << frag_source << std::endl;
    std::cout << "--" << std::endl;
    //std::cout << getInfoLog(mFrag) << std::endl;
    //std::cout << "--" << std::endl;
     */

    glAttachShader(mShader, mVert);
    glAttachShader(mShader, mFrag);

    glLinkProgram(mShader);

    int32_t isLinked = 0;
    glGetProgramiv(mShader, GL_LINK_STATUS, (int32_t *)&isLinked);
    if(isLinked == GL_FALSE) std::cout << "Failed to link program!" << std::endl;

    glDetachShader(mShader, mVert);
    glDetachShader(mShader, mFrag);
    glDeleteShader(mVert);
    glDeleteShader(mFrag);


    GLuint attribloc = (GLuint)glGetAttribLocation(mShader, "vPosition");
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glEnableVertexAttribArray(attribloc);
    glVertexAttribPointer(attribloc, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);

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

    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteProgram(mShader);
}

void Chunk::update() {
    if (mChanged)
    {
        double msnow = glfwGetTime();
        mChanged = false;
        std::cout << "Chunk update. Updating chunk geometry." << std::endl;
        //Generate chunk data here, check for necessary blocks.
        std::vector<glm::vec4> chunk_geometry;
        for (int32_t y = 0; y < 128; y++) {
            for (int32_t z = 0; z < 16; z++) {
                for (int32_t x = 0; x < 16; x++) {
                    if (mBlocks[x][y][z] == 0) continue; //We dont have to check air blocks.
                    std::cout << "Found non air block." << std::endl;
                    std::vector<int32_t> neighbors = getNeighbors(x, y, z);
                    if (std::find(neighbors.begin(), neighbors.end(), 0) != neighbors.end()) //Block has an air block as neighbor --> VISIBLE/DRAW IT!
                    {
                        std::cout << "This block is visible!" << std::endl;
                        glm::vec4 block_offset = glm::vec4(x, y, z, 1.0f);
                        for (glm::vec4 block_vertex : sBlockGeometry)
                        {
                            chunk_geometry.push_back(block_offset + block_vertex);
                        }
                    }
                }
            }
        }
        mVertexCount = chunk_geometry.size();

        std::cout << "Vertex count: " << chunk_geometry.size() << std::endl;

        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * chunk_geometry.size(), glm::value_ptr(chunk_geometry[0]), GL_STATIC_DRAW);
        GLint size = 0;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        std::cout << "Successfully updated vertex buffer. Size: " << size << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        double mslater = glfwGetTime();
        std::cout << "The chunk update process just took " << mslater - msnow << "ms!" << std::endl;
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

    glm::mat4 vp = cam->getVPMatrix();
    glm::mat4 mvp = vp * mTransformation;

    glUseProgram(mShader);
    glUniformMatrix4fv(glGetUniformLocation(mShader, "uMVP"), 1, GL_FALSE, glm::value_ptr(mvp));
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
    glBindVertexArray(0);
    glUseProgram(0);
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