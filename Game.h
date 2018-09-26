//
// Created by grzegorz on 24.09.18.
//

#pragma once


#include "src/engine_gl.h"
#include "Pipe.h"

#define ACCELERATION (-2.0f/360.0f)
#define VELOCITY (0.3f)

using namespace engine;
using namespace graphics;
using namespace maths;


class Game : public EngineGL {
private:
    Window *window;

    Layer *BackGround;
    Texture *BgTex;

    Layer *Bird;
    Texture *birdTex;
    float velocity;
    float BirdPositionY;
    float BirdPositionX;


    Pipe *pipe;



    Layer *logLayer;
    Label *fps;
    Label *ups;

public:
    Game(): window(nullptr), BackGround(nullptr), BgTex(nullptr), Bird(nullptr), birdTex(nullptr), velocity(0), BirdPositionY(0), BirdPositionX(0),
            pipe(nullptr), logLayer(nullptr), fps(nullptr), ups(nullptr) { }

    ~Game();

    void init() override;

    void render() override;

    void update() override;

    void tick() override;



};



