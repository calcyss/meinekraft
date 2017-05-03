#include <core/VertexArray.hpp>
#include <core/VertexBuffer.hpp>
#include <core/Shader.hpp>

#include <Camera.hpp>
#include <GameWindow.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

int main()
{
    GameWindow gw(1280, 720, "meinekraft");
    gw.makeCurrent();

    Camera c;
    c.setCurrent();

    std::vector<glm::vec3> triangle_geometry;
    triangle_geometry.push_back(glm::vec3(0.5f, -0.5f, 0.0f));
    triangle_geometry.push_back(glm::vec3(-0.5f, -0.5f, 0.0f));
    triangle_geometry.push_back(glm::vec3(0.0f, 0.5f, 0.0f));

    VertexBuffer vb;
    vb.bind();
    vb.uploadData(triangle_geometry, StaticDraw);
    vb.unbind();

    Shader s;
    s.loadVertexShader("./shaders/chunk.vert.glsl");
    s.loadFragmentShader("./shaders/chunk.frag.glsl");
    s.link();

    VertexArray va;
    va.bind();
    vb.bind();
    va.createVertexPointer<glm::vec3>((uint32_t)s.getAttributeLocation("vPosition"), 0, 0);
    va.unbind();


    gw.show();

    glm::mat4 rot;
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(0.0, 0.0, -5.0));
    double last_time = 0.0;
    glfwSetTime(0.0);
    while(!gw.getShouldClose())
    {
        gw.update();
        gw.clear();

        double time_delta = glfwGetTime() - last_time;

        std::cout << "Time passed sicne last frame: " << time_delta << std::endl;

        float rot_angle = (float)(glm::half_pi<double>() * time_delta);

        last_time += time_delta;

        glm::mat4 proj = c.getProjectionMatrix();
        glm::mat4 view = c.getViewMatrix();

        std::cout << "Rotation angle: " << rot_angle << std::endl;

        rot = glm::rotate(rot, rot_angle, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 model = trans * rot;

        glm::mat4 mvp = proj * view * model;

        s.use();
        s.uploadUniform("uMVP", mvp);
        va.bind();
        va.draw(0, 3);
        va.unbind();

        gw.swapBuffers();
    }
}