#include <Chunk.hpp>

#include <Camera.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <fstream>
#include <vector>
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

Chunk::Chunk()
{
    //Front
    mBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

    //Back
    mBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mBlockGeometry.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

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
}

Chunk::~Chunk()
{
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteProgram(mShader);
}

void Chunk::update()
{
    if(mChanged)
    {
        mChanged = !mChanged;
        //Generate chunk data here, check for necessary blocks.
        std::vector<glm::ivec3> blocksToDraw;
        for(int32_t y = 0; y < 128; y++)
        {
            for(int32_t z = 0; z < 32; z++)
            {
                for(int32_t x = 0; x < 32; x++)
                {
                    if(mBlocks[x][y][z] == 0) continue; //We dont have to check air blocks.
                    std::vector<int32_t> neighbors = getNeighbors(x, y, z);
                    if(std::find(neighbors.begin(), neighbors.end(), 0) == neighbors.end())
                    {
                        blocksToDraw.push_back(glm::ivec3(x, y, z));
                    }
                }
            }
        }

        for(glm::ivec3 block : blocksToDraw)
        {

        }
    }
}
void Chunk::draw()
{
    glm::mat4 mvp(1.0f);

    Camera* cam = Camera::getCurrent();
    if(cam == 0)
    {
        std::cerr << "No current camera set! Cannot draw chunk!" << std::endl;
        return;
    }
    glm::mat4 vp = cam->getVPMatrix();
    mvp = vp * mTransformation;

    glUseProgram(mShader);
    glUniformMatrix4fv(glGetUniformLocation(mShader, "uMVP"), 1, GL_FALSE, glm::value_ptr(mvp));
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
    glBindVertexArray(0);
    glUseProgram(0);
}