//
// Created by grzegorz on 26.09.18.
//

#include "Pipe.h"

#define WIDTH (52.0f / (320.0f / 9.0f))
#define LENGTH 7.4625f

Pipe::Pipe(float size): m_BreakSize(size) {
    srand(time(nullptr));
    init();
}

Pipe::~Pipe() {
    delete m_Layer;
    delete m_Pipe_down;
    delete m_Pipe_up;
}

void Pipe::movePipe() {
    using namespace engine;
    using namespace graphics;
    using namespace maths;

    float speed = 0.05;
    for (auto &m_Renderable : m_Layer->m_Renderables) {
        ((Sprite*) m_Renderable)->position.x -= speed;
    }

    if(-16.0f - WIDTH >= ((Sprite*)(m_Layer->m_Renderables.at(0)))->position.x ){
        m_PosX = ((Sprite*)m_Layer->getSprite())->position.x + LENGTH;
        delete m_Layer->m_Renderables.at(0);
        delete m_Layer->m_Renderables.at(1);
        m_Layer->m_Renderables.erase(m_Layer->m_Renderables.begin());
        m_Layer->m_Renderables.erase(m_Layer->m_Renderables.begin());
        makePipe();
    }


}

void Pipe::drewPipes() {
    m_Layer->render();
}

void Pipe::makePipe() {

    float temp = -9.0f - (float)(rand()%35) / 7.0f;
    m_Layer->add(new engine::graphics::Sprite(m_PosX, temp, WIDTH, 9.0f, m_Pipe_down));
    m_Layer->add(new engine::graphics::Sprite(m_PosX, temp + 9.0f + m_BreakSize, WIDTH, 9.0f, m_Pipe_up));

}

void Pipe::init() {
    m_Layer = new myLayer(new engine::graphics::Shader("Shaders/basic.vert", "Shaders/basic.frag"),
            engine::maths::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
    m_Pipe_down = new engine::graphics::Texture("textures/pipe.png", true);
    m_Pipe_up = new engine::graphics::Texture("textures/pipe_up.png", true);

    float temp = -9.0f - (float)(rand()%35) / 7.0f;
    m_Layer->add(new engine::graphics::Sprite(FIRST_X, temp, WIDTH, 9.0f, m_Pipe_down));
    m_Layer->add(new engine::graphics::Sprite(FIRST_X, temp + 9.0f + m_BreakSize, WIDTH, 9.0f, m_Pipe_up));

    m_PosX = FIRST_X + LENGTH;
    for(int i = 0; i < NUMBER_OF_PIPS - 1; i++){
        makePipe();
        m_PosX += LENGTH;
    }
}
