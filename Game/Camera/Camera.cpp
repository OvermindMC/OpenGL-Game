#include "Camera.h"
#include "../Game.h"

Camera::Camera(Game* game) : gamePtr(game), mMode(CameraMode::Spectate), mTarget(nullptr), mPos(0.f), mRot(0.0f) {
    //
};

Camera::~Camera() {
    //
};

Game* Camera::getGame() {
    return gamePtr;
};

CameraMode Camera::getMode() {
    return mMode;
};

void Camera::setMode(CameraMode mode, Entity* target) {
    mMode = mode;
    mTarget = (
        target && target->isAlive() ? target : nullptr
    );
};

void Camera::update(float deltaTime) {
    if(mMode == CameraMode::Attach) {
        if(mTarget && mTarget->isAlive()) {
            this->setPos(
                mTarget->getPos()
            );
            this->setRot(
                mTarget->getRot()
            );
        };
    };
};

void Camera::updateNorms() {
    float pitch = glm::radians(mRot.x);
    float yaw   = glm::radians(mRot.y);

    mFront = glm::normalize(glm::vec3(
        cos(pitch) * cos(yaw),
        sin(pitch),
        cos(pitch) * sin(yaw)
    ));

    mUp = glm::vec3(0.f, 1.f, 0.f);
};

glm::vec3 Camera::getPos() {
    return mPos;
};

void Camera::setPos(glm::vec3 newPos) {
    mPos = newPos;
    updateNorms();
};

glm::vec3 Camera::getFront() {
    return mFront;
};

glm::vec2 Camera::getRot() {
    return mRot;
};

void Camera::setRot(glm::vec2 newRot) {
    newRot.x = glm::clamp(newRot.x, -89.f, 89.f);
    
    if(newRot.y < 0.f)
        newRot.y += 360.f;
    else if(newRot.y >= 360.f)
        newRot.y -= 360.f;
    
    mRot = newRot;
    updateNorms();
};

float Camera::getFov() {
    return mFov;
};

void Camera::setFov(float fov) {
    mFov = fov;
};

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(mPos, mPos + mFront, mUp);
};

glm::mat4 Camera::getProjection() {
    float aspect = 1.f;

    if(auto vp = gamePtr->getViewport()) {
        aspect = static_cast<float>(vp[0]) / static_cast<float>(vp[1]);
    };

    return glm::perspective(glm::radians(mFov), aspect, 0.1f, 500.f);
};