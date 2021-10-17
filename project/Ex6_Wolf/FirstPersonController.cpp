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


void FirstPersonController::update(float deltaTime) {
    auto directionVector = vec3(left?-1:right?1:0, 0,fwd?-1:bwd?1:0)*deltaTime * speed;
    auto rotationRadians = glm::radians(rotation);
    directionVector = glm::rotateY(directionVector, rotationRadians);

    position += directionVector;

    mat4 view = glm::rotate(rotationRadians, vec3(0.0f, -1.0f, 0.0f));
    view = translate(view, -position);
    camera->setViewTransform(view);
}

void FirstPersonController::onKey(SDL_Event &event) {
    // TODO implement key input here
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    fwd = true;
                    break;
                case SDLK_a:
                    left = true;
                    break;
                case SDLK_s:
                    bwd = true;
                    break;
                case SDLK_d:
                    right = true;
                    break;
                case SDLK_LSHIFT:
                    speed = 2;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    fwd = false;
                    break;
                case SDLK_a:
                    left = false;
                    break;
                case SDLK_s:
                    bwd = false;
                    break;
                case SDLK_d:
                    right = false;
                    break;
                case SDLK_LSHIFT:
                    speed = 1;
                    break;
            }
            break;
    }
}

void FirstPersonController::onMouse(SDL_Event &event) {
    // xrel ~-100 to ~100
    float floatingXrel = -(event.motion.xrel/10.0f); // todo adjust sensitivity
    float flipValue = 360;
    if(rotation + floatingXrel > flipValue) rotation = rotation + floatingXrel - flipValue; // tip over
    else if(rotation + floatingXrel < 0) rotation = rotation + floatingXrel + flipValue; // tip over
    else rotation += floatingXrel;
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation) {
    this->position = glm::vec3(position.x,0,position.y);
    this->rotation = rotation;
}
