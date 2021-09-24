#include <ctime>
#include <glm/gtc/constants.hpp>
#include "AsteroidsGame.hpp"
#include "SpaceShip.hpp"

using namespace sre;
AsteroidsGame* AsteroidsGame::pSingleton = nullptr;

AsteroidsGame::AsteroidsGame() {
    pSingleton=this;

    r.setWindowTitle("Asteroids");

    r.init().withSdlInitFlags(SDL_INIT_EVERYTHING)
            .withSdlWindowFlags(SDL_WINDOW_OPENGL);

    time_t t;
    // random seed based on time
    srand((unsigned) time(&t));

    atlas = SpriteAtlas::create("asteroids.json","asteroids.png");

    camera.setWindowCoordinates();

    restartGame();

    r.frameUpdate = [&](float deltaTime){
        if(!freezeGame) update(deltaTime);
    };

    r.keyEvent = [&](SDL_Event& event){
        keyEvent(event);
    };

    r.frameRender = [&](){
        render();
    };

    r.startEventLoop();
}

void AsteroidsGame::update(float deltaTime) {
	for (auto & gameObject : gameObjects) {
		gameObject->update(deltaTime);
    }
}

Sprite AsteroidsGame::getSprite(std::string fileName) {
    return atlas->get(fileName);
}

void drawCircle(std::vector<glm::vec3>& lines, glm::vec2 position, float radius){
    int sides = 15;
    float quaterPi = glm::two_pi<float>() / (float)sides;
    for (float f = 0; f<glm::two_pi<float>(); f += quaterPi){
        // line from
        lines.emplace_back(position.x + cosf(f)*radius,
                                  position.y + sinf(f)*radius,
                                  0
        );
        // line to
        lines.emplace_back(position.x + cosf(f+quaterPi)*radius,
                                  position.y + sinf(f+quaterPi)*radius,
                                  0
        );
    }
}

void AsteroidsGame::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, {.20, .60, .86, 1})
            .build();
    auto spriteBatchBuilder = SpriteBatch::create();

    for (auto & gameObject : gameObjects) {
        gameObject->render(spriteBatchBuilder);
    }
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);

    if (debugCollisionCircles){
        std::vector<glm::vec3> lines;
        for (auto & go : gameObjects){
            auto col = std::dynamic_pointer_cast<Collidable>(go);
            if (col != nullptr){
                drawCircle(lines, go->position, col->getRadius());
            }
        }
        renderPass.drawLines(lines);
    }

    // Collision detection
    for (int i = 0; i < gameObjects.size(); i++){ // NOLINT
        auto go = gameObjects[i];
        auto col = std::dynamic_pointer_cast<Collidable>(go);
        if (col != nullptr){
            for (int j = 0; j < gameObjects.size(); j++){ // NOLINT
                auto go2 = gameObjects[j];
                auto col2 = std::dynamic_pointer_cast<Collidable>(go2);
                if (
                        col2 != nullptr &&
                        col2 != col &&
                        col->getRadius()+col2->getRadius() > glm::distance(go->position, go2->position)
                        )
                {
                    col->onCollision(go2);
                    col2->onCollision(go);
                }
            }
        }
    }

    // Check game won
    auto asteroids = 0;
    for (auto & gameObject : gameObjects) {
        if(std::dynamic_pointer_cast<Asteroid>(gameObject)) asteroids++;
    }
    if (asteroids == 0) freezeGame = true;

    // UI
    ImGui::SetNextWindowPos(ImVec2(Renderer::instance->getWindowSize().x/2 - 100, .0f), ImGuiSetCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 85), ImGuiSetCond_Always);
    ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::LabelText(asteroids==0 ? "You Win!":"GOs", "%i", (int)gameObjects.size());
    ImGui::LabelText("Score", "%i",score);
    ImGui::Checkbox("Multiplayer: ", &multiplayer);
    ImGui::End();
}

void AsteroidsGame::keyEvent(SDL_Event &event) {
    if (freezeGame && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        restartGame();
        return;
    }
    for (int i = 0; i < gameObjects.size(); i++) gameObjects[i]->onKey(event); // NOLINT
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) {
        debugCollisionCircles = !debugCollisionCircles;
    }
}

void AsteroidsGame::unregisterObject(GameObject *pGameObj) {
    for (int i = 0; i<gameObjects.size(); i++) {
        if(gameObjects[i].get() == pGameObj)
            gameObjects.erase(gameObjects.begin() + i);
    }
}

void AsteroidsGame::instantiateObject(std::shared_ptr<GameObject> pGameObj) {
    gameObjects.push_back(pGameObj);
}

void AsteroidsGame::incrementScore() {
    score++;
}

void AsteroidsGame::restartGame() {
    score = 0;
    gameObjects.clear();

    gameObjects.push_back(std::make_shared<SpaceShip>());
    gameObjects.push_back(std::make_shared<Asteroid>());
    gameObjects.push_back(std::make_shared<Asteroid>());
    gameObjects.push_back(std::make_shared<Asteroid>());
    gameObjects.push_back(std::make_shared<Asteroid>());
    gameObjects.push_back(std::make_shared<Asteroid>());

    freezeGame = false;
}

void AsteroidsGame::gameOver() {
    freezeGame = true;
}

int main() {
    new AsteroidsGame();
    return 0;
}