#include "Wolf3D.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


using namespace std;
using namespace sre;
using namespace glm;

Wolf3D::Wolf3D()
        :fpsController(&camera)
{
    r.init();
    init();

    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };
    r.frameRender = [&](){
        render();
    };
    r.keyEvent = [&](SDL_Event& e){
        fpsController.onKey(e);
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_RETURN)
                lockMouse = !lockMouse;
            if (e.key.keysym.sym == SDLK_l)
                lockRotation = !lockRotation;
        }
    };
    r.mouseEvent = [&](SDL_Event& e){
        if (!lockRotation){
            fpsController.onMouse(e);
        }
    };
    r.startEventLoop();
}

void Wolf3D::update(float deltaTime) {
    // Enable/disable mouse lock
    SDL_SetWindowGrab(r.getSDLWindow(),lockMouse?SDL_TRUE:SDL_FALSE);
    SDL_SetRelativeMouseMode(lockMouse?SDL_TRUE:SDL_FALSE);

    fpsController.update(deltaTime);
}

void Wolf3D::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .build();

    renderPass.draw(walls, glm::mat4(1), wallMaterial);

    if (debugBricks){
        renderDebugBricks(renderPass);
    }

    ImGui::SetNextWindowPos(ImVec2(10, .0f), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(260, 130), ImGuiCond_Once);
    ImGui::Begin("Config", nullptr);
    ImGui::DragFloat("Rot", &fpsController.rotation);
    ImGui::DragFloat3("Pos", &(fpsController.position.x), 0.1f);
    ImGui::Checkbox("DebugBricks", &debugBricks);
    ImGui::SameLine(); ImGui::Checkbox("Lock Mouse[RET]", &lockMouse);
    ImGui::Checkbox("LockRotation[L]", &lockRotation);
    ImGui::End();
}

// Creates a textured cube with a side length of 1 (e.g. from -0.5 to 0.5).
// The cube must be centered at (x,0,z)
// The texturing
void Wolf3D::addCube(std::vector<glm::vec3>& vertexPositions, std::vector<glm::vec4>& textureCoordinates, int x, int z, int type){
    // TODO implement this

    auto translation = vec3(x, 0, z);
    // Incomplete implementation - creates two triangles in the xy-plane
    vertexPositions.insert(vertexPositions.end(),{
            // front:
            translation + glm::vec3(-0.5,-0.5,0.5),
            translation + glm::vec3(0.5,-0.5,0.5),
            translation + glm::vec3(-0.5,0.5,0.5),
            translation + glm::vec3(0.5,0.5,0.5),
            translation + glm::vec3(-0.5,0.5,0.5),
            translation + glm::vec3(0.5,-0.5,0.5),
            // side left
            translation + glm::vec3(-0.5,-0.5,-0.5),
            translation +  glm::vec3(-0.5,-0.5,0.5),
            translation +  glm::vec3(-0.5,0.5,-0.5),
            translation +     glm::vec3(-0.5,0.5,0.5),
            translation +     glm::vec3(-0.5,0.5,-0.5),
            translation +      glm::vec3(-0.5,-0.5,0.5),
            // side right
            translation +       glm::vec3(0.5,-0.5,0.5),
            translation +       glm::vec3(0.5,-0.5,-0.5),
            translation +      glm::vec3(0.5,0.5,0.5),
            translation +      glm::vec3(0.5,0.5,-0.5),
            translation +      glm::vec3(0.5,0.5,0.5),
            translation +      glm::vec3(0.5,-0.5,-0.5),
            // back side
            translation +      glm::vec3(0.5,-0.5,-0.5),
            translation +      glm::vec3(-0.5,-0.5,-0.5),
            translation +     glm::vec3(0.5,0.5,-0.5),
            translation +    glm::vec3(-0.5,0.5,-0.5),
            translation +    glm::vec3(0.5,0.5,-0.5),
            translation +   glm::vec3(-0.5,-0.5,-0.5),
    });

    glm::vec2 textureSize(2048,4096);
    glm::vec2 tileSize(64,64);
    glm::vec2 tileSizeWithBorder(65,65);
    float column = type % 8;
    auto row = type / 8;

    glm::vec2 min = vec2(0,42*tileSizeWithBorder.y) / textureSize;
    glm::vec2 max = min+tileSize / textureSize;
    glm::vec2 minDark = vec2(tileSizeWithBorder.x*(column+1.0f), (42.0f - row)*tileSizeWithBorder.y) / textureSize;
    glm::vec2 maxDark = minDark + tileSize / textureSize;

    textureCoordinates.insert(textureCoordinates.end(),{ // front and right
            glm::vec4(min.x,min.y,0,0), glm::vec4(max.x,min.y,0,0), glm::vec4(min.x,max.y,0,0),
            glm::vec4(max.x,max.y,0,0), glm::vec4(min.x,max.y,0,0), glm::vec4(max.x,min.y,0,0),
            glm::vec4(minDark.x,minDark.y,0,0), glm::vec4(maxDark.x,minDark.y,0,0), glm::vec4(minDark.x,maxDark.y,0,0),
            glm::vec4(maxDark.x,maxDark.y,0,0), glm::vec4(minDark.x,maxDark.y,0,0), glm::vec4(maxDark.x,minDark.y,0,0),
            // left and back
            glm::vec4(minDark.x,minDark.y,0,0), glm::vec4(maxDark.x,minDark.y,0,0), glm::vec4(minDark.x,maxDark.y,0,0),
            glm::vec4(maxDark.x,maxDark.y,0,0), glm::vec4(minDark.x,maxDark.y,0,0), glm::vec4(maxDark.x,minDark.y,0,0),

            //back
            glm::vec4(min.x,min.y,0,0), glm::vec4(max.x,min.y,0,0), glm::vec4(min.x,max.y,0,0),
            glm::vec4(max.x,max.y,0,0), glm::vec4(min.x,max.y,0,0), glm::vec4(max.x,min.y,0,0),
    });
}

void Wolf3D::init() {
    wallMaterial = Shader::getUnlit()->createMaterial();
    auto texture = Texture::create().withFile("level0.png")
            .withGenerateMipmaps(false)
            .withFilterSampling(false)
            .build();
    wallMaterial->setTexture(texture);

    map.loadMap("level0.json");

    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec4> textureCoordinates;

    for (int x=0;x<map.getWidth();x++){
        for (int y=0;y<map.getHeight();y++){
            int field = map.getTile(x,y);
            if (field != -1){
                addCube(vertexPositions,textureCoordinates,x,y,field);
            }
        }
    }

    fpsController.setInitialPosition(map.getStartingPosition(), map.getStartingRotation());

    walls = Mesh::create()
            .withPositions(vertexPositions)
            .withUVs(textureCoordinates)
            .build();
}

void Wolf3D::renderDebugBricks(RenderPass & renderPass){
    static auto cube = Mesh::create().withCube(0.5f).build();
    static vector<shared_ptr<Material> > materials = {
            Shader::getUnlit()->createMaterial(),
            Shader::getUnlit()->createMaterial(),
            Shader::getUnlit()->createMaterial()
    };

    std::vector<vec3> positions = {
            {-1,0,-2},
            { 0,0,-3},
            { 1,0,-4}
    };
    std::vector<sre::Color> colors = {
            {1,0,0,1},
            {0,1,0,1},
            {0,0,1,1},
    };
    for (int i=0;i<positions.size();i++){
        materials[i]->setColor(colors[i]);
        renderPass.draw(cube, glm::translate(positions[i]), materials[i]);
    }
}

int main(){
    new Wolf3D();
    return 0;
}