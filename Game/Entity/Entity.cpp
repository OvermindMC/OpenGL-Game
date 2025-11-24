#include "Entity.h"

Entity::Entity(Game* game, float health) : gamePtr(game), mPos(0.f), mVel(0.f), mRot(0.f), mHealth(health), mIsAlive(health > 0.f), mWasAlive(health > 0.f) {
    //
};

Game* Entity::getGame() {
    return gamePtr;
};

glm::dvec3 Entity::getPos() {
    return mPos;
};

void Entity::setPos(glm::dvec3 newPos) {
    mPos = newPos;
};

glm::dvec3 Entity::getVelocity() {
    return mVel;
};

void Entity::setVelocity(glm::dvec3 motion) {
    mVel = motion;
};

glm::dvec2 Entity::getRot() {
    return mRot;
};

glm::dvec2 Entity::getRotTarget() {
    return mRotTarget;
};

void Entity::setRot(glm::dvec2 newRot) {
    mRotTarget = newRot;
};

bool Entity::isAlive() {
    return mIsAlive;
};