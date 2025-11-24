#include "Player.h"
#include "../Game.h"

#include <string>

Player::Player(Game* game) : Entity(game, 10.f) {
    //
};

void Player::update(float deltaTime) {
    if(Game* game = this->getGame()) {
        Camera* cam = game->getCam();

        if(!cam || !this->isAlive())
            return;
        
        glm::vec2 diff = mRotTarget - mRot;
        
        if(glm::length(diff) > 0.001f) {
            diff.x = mRotTarget.x - mRot.x;
            diff.y = fmodf((mRotTarget.y - mRot.y) + 540.f, 360.f) - 180.f;

            float dist = glm::length(diff);
            if(dist < 1.f)
                dist *= 0.1f;

            float t = 1.f - expf(-((dist * 1.f) + 0.1f) * deltaTime);
            mRot += diff * t;

            mRot.x = glm::clamp(mRot.x, -89.f, 89.f);
        };
        
        glm::vec3 moveDir(0.f);
        glm::vec3 front = cam->getFront();

        front.y = 0.f;
        front = glm::normalize(front);

        glm::vec3 right = glm::normalize(
            glm::cross(
                front, glm::vec3(0.f, 1.f, 0.f)
            )
        );

        if(game->isInputPressed(MoveInput::Forward))
            moveDir += front;
        if(game->isInputPressed(MoveInput::Backward))
            moveDir -= front;
        
        if(game->isInputPressed(MoveInput::Left))
            moveDir -= right;
        if(game->isInputPressed(MoveInput::Right))
            moveDir += right;
        
        moveDir.y = (
            game->isInputPressed(MoveInput::Jump) ? 1.f : game->isInputPressed(MoveInput::Crouch) ? -1.f : 0.f
        );
        
        if(glm::length(moveDir) > 0.0001f)
            moveDir = glm::normalize(moveDir);
        
        float speed = 3.f;
        glm::vec3 vel = moveDir * speed;
        this->setVelocity(vel);

        glm::vec3 pos = this->getPos();
        pos += vel * deltaTime;

        this->setPos(pos);
    };
};