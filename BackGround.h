//
// Created by grzegorz on 03.10.18.
//
#pragma once
#include "myLayer.h"



class BackGround {
private:
    myLayer *m_Layer;
    engine::graphics::Texture *m_Texture;
    float m_Speed;
private:
    void init();

public:
    explicit BackGround(float speed);
    ~BackGround();
    void drewBG();
    void moveBG();


};




