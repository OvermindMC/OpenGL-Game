#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Game;
class Entity;

enum class CameraMode : char {
    Attach = 0,     // Follow Entity, Local Player, Other Player
    Spectate = 1    // Fly freely to spectate for debugging purposes
};

class Camera {
public:
    Camera(Game*);
    ~Camera();

    Game* getGame();

    CameraMode getMode();
    void setMode(CameraMode, Entity* = nullptr);

    void update(float);
    void updateNorms();

    glm::dvec3 getPos();
    void setPos(glm::dvec3);

    glm::vec3 getFront();

    glm::vec2 getRot();
    void setRot(glm::vec2);
    
    float getFov();
    void setFov(float);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjection();
private:
    Game* gamePtr;

    CameraMode mMode; Entity* mTarget;

    glm::dvec3 mPos;
    glm::dvec3 mFront, mUp;
    glm::dvec2 mRot;

    float mFov = 72.f;
};