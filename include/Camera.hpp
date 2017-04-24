#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec4 _position);
    ~Camera();

    void moveTo(glm::vec4 _position);
    void moveBy(glm::vec4 _delta);
    void lookAt(glm::vec4 _point);
    glm::vec4 getViewDirection();
    void roll(float _radians);
    void setCurrent();
    static Camera* getCurrent();
    glm::mat4 getVPMatrix();
private:
    glm::vec4 mPosition, mLookat, mUp;
    static Camera* sCurrent;
};