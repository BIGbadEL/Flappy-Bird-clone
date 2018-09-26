//
// Created by grzegorz on 24.09.18.
//

#include "Game.h"


Game::~Game() {
    delete logLayer;
    delete BackGround;
    delete BgTex;
    delete birdTex;
    delete Bird;
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


    BackGround = new Layer(new BatchRenderer2D, new Shader("Shaders/basic.vert", "Shaders/basic.frag"), ortMat);

    BgTex = new Texture("textures/bg.png");

    BackGround->add( new Sprite(-16.0f + 0 * 9, -9.0f, 9, 18, BgTex));
    BackGround->add( new Sprite(-16.0f + 1 * 9, -9.0f, 9, 18, BgTex));
    BackGround->add( new Sprite(-16.0f + 2 * 9, -9.0f, 9, 18, BgTex));
    BackGround->add( new Sprite(-16.0f + 3 * 9, -9.0f, 9, 18, BgTex));
    BackGround->add( new Sprite(-16.0f + 4 * 9, -9.0f, 9, 18, BgTex));

    Bird = new Layer(new BatchRenderer2D, new Shader("Shaders/basic.vert", "Shaders/basic.frag"), ortMat);

    birdTex = new Texture("textures/bird.png", true);
    Bird->add( new Sprite(0.0f, 0.0f, 1.0f, 1.0f, birdTex));

    pipe = new Pipe(5);


}


void Game::render() { //as fast as possible
    BackGround->render();
    logLayer->render();
    pipe->drewPipes();

    Bird->render();


    if(window->isKeyTyped(GLFW_KEY_SPACE)) velocity = VELOCITY;

}

void Game::update() { //60 per second

    std::vector<Renderable2D*> BG =  BackGround->getRenderable();
    float speed = 0.01;
    for(unsigned int i = 0; i < 5; i++){
        ((Sprite*)(BG.at(i)))->position.x -= speed;
        if (-16.0f - 9 >= ((Sprite *) (BG.at(i)))->position.x) ((Sprite*)(BG.at(i)))->position.x = -16.0f + 4 * 9;
    }

    velocity += ACCELERATION;
    BirdPositionY += velocity;

    Shader *temp = Bird->getShader();
    temp->enable();

    temp->setUniformMat4("vm_matrix", Mat4::translation(Vec3(0.0f, BirdPositionY, 0.0f)) *  Mat4::roatation(velocity * 90, Vec3(0.0f, 0.0f, 1.0f)));

    temp->disable();

    pipe->movePipe();


}

void Game::tick() { //once per second
    fps->text = std::to_string(getFPS()) + " fps";
    ups->text = std::to_string(getUPS()) + " ups";
}




