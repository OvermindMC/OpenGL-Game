#include "Entity.h"

Entity::Entity(Game* game, float health) : gamePtr(game), mPos(0.f), mVel(0.f), mRot(0.f), mHealth(health), mIsAlive(health > 0.f), mWasAlive(health > 0.f) {
    //
};

Game* Entity::getGame() {
    return gamePtr;
};

glm::vec3 Entity::getPos() {
    return mPos;
};

void Entity::setPos(glm::vec3 newPos) {
    mPos = newPos;
};

glm::vec3 Entity::getVelocity() {
    return mVel;
};

void Entity::setVelocity(glm::vec3 motion) {
    mVel = motion;
};

glm::vec2 Entity::getRot() {
    return mRot;
};

glm::vec2 Entity::getRotTarget() {
    return mRotTarget;
};

void Entity::setRot(glm::vec2 newRot) {
    mRotTarget = newRot;
};

bool Entity::isAlive() {
    return mIsAlive;
};