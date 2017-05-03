#include <Camera.hpp>

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

Camera* Camera::sCurrent = 0;

Camera::Camera(glm::vec3 _position)
{
    mPosition = _position;
    mTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
    glm::mat4 view = glm::lookAt(mPosition, mTarget, mUp);
    return view;
}
glm::mat4 Camera::getProjectionMatrix()
{
    glm::mat4 per = glm::perspective(glm::half_pi<float>(), 1280.0f/720.0f, 0.0f, 100.0f);
    return per;
}
void Camera::lookAt(glm::vec3 _point)
{
    mTarget = _point;
}
glm::vec3 Camera::getViewDirection()
{
    return glm::normalize(mTarget - mPosition);
}
void Camera::roll(float _radians)
{
    glm::mat3 rotm = glm::rotate(glm::mat4(1.0f), _radians, glm::vec3(glm::normalize(mTarget - mPosition)));
    mUp = glm::normalize(rotm * mUp);
}
void Camera::moveTo(glm::vec3 _position)
{
    mPosition = _position;
}
void Camera::moveBy(glm::vec3 _delta, bool _keepTarget)
{
    mPosition += _delta;
    if(!_keepTarget) mTarget += _delta;
}


