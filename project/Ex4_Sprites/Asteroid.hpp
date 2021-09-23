//
// Created by hojte on 22/09/2021.
//

#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include "AsteroidsGame.hpp"
#include "SpaceShip.hpp"

class Asteroid : public GameObject, public Collidable  {
public:
    Asteroid(glm::vec2 position = glm::vec2(0,0), int size = 2);

    void update(float deltaTime) override;
    void onCollision(std::shared_ptr<GameObject> other) override;

private:
    int size = 2;
    glm::vec2 velocity{};
    float rotationSpeed;

    glm::vec2 winSize{};
};
