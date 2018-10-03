//
// Created by grzegorz on 03.10.18.
//

#include "Bird.h"

Bird::Bird(float acceleration, float x, float y) : m_Layer(nullptr), m_Texture(nullptr), v(0.0f), a(acceleration), posX(x), posY(y){
    init();
}

Bird::~Bird() {
    delete m_Layer;
    delete m_Texture;
}

void Bird::moveBird(bool spacePressed) {
    using namespace engine;
    using namespace maths;
    using namespace graphics;

    v += a;
    if(spacePressed) v = VELOCITY;
    posY += v;

    Shader *temp = m_Layer->getShader();
    temp->enable();
    temp->setUniformMat4("vm_matrix", Mat4::translation(Vec3(0.0f, posY, 0.0f)) *  Mat4::roatation(v * 90, Vec3(0.0f, 0.0f, 1.0f)));
    temp->disable();

}

void Bird::drewBird() {
    m_Layer->render();
}

void Bird::init() {
    using namespace engine;
    using namespace maths;
    using namespace graphics;
    m_Layer = new myLayer(new Shader("Shaders/basic.vert", "Shaders/basic.frag"), Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

    m_Texture = new Texture("textures/bird.png", true);
    m_Layer->add( new Sprite(posX, posY, 1.0f, 1.0f, m_Texture));
}
