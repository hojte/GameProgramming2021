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
    // TODO exercise 2
}

glm::mat4 Ball::getTransform() {
    // TODO exercise 1 - should return the transformation matrix for this object
    //  containing translation (position) and scale,
    //  remember that the order of transformations is important
    float scaleZ = 0.1f;

    return glm::mat4(1);
}

void Ball::init() {
    // we use a 3D shape, and flatten it in Z so that it looks 2D
    mesh = Mesh::create().withSphere().build();
    // set shading technique and color of this object
    auto shader = Shader::getUnlit();
    material = shader->createMaterial();
    material->setColor(sre::Color(1,1,1));
}
