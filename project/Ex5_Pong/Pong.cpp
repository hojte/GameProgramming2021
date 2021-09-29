#define GLM_ENABLE_EXPERIMENTAL
#include "sre/Shader.hpp"
#include "Pong.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "sre/Texture.hpp"
#include <iostream>
#include <glm/gtx/closest_point.hpp>

using namespace glm;
using namespace sre;

Pong::Pong() {
    int width = 640;
    int height = 480;
    r.setWindowSize({width,height});
    r.init()
      .withSdlWindowFlags(SDL_WINDOW_OPENGL)
      .build();

    cam.setWindowCoordinates();
    this->width = width;
    this->height = height;
    wPressed = false;
    pPressed = false;
    sPressed = false;
    lPressed = false;

    backgroundColor = sre::Color(0, 0, 0, 1);

    leftPaddle.position = vec2(paddleOffsetX, height / 2);
    leftPaddle.scale = vec2(10, paddleHeight);
    rightPaddle.position = vec2(width - paddleOffsetX, height / 2);
    rightPaddle.scale = vec2(lineWidth, paddleHeight);

    topBar.position = vec2(width / 2, height - barOffsetY);
    topBar.scale = vec2(width / 2, lineWidth);
    bottomBar.position = vec2(width / 2, barOffsetY);
    bottomBar.scale = vec2(width / 2, lineWidth);

    leftPaddle.init();
    rightPaddle.init();
    topBar.init();
    bottomBar.init();
    ball.init();

    resetBall(true);
    leftScore = 0;
    rightScore = 0;

    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };
    r.frameRender = [&](){
        render();
    };
    r.keyEvent = [&](SDL_Event& e){
        handleKeyInput(e);
    };
    r.startEventLoop();
}

void Pong::render(){
    auto renderPass = RenderPass::create()
            .withCamera(cam)
            .withClearColor(true, backgroundColor)
            .build();

    leftPaddle.draw(renderPass);
    rightPaddle.draw(renderPass);
    topBar.draw(renderPass);
    bottomBar.draw(renderPass);
    ball.draw(renderPass);
}

void Pong::update(float deltaTimeSec){
    float paddleSpeed = 200.0f;
    if (wPressed){
        movePaddle(&leftPaddle, paddleSpeed * deltaTimeSec);
    }
    if (sPressed){
        movePaddle(&leftPaddle, -paddleSpeed * deltaTimeSec);
    }
    if (pPressed){
        movePaddle(&rightPaddle, paddleSpeed * deltaTimeSec);
    }
    if (lPressed){
        movePaddle(&rightPaddle, -paddleSpeed * deltaTimeSec);
    }

    handleCollision(&leftPaddle);
    handleCollision(&rightPaddle);
    handleCollision(&topBar);
    handleCollision(&bottomBar);

    // move ball
    ball.move(deltaTimeSec);

    handleOutOfBounds();

    std::string score = std::to_string(leftScore) + "   " + std::to_string(rightScore);
    r.setWindowTitle(score);
}

void Pong::handleKeyInput(SDL_Event& event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    wPressed = true;
                    break;
                case SDLK_s:
                    sPressed = true;
                    break;
                case SDLK_p:
                    pPressed = true;
                    break;
                case SDLK_l:
                    lPressed = true;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    wPressed = false;
                    break;
                case SDLK_s:
                    sPressed = false;
                    break;
                case SDLK_p:
                    pPressed = false;
                    break;
                case SDLK_l:
                    lPressed = false;
                    break;
            }
            break;
    }
}

void Pong::movePaddle(Box *paddle, float yDelta) {
    paddle->position += glm::vec2(0, yDelta);
    paddle->position.y = glm::clamp(paddle->position.y, (float)(0+paddle->scale.y+paddle->scale.x*2), (float)height-paddle->scale.y - paddle->scale.x*2);
}

void Pong::resetBall(bool right) {
    ball.velocity = vec2(right ? 100 : -100, 180);
    ball.position = vec2(width / 2, height / 2);
}

bool Pong::handleCollision(Box *paddle) {
    for (int i = 0; i < 4; i++){
        auto e = paddle->getEdge(i);

        if (hasCollision(e)){
            // TODO: Exercise 3
            //  control what happens to the ball if there is a collision
            // check if 90 deg
            if (glm::dot(e.normal, ball.velocity) < 0) { // if angle > 90
                auto angle = glm::acos(glm::dot(e.normal, ball.velocity) / (glm::length(e.normal)*glm::length(ball.velocity)));
                angle = glm::degrees(angle);
                ball.velocity = ball.velocity - 2.0f * (ball.velocity*e.normal) * e.normal;
            }

            return false;
        }
    }
    return false;
}

bool Pong::hasCollision(Edge2D edge) {
    // TODO: Exercise 3 - are "ball" and "edge" intersecting/colliding?
    //  If the angle between edge.normal and ball->velocity is less than 90 degrees, then assume no collision
    //  test for collision between edge and this->ball. If collision is detected, then reflect the velocity on the ball
    //  using edge.normal.
    auto point = glm::closestPointOnLine(ball.position, edge.from, edge.to);
    if (glm::distance(point, ball.position) < ball.radius) {
        return true;
    }

    return false;
}

void Pong::handleOutOfBounds() {
    // TODO: Exercise 3 - what happens when the ball goes out of the field
    if (ball.position.x > width) {
        resetBall(true);
        leftScore++;
    }

    if (ball.position.x < 0) {
        resetBall(false);
        rightScore++;
    }
}

int main(int argc, char** argv) {
    new Pong();
    return 0;
}