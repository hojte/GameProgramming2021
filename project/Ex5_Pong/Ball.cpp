#include "Ball.hpp"
#include "sre/Mesh.hpp"
#include "sre/Shader.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace sre;
using namespace glm;

Ball::Ball() {
    position = vec2(0,0);
    radius = 10;
}

void Ball::draw(sre::RenderPass& renderPass) {
    renderPass.draw(mesh, getTransform(), material);
}

void Ball::move(float deltaTimeInSeconds) {
    velocity *= 1.001; // make the game harder

    position += velocity*deltaTimeInSeconds;
}

glm::mat4 Ball::getTransform() {
    float scaleZ = 0.01f;
    glm::vec3 pos = glm::vec3(position.x, position.y, 0);
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1), pos);
    translationMatrix = glm::scale(translationMatrix, glm::vec3(radius, radius, scaleZ));

    return translationMatrix;
}

void Ball::init() {
    // we use a 3D shape, and flatten it in Z so that it looks 2D
    mesh = Mesh::create().withSphere().build();
    // set shading technique and color of this object
    auto shader = Shader::getUnlit();
    material = shader->createMaterial();
    material->setColor(sre::Color(1,1,1));
}
