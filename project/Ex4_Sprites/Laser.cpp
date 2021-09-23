//
// Created by hojte on 22/09/2021.
//
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/rotate_vector.hpp>
#include "Laser.hpp"

bool Laser::isPresent = false;

Laser::Laser(const glm::vec2 _position, float _rotation) : GameObject(sprite) {
    sprite = AsteroidsGame::pSingleton->getSprite("Lasers/laserBlue07.png");
    radius = 7;
    position = _position;
    rotation = _rotation;
    velocity = glm::rotateZ(glm::vec3(0, 400, 0), glm::radians(rotation));
    isPresent = true;
}

void Laser::destroy() {
    isPresent = false;
    AsteroidsGame::pSingleton->unregisterObject(this);
}

void Laser::update(float deltaTime) {
    position += velocity * deltaTime;
    timeAlive += deltaTime;
    if (timeAlive > 1) destroy();
}

void Laser::onCollision(std::shared_ptr<GameObject> other) {
    if (std::dynamic_pointer_cast<Asteroid>(other) != nullptr) {
        destroy();
    }
}


