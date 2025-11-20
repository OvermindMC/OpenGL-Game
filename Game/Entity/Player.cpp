#include "Player.h"
#include "../Game.h"

#include <string>

Player::Player(Game* game) : Entity(game, 10.f) {
    //
};

void Player::update(float deltaTime) {
    if(Game* game = getGame()) {
        Camera* cam = game->getCam();

        if(!cam || !this->isAlive())
            return;
        
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
        
        float speed = 10.f;
        glm::vec3 vel = moveDir * speed;
        this->setVelocity(vel);

        glm::vec3 pos = this->getPos();
        pos += vel * deltaTime;

        this->setPos(pos);
    };
};