//
// Created by grzegorz on 24.09.18.
//

#pragma once


#include "src/engine_gl.h"

using namespace engine;
using namespace graphics;
using namespace maths;

class Game : public EngineGL {
private:
    Window *window;
    Layer *logLayer;
    Label *fps;
    Label *ups;

public:
    Game(){ }

    ~Game() {
        delete logLayer;
    }

    void init() override{
        window = createWindow("Flappy", 960, 540);
        FontManager::get()->setScale(Vec2((float)window->getWidth()/32, (float)window->getHeight()/8));

        logLayer = new Layer(new BatchRenderer2D, new Shader("Shaders/basic.vert", "Shaders/basic.frag"), Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
        fps = new Label("", -15.5f, 8.0f, 0xffffffff);
        ups = new Label("", -15.5f, 7.0f, 0xffffffff);
        logLayer->add(fps);
        logLayer->add(ups);
    }

    void render() override{ //as fast as possible
        logLayer->render();
    }

    void update() override{ //60 per second

    }

    void tick() override{ //once per second
        fps->text = std::to_string(getFPS()) + " fps";
        ups->text = std::to_string(getUPS()) + " ups";
    }

};



