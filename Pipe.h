//
// Created by grzegorz on 26.09.18.
//

#pragma once

#include <time.h>

#include "myLayer.h"
#include "src/engine_gl.h"


#define NUMBER_OF_PIPS 5
#define FIRST_X 10.0f


class Pipe {
private:
    myLayer *m_Layer;
    engine::graphics::Texture *m_Pipe_down;
    engine::graphics::Texture *m_Pipe_up;
    //std::vector<float> m_PosX;
    float m_PosX;
    float m_BreakSize;

private:
    void makePipe();
    void init();

public:
    explicit Pipe(float size);
    ~Pipe();

    void drewPipes();
    void movePipe();


};



