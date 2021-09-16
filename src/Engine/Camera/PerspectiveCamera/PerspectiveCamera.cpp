#include "PerspectiveCamera.h"

#include <glm/gtx/transform.hpp>
#include <algorithm>

const int PI = 3.14159265358979323846;


PerspectiveCamera::PerspectiveCamera(double fov, double aspect, double near, double far):
    Camera(fov, aspect, near, far),
    m_phi(0.0), m_theta(0.0), m_orientation(),
    m_lateralDisplacement(), m_target(),
    m_sensivity(1)
{

}

PerspectiveCamera::~PerspectiveCamera() {
    
}




// orientates the camera's target point
void PerspectiveCamera::orientate(const glm::vec2& dir) {
    m_phi += std::clamp(-dir.y * m_sensivity, -89.0f, 89.0f);
    m_theta += -dir.x * m_sensivity;

    float phiRadian = m_phi * PI / 180;
    float thetaRadian = m_theta * PI / 180;

    // vertical axis = horizontal axis

    if(m_verticalAxis.x == 1.0f) {
        m_orientation.x = sin(phiRadian);
        m_orientation.y = cos(phiRadian) * cos(thetaRadian);
        m_orientation.z = cos(phiRadian) * sin(thetaRadian);
    }
    // Y axis
    else if(m_verticalAxis.y == 1.0f) {
        m_orientation.x = cos(phiRadian) * sin(thetaRadian);
        m_orientation.y = sin(phiRadian);
        m_orientation.z = cos(phiRadian) * cos(thetaRadian);
    }
    // Z axis
    else {
        m_orientation.x = cos(phiRadian) * cos(thetaRadian);
        m_orientation.y = cos(phiRadian) * sin(thetaRadian);
        m_orientation.z = sin(phiRadian);
    }

    m_orientation = glm::normalize(m_orientation);
    m_lateralDisplacement = glm::normalize(glm::cross(m_verticalAxis, m_orientation));
    m_target = m_orientation;

    updatelookAt();
}

// Defines the camera's target
void PerspectiveCamera::lookAt(const glm::vec3& target) {
    m_orientation = glm::normalize(target - m_position);

    if(m_verticalAxis.x == 1.0) {
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.y / cos(m_phi));

        if(m_orientation.y < 0)
            m_theta *= 1;
    }

    else if(m_verticalAxis.y == 1.0) {
        m_phi = asin(m_orientation.y);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0)
            m_theta *= -1;
    }

    else {
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0)
            m_theta *= -1;
    }

    m_phi *= 180 / PI;
    m_theta *= 180 / PI;

    updatelookAt();
}


// Set's the camera's look at. The view matrix will be upated in the loop
void PerspectiveCamera::lookAt(const glm::vec3 eye, const glm::vec3 center, const glm::vec3 up) {
    setPosition(eye);
    lookAt(center);
    m_verticalAxis = up;
    m_target = glm::normalize(center - eye);
    updatelookAt();
}


// Updates the view matrix. Normally called every update loop
void PerspectiveCamera::updatelookAt() {
    m_mvp.setView(glm::lookAt(m_position, m_position + m_target, m_verticalAxis));
}


void PerspectiveCamera::setPosition(const float x, const float y, const float z) {
    setPosition(glm::vec3(x, y, z));
}


// Defines the camera's position
void PerspectiveCamera::setPosition(const glm::vec3& position) {
    Object3D::setPosition(position);
    updatelookAt();
}




/* 
// TODO: user's work
// Updates the camera position and look
void Camera::update(const Input& input) {
    if(input.isMouseMoving())
		orientate(input.getMouseDir());

    if(input.isKeyDown(SDL_SCANCODE_W))
        m_position += m_orientation * m_speed;

    if(input.isKeyDown(SDL_SCANCODE_S))
        m_position -= m_orientation * m_speed;

    if(input.isKeyDown(SDL_SCANCODE_A)) {
        m_position += m_lateralDisplacement * m_speed;
        m_lateralDisplacement = glm::normalize(glm::cross(m_verticalAxis, m_orientation));
    }

    if(input.isKeyDown(SDL_SCANCODE_D)) {
        m_position -= m_lateralDisplacement * m_speed;
        m_lateralDisplacement = glm::normalize(glm::cross(m_verticalAxis, m_orientation));
    }

    if(input.isKeyDown(SDL_SCANCODE_SPACE))
		m_position += m_verticalAxis * m_speed;

    if(input.isKeyDown(SDL_SCANCODE_LCTRL))
		m_position -= m_verticalAxis * m_speed;

    m_target = m_orientation;
}


// moves the camera's position with given offset
void Camera::move(const glm::vec3 offset) {
    m_position += offset;
}


// moves the camera's vertical axis with given offset
void Camera::addUp(const glm::vec3 offset) {
    m_verticalAxis += offset;
}


// moves the camera's target with given offset
void Camera::addTarget(const glm::vec3 offset) {
    m_target += offset;
}


// moves the camera's position with given offset
void Camera::move(const float x, const float y, const float z) {
    m_position += glm::vec3(x, y, z);
}


// moves the camera's position with given offset
void Camera::move(const int x, const int y, const int z) {
    m_position += glm::vec3(x, y, z);
}


// moves the camera's vertical axis with given offset
void Camera::addUp(const float x, const float y, const float z) {
    m_verticalAxis += glm::vec3(x, y, z);
}

// moves the camera's vertical axis with given offset
void Camera::addUp(const int x, const int y, const int z) {
    m_verticalAxis += glm::vec3(x, y, z);
}


// moves the camera's target with given offset
void Camera::addTarget(const float x, const float y, const float z) {
    m_target += glm::vec3(x, y, z);
}


// moves the camera's target with given offset
void Camera::addTarget(const int x, const int y, const int z) {
    m_target += glm::vec3(x, y, z);
} */