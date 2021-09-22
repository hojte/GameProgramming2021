//
// Created by hojte on 22/09/2021.
//

#include <sre/Renderer.hpp>
#include "Asteroid.hpp"

Asteroid::Asteroid(AsteroidsGame *_pAsteroidsGame) : GameObject(sprite) {
    pAsteroidsGame = _pAsteroidsGame;
    velocity = glm::vec2(rand() % 200 - 100, rand() % 200 - 100);
    winSize = sre::Renderer::instance->getDrawableSize();
    position = glm::vec2(rand() % int(winSize.x), rand() % int(winSize.y));
    scale = glm::vec2(0.7f,0.7f);
    sprite = pAsteroidsGame->getSprite("Meteors/meteorGrey_big1.png");
}

void Asteroid::update(float deltaTime) {
    position += velocity * deltaTime;

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
    printf("Asteroid Collided...");
    switch (size) {
        case 2:
            size--;
            sprite = pAsteroidsGame->getSprite("Meteors/meteorGrey_med1.png");
        case 1:
            size--;
            sprite = pAsteroidsGame->getSprite("Meteors/meteorGrey_small1.png");
        default:
            pAsteroidsGame->unregister(this);
    }
}
