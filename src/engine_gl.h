//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include "graphics/window.h"
#include "graphics/label.h"
#include "graphics/layer/layer.h"

#include "utils/Timer.h"

#include "Maths/maths.h"

namespace engine{

    class EngineGL
    {
    private:
        graphics::Window *m_Window;
        Timer *m_Timer;
        int m_FramesPerSecond, m_UpdatesPerSecond;
    protected:
        EngineGL()
                : m_Window(NULL), m_Timer(NULL), m_FramesPerSecond(0), m_UpdatesPerSecond(0)
        {
        }

        virtual ~EngineGL() {
            delete m_Window;
            delete m_Timer;
        }


    protected:

        graphics::Window* createWindow(const char *title, int width, int height){
            m_Window = new graphics::Window(title, width, height);

            return m_Window;
        }

        virtual void init() = 0; //runs once upone initialization
        virtual void tick() { } //runs once per second
        virtual void update() { } //runs 60 times per seond
        virtual void render() = 0; //runs as fast as possible

        inline const unsigned int getFPS() const{ return m_FramesPerSecond; }
        inline const unsigned int getUPS() const{ return m_UpdatesPerSecond; }
    private:

        void run(){

            m_Timer = new Timer();
            Timer time;
            float updateTimer = 0.0f;
            float updateTick = 1.0f / 60.0f;
            unsigned int frames = 0;
            unsigned int updates = 0;


            while(!m_Window->closed()){

                if(time.elapsed() - updateTimer >= updateTick){
                    update();
                    updates++;
                    updateTimer += updateTick;
                }

                m_Window->clear();
                render();
                m_Window->update();

                frames++;
                if(m_Timer->elapsed() >= 1.0f){
                    m_Timer->reset();
                    m_FramesPerSecond = frames;
                    m_UpdatesPerSecond = updates;
                    frames = 0;
                    updates = 0;
                    tick();
                }
            }
        }
    public:
        void start(){
            init();
            run();
        }
    };

}
