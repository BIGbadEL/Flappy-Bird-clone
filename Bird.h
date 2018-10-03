//
// Created by grzegorz on 03.10.18.
//

#pragma once

#include "myLayer.h"
#define VELOCITY (0.3f)

class Bird {
private:
    myLayer *m_Layer;
    engine::graphics::Texture *m_Texture;
    float v;
    float a;
    float posX;
    float posY;
private:
    void init();
public:
    Bird(float acceleration, float x, float y);
    ~Bird();

    void moveBird(bool spacePressed = false);
    void drewBird();

};



