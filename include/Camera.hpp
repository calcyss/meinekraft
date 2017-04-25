#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec4 _position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ~Camera();

    void moveTo(glm::vec4 _position);
    void moveBy(glm::vec4 _delta, bool _keepTarget = true);
    void lookAt(glm::vec4 _point);
    glm::vec4 getViewDirection();
    void roll(float _radians);
    void setCurrent();
    static Camera* getCurrent();
    glm::mat4 getVPMatrix();
private:
    glm::vec4 mPosition, mTarget, mUp;
    static Camera* sCurrent;
};