#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "SpaceShip.hpp"
#include "sre/Renderer.hpp"
#include "Laser.hpp"

SpaceShip::SpaceShip(AsteroidsGame *_pAsteroidsGame) : GameObject(sprite) {
    pAsteroidsGame = _pAsteroidsGame;
    scale = glm::vec2(0.5f,0.5f);
    winSize = sre::Renderer::instance->getDrawableSize();
    radius = 23;
    position = winSize * 0.5f;
    velocity = glm::vec2(0.0f,0.0f);
    sprite = pAsteroidsGame->getSprite("playerShip3_blue.png");
}

void SpaceShip::update(float deltaTime) {
    if (thrust){
        float acceleration = deltaTime*thrustPower;
        glm::vec2 direction = glm::rotateZ(glm::vec3(0,acceleration,0), glm::radians(rotation));
        velocity += direction;
        float speed = glm::length(velocity);
        if (speed > maxSpeed){
            velocity = velocity * (maxSpeed / speed);
        }
    } else {
        velocity = velocity * (1.0f - drag*deltaTime);
    }
    position += velocity * deltaTime;
    if (rotateCCW){
        rotation += deltaTime * rotationSpeed;
    }
    if (rotateCW){
        rotation -= deltaTime * rotationSpeed;
    }

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

void SpaceShip::onCollision(std::shared_ptr<GameObject> other) {
    printf("SpaceShip Collided...");
    if(dynamic_cast<Asteroid*>(&*other) != nullptr) printf("astroid\n");
}

void SpaceShip::onKey(SDL_Event &keyEvent) {
    if (keyEvent.key.keysym.sym == SDLK_UP){
        thrust = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_LEFT){
        rotateCCW = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_RIGHT){
        rotateCW = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_RIGHT){
        rotateCW = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_SPACE && keyEvent.type == SDL_KEYDOWN){
        printf("%p = ptr to GM:SS\n", pAsteroidsGame->getGMPointer());
        auto pGameObj = std::make_shared<Laser>(pAsteroidsGame->getGMPointer(), position, rotation);

        pAsteroidsGame->instantiateObject(pGameObj);
    }
}
