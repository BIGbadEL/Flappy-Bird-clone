//
// Created by grzegorz on 26.09.18.
//

#pragma once

#include "src/engine_gl.h"

class myLayer : public engine::graphics::Layer{

    friend class Pipe;

public:
    myLayer(engine::graphics::Shader *shader, engine::maths::Mat4 matrix)
            : engine::graphics::Layer(new engine::graphics::BatchRenderer2D(), shader, matrix) {

    }

    void destroy(){
//        delete m_Renderables.at(0);
//        delete temp.at(1);
//        temp.erase(temp.begin());
//        temp.erase(temp.begin());
    }
};

