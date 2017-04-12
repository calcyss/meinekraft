#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec4 _position = glm::vec4(0.0f));
    ~Camera();

    void moveTo(glm::vec4 _position);
    void moveBy(glm::vec4 _delta);
    void lookAt(glm::vec4 _point);
private:
    glm::mat4 mTransform;
};