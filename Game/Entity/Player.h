#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    Player(Game*);

    void update(float) override;
private:
    //
};