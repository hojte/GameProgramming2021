//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include <iostream>
#include "BirdMovementComponent.hpp"
#include "GameObject.hpp"

BirdMovementComponent::BirdMovementComponent(GameObject *gameObject) : Component(gameObject) {}

void BirdMovementComponent::update(float deltaTime) {
    time += deltaTime;
    gameObject->setPosition(computePositionAtTime(time));
}

glm::vec2 BirdMovementComponent::computePositionAtTime(float time) {
    int segment = (int)fmod(time, getNumberOfSegments());
    float t = fmod(time,1.0f);

    float b0 = glm::pow(1 - t, 2);
    float b1 = 2 * (1 - t)*t;
    float b2 = glm::pow(t, 2);

    auto p0 = positions[(segment * 2)];
    auto p1 = positions[(segment * 2) + 1];
    auto p2 = positions[(segment * 2) + 2];

    return (b0*p0 + b1*p1 + b2*p2);
}

const std::vector<glm::vec2> &BirdMovementComponent::getPositions() {
    return positions;
}

void BirdMovementComponent::setPositions(std::vector<glm::vec2> positions) {
    this->positions = std::move(positions);
}

int BirdMovementComponent::getNumberOfSegments() {
    // todo return number of Quadratic Bézier spline segments instead
    return positions.size() / 2;
}

