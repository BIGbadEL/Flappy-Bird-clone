//
// Created by grzegorz on 03.10.18.
//
#include "BackGround.h"

BackGround::BackGround(float speed) : m_Layer(nullptr), m_Texture(nullptr), m_Speed(speed){
    init();
}

BackGround::~BackGround() {
    delete m_Layer;
    delete m_Texture;
}

void BackGround::drewBG() {
    m_Layer->render();
}

void BackGround::moveBG() {
    using namespace engine;
    using namespace maths;
    using namespace graphics;


    for(auto renderable : m_Layer->m_Renderables){
        ((Sprite*)(renderable))->position.x -= m_Speed;
        if (-16.0f - 9 >= ((Sprite *) (renderable))->position.x) ((Sprite*)(renderable))->position.x = -16.0f + 4 * 9;
    }
}

void BackGround::init() {
    m_Layer = new myLayer(new engine::graphics::Shader("Shaders/basic.vert", "Shaders/basic.frag"), engine::maths::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

    m_Texture = new engine::graphics::Texture("textures/bg.png");

    m_Layer->add( new engine::graphics::Sprite(-16.0f + 0 * 9, -9.0f, 9, 18, m_Texture));
    m_Layer->add( new engine::graphics::Sprite(-16.0f + 1 * 9, -9.0f, 9, 18, m_Texture));
    m_Layer->add( new engine::graphics::Sprite(-16.0f + 2 * 9, -9.0f, 9, 18, m_Texture));
    m_Layer->add( new engine::graphics::Sprite(-16.0f + 3 * 9, -9.0f, 9, 18, m_Texture));
    m_Layer->add( new engine::graphics::Sprite(-16.0f + 4 * 9, -9.0f, 9, 18, m_Texture));
}
