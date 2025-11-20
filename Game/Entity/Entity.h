#pragma once

#include <glm/glm.hpp>

class Game;

class Entity {
public:
    Entity(Game*, float = 0.f);
    ~Entity() = default;

    Game* getGame();

    glm::vec3 getPos();
    void setPos(glm::vec3);

    glm::vec3 getVelocity();
    void setVelocity(glm::vec3);

    glm::vec2 getRot();
    void setRot(glm::vec2);

    bool isAlive();

    virtual void update(float) {};
private:
    Game* gamePtr;

    glm::vec3 mPos, mVel;
    glm::vec2 mRot;

    bool mIsAlive = false, mWasAlive = false;
    float mHealth;
};