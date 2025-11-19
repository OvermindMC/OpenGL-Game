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

    void update();

    glm::vec3 getPos();
    void setPos(glm::vec3);

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

    glm::vec3 mPos, mFront, mUp;
    glm::vec2 mRot;

    float mFov = 72.f;
};