#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f));
    ~Camera();

    void moveTo(glm::vec3 _position);
    void moveBy(glm::vec3 _delta, bool _keepTarget = true);
    void lookAt(glm::vec3 _point);
    glm::vec3 getViewDirection();
    void roll(float _radians);
    void setCurrent();
    static Camera* getCurrent();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
private:
    glm::vec3 mPosition, mTarget, mUp;
    static Camera* sCurrent;
};