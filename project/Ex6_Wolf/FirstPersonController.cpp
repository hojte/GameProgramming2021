#include "FirstPersonController.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

using namespace sre;
using namespace glm;


FirstPersonController::FirstPersonController(sre::Camera * camera)
:camera(camera)
{
    camera->setPerspectiveProjection(45,0.1f,1000);
    position = vec3(0,0,0);
}


void FirstPersonController::update(float deltaTime){
    // TODO implement the camera movement using position and rotation here
    camera->lookAt(vec3(0,0,0), vec3(0,0,-1), vec3{0,1,0});
}

void FirstPersonController::onKey(SDL_Event &event) {
    // TODO implement key input here
}

void FirstPersonController::onMouse(SDL_Event &event) {
    // TODO implement mouse input here
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation) {
    this->position = glm::vec3(position.x,0,position.y);
    this->rotation = rotation;
}
