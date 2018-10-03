//
// Created by grzegorz on 24.09.18.
//

#pragma once


#include "src/engine_gl.h"
#include "Pipe.h"
#include "BackGround.h"
#include "Bird.h"

#define ACCELERATION (-2.0f/360.0f)


using namespace engine;
using namespace graphics;
using namespace maths;


class Game : public EngineGL {
private:
    Window *window;

    //Layer *BackGround;
    Texture *BgTex;

    BackGround *background;

//    Layer *Bird;
    Bird *bird;
    bool spacePressed;

    float BirdPositionY;
    float BirdPositionX;


    Pipe *pipe;



    Layer *logLayer;
    Label *fps;
    Label *ups;

public:
    Game(): window(nullptr), BgTex(nullptr), background(nullptr), bird(nullptr), spacePressed(false), BirdPositionY(0), BirdPositionX(0),
            pipe(nullptr), logLayer(nullptr), fps(nullptr), ups(nullptr) { }

    ~Game();

    void init() override;

    void render() override;

    void update() override;

    void tick() override;



};



