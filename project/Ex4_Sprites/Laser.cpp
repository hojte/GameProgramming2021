//
// Created by hojte on 22/09/2021.
//
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/rotate_vector.hpp>
#include "Laser.hpp"

Laser::Laser(const glm::vec2 _position, float _rotation) : GameObject(sprite) {
    sprite = AsteroidsGame::pSingleton->getSprite("Lasers/laserBlue07.png");
    winSize = sre::Renderer::instance->getWindowSize();
    radius = 10;
    position = _position;
    rotation = _rotation;
    velocity = glm::rotateZ(glm::vec3(0, 400, 0), glm::radians(rotation));
}

void Laser::update(float deltaTime) {
    position += velocity * deltaTime;

    // wrap around
    if (position.x < 0) {
        position.x += winSize.x;
    }
    else if (position.x > winSize.x) {
        position.x -= winSize.x;
    }
    if (position.y < 0) {
        position.y += winSize.y;
    }
    else if (position.y > winSize.y) {
        position.y -= winSize.y;
    }
}

void Laser::onCollision(std::shared_ptr<GameObject> other) {
    if (dynamic_cast<Asteroid*>(&*other) != nullptr) {
        AsteroidsGame::pSingleton->unregisterObject(&*this);
    }
}
