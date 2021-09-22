//
// Created by hojte on 22/09/2021.
//

#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include "AsteroidsGame.hpp"

class Asteroid : public GameObject, public Collidable  {
public:
    //Asteroid();

    Asteroid(AsteroidsGame *pAsteroidsGame);

    void update(float deltaTime) override;
    void onCollision(std::shared_ptr<GameObject> other) override;

private:
    int size = 2;
    glm::vec2 velocity{};
    AsteroidsGame *pAsteroidsGame;

    glm::vec2 winSize{};
};
