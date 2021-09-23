//
// Created by hojte on 22/09/2021.
//
#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include "AsteroidsGame.hpp"
#include "SpaceShip.hpp"
#include "Asteroid.hpp"

class Laser : public GameObject, public Collidable {
public:
    Laser(AsteroidsGame* pAsteroidsGame, glm::vec2 position, float rotation);

    void update(float deltaTime) override;

    void onCollision(std::shared_ptr<GameObject> other) override;

    glm::vec2 velocity{};
private:
    glm::vec2 winSize{};
    AsteroidsGame *pAsteroidsGame;
};
