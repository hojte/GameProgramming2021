//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include "BirdController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "BirdGame.hpp"
#include "SpriteComponent.hpp"

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
    // initiate bird physics
    pBirdPhys = gameObject->getComponent<PhysicsComponent>();
    pBirdPhys->setLinearVelocity(glm::vec2(1,1));
}

void BirdController::update(float deltaTime) {
    auto clampedVelocity = glm::clamp(pBirdPhys->getLinearVelocity().y, -5.0f, 5.0f);
    pBirdPhys->setLinearVelocity(glm::vec2(1, clampedVelocity));
}

bool BirdController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN){
        pBirdPhys->addImpulse(glm::vec2(0,.2f));
    }
    return false;
}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
    if (comp->getGameObject()->name.find("Wall") != std::string::npos)
        BirdGame::instance->setGameState(GameState::GameOver);
    else {
        printf("coin collected\n");
        comp->getGameObject()->removeComponent(comp->getGameObject()->getComponent<SpriteComponent>());
    }
}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}


