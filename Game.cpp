//
// Created by grzegorz on 24.09.18.
//

#include "Game.h"


Game::~Game() {
    delete logLayer;
    delete background;
    delete bird;
    delete pipe;

}

void Game::init() {
    window = createWindow("Flappy", 1280, 720);
    FontManager::get()->setScale(Vec2((float)window->getWidth()/32, (float)window->getHeight()/8));

    Mat4 ortMat = Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);

    logLayer = new Layer(new BatchRenderer2D, new Shader("Shaders/basic.vert", "Shaders/basic.frag"), ortMat);
    fps = new Label("", -15.5f, 8.0f, 0xf0f0ffff);
    ups = new Label("", -15.5f, 7.0f, 0xf0f0ffff);

    logLayer->add(fps);
    logLayer->add(ups);


    background = new BackGround(0.01);
    bird = new Bird(ACCELERATION, BirdPositionX, BirdPositionY);
    pipe = new Pipe(5);

}


void Game::render() { //as fast as possible

   background->drewBG();
   logLayer->render();
   pipe->drewPipes();
   bird->drewBird();

   if(window->isKeyTyped(GLFW_KEY_SPACE)) spacePressed = true;

}

void Game::update() { //60 per second

    background->moveBG();
    bird->moveBird(spacePressed);
    spacePressed = false;
    pipe->movePipe();

}

void Game::tick() { //once per second
    fps->text = std::to_string(getFPS()) + " fps";
    ups->text = std::to_string(getUPS()) + " ups";
}




