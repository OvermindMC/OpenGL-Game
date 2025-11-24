#pragma once

#include <glm/glm.hpp>

class Game;

class Entity {
public:
    Entity(Game*, float = 0.f);
    ~Entity() = default;

    Game* getGame();

    glm::dvec3 getPos();
    void setPos(glm::dvec3);

    glm::dvec3 getVelocity();
    void setVelocity(glm::dvec3);

    glm::dvec2 getRot();
    glm::dvec2 getRotTarget();

    void setRot(glm::dvec2);

    bool isAlive();

    virtual void update(float) {};
protected:
    Game* gamePtr;

    glm::dvec3 mPos, mVel;
    glm::dvec2 mRot, mRotTarget;

    bool mIsAlive = false, mWasAlive = false;
    float mHealth;
};