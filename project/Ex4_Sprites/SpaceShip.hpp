#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include "Asteroid.hpp"


class SpaceShip : public GameObject, public Collidable  {
public:
    SpaceShip();

    void update(float deltaTime) override;
    void onCollision(std::shared_ptr<GameObject> other) override;
    void onKey(SDL_Event &keyEvent) override;

private:
    bool rotateCW = false;
    bool rotateCCW = false;
    bool thrust = false;

    float drag = 0.80f;
    float maxSpeed = 460.0f;
    float thrustPower = 600.0f;
    float rotationSpeed = 130.0f;
    glm::vec2 velocity;
    int shotsFired = 0;

    glm::vec2 winSize;
};


