#include <Camera.hpp>

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

Camera* Camera::sCurrent = 0;

Camera::Camera(glm::vec4 _position = glm::vec4(1.0f))
{
    mPosition = _position;
    mLookat = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    mUp = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
Camera::~Camera()
{
    if(sCurrent == this) sCurrent = 0;
}

void Camera::setCurrent()
{
    sCurrent = this;
}
Camera* Camera::getCurrent()
{
    return sCurrent;
}
glm::mat4 Camera::getVPMatrix()
{
    glm::mat4 view = glm::lookAt(glm::vec3(mPosition), glm::vec3(mLookat), glm::vec3(mUp));
    float fovY = 2 * std::atan(std::tan(90.0f/2) * (720/1280.0f));
    glm::mat4 per = glm::perspective(fovY, 1280/720.0f, 0.0f, 1000.0f);
    return per * view;
}
void Camera::lookAt(glm::vec4 _point)
{
    mLookat = _point;
}
glm::vec4 Camera::getViewDirection()
{
    return glm::normalize(mLookat - mPosition);
}
void Camera::roll(float _radians)
{
    glm::mat4 rotm = glm::rotate(glm::mat4(1.0f), _radians, glm::vec3(glm::normalize(mLookat - mPosition)));
    mUp = glm::normalize(rotm * mUp);
}
void Camera::moveTo(glm::vec4 _position)
{
    mPosition = _position;
}
void Camera::moveBy(glm::vec4 _delta)
{
    mPosition += _delta;
}


