//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include "MovingPlatformComponent.hpp"
#include "PlatformComponent.hpp"
#include "GameObject.hpp"

MovingPlatformComponent::MovingPlatformComponent(GameObject *gameObject) : Component(gameObject)
{
    platformComponent = gameObject->getComponent<PlatformComponent>();
}

void MovingPlatformComponent::update(float deltaTime) {
    totalTime += deltaTime;
    float time = fmod(totalTime,2);

    if (time>1){
        time = time -1;
        time = glm::smoothstep(0.0f, 1.0f, time);
        platformComponent->moveTo(glm::mix(movementStart, movementEnd, time));
    } else {
        time = glm::smoothstep(0.0f, 1.0f, time);
        platformComponent->moveTo(glm::mix(movementEnd, movementStart, time));
    }
}

void MovingPlatformComponent::setMovementStart(glm::vec2 pos) {
    movementStart = pos;
}

void MovingPlatformComponent::setMovementEnd(glm::vec2 pos) {
    movementEnd = pos;
}
