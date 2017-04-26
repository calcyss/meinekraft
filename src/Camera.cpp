#include <Camera.hpp>

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

Camera* Camera::sCurrent = 0;

Camera::Camera(glm::vec4 _position)
{
    mPosition = _position;
    mTarget = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
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
glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 view = glm::lookAt(glm::vec3(mPosition), glm::vec3(mTarget), glm::vec3(mUp));
    return view;
}
glm::mat4 Camera::getProjectionMatrix()
{
    glm::mat4 per = glm::perspective(45.0f, 1280.0f/720.0f, 0.0f, 1000.0f);
    return per;
}
void Camera::lookAt(glm::vec4 _point)
{
    mTarget = _point;
}
glm::vec4 Camera::getViewDirection()
{
    return glm::normalize(mTarget - mPosition);
}
void Camera::roll(float _radians)
{
    glm::mat4 rotm = glm::rotate(glm::mat4(1.0f), _radians, glm::vec3(glm::normalize(mTarget - mPosition)));
    mUp = glm::normalize(rotm * mUp);
}
void Camera::moveTo(glm::vec4 _position)
{
    mPosition = _position;
}
void Camera::moveBy(glm::vec4 _delta, bool _keepTarget)
{
    mPosition += _delta;
    if(!_keepTarget) mTarget += _delta;
}


