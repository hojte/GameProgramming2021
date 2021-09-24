//
// Created by hojte on 22/09/2021.
//

#include <sre/Renderer.hpp>
#include "Asteroid.hpp"
#include "Laser.hpp"

Asteroid::Asteroid(glm::vec2 _position, int _size) : GameObject(sprite) {
    size = _size;
    rotationSpeed = rand() % 100 + 40;
    velocity = glm::vec2(rand() % 200 - 100, rand() % 200 - 100);
    winSize = sre::Renderer::instance->getDrawableSize();
    scale = glm::vec2(0.7f,0.7f);

    switch (size) {
        case 0:
            position = _position;
            sprite = AsteroidsGame::pSingleton->getSprite("Meteors/meteorGrey_small1.png");
            radius = 10;
            break;
        case 1:
            position = _position;
            sprite = AsteroidsGame::pSingleton->getSprite("Meteors/meteorGrey_med1.png");
            radius = 15;
            break;
        default: // big asteroid
            position = glm::vec2(rand() % int(winSize.x), rand() % int(winSize.y));
            sprite = AsteroidsGame::pSingleton->getSprite("Meteors/meteorGrey_big1.png");
            radius = 25;
            break;
    }
}

void Asteroid::update(float deltaTime) {
    position += velocity * deltaTime;
    rotation += rotationSpeed * deltaTime;

    // wrap around
    if (position.x < 0){
        position.x += winSize.x;
    } else if (position.x > winSize.x){
        position.x -= winSize.x;
    }
    if (position.y < 0){
        position.y += winSize.y;
    } else if (position.y > winSize.y){
        position.y -= winSize.y;
    }
}

void Asteroid::onCollision(std::shared_ptr<GameObject> other) {
    if(std::dynamic_pointer_cast<Laser>(other) != nullptr) {
        if(size != 0) {
            AsteroidsGame::pSingleton->instantiateObject(std::make_shared<Asteroid>(position, --size));
            AsteroidsGame::pSingleton->instantiateObject(std::make_shared<Asteroid>(position, size));
        }
        AsteroidsGame::pSingleton->unregisterObject(this);
        AsteroidsGame::pSingleton->incrementScore();
    }
}
