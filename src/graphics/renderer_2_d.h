//
// Created by grzegorz on 21.09.18.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

#include "../Maths/maths.h"
#include "font.h"



namespace engine {
    namespace graphics {

        class Renderable2D;

        class Renderer2D{
        protected:
            std::vector<maths::Mat4> m_TransformationStack;
            maths::Mat4* m_TransformationStackBack;
        protected:
            Renderer2D(){
                m_TransformationStack.push_back(maths::Mat4::identity());
                m_TransformationStackBack = &m_TransformationStack.back();
            }
        public:
            void push(const maths::Mat4 &matrix, bool override = false){

                if(override)
                    m_TransformationStack.push_back(matrix);
                else
                    m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

                m_TransformationStackBack = &m_TransformationStack.back();
            }

            void pop(){
                if(m_TransformationStack.size() > 1){
                    m_TransformationStack.pop_back();
                    m_TransformationStackBack = &m_TransformationStack.back();
                }
            }

            virtual ~Renderer2D(){}
            virtual void begin(){}
            virtual void end(){}
            virtual void drawString(const std::string& text, const maths::Vec3& position, const Font &font, const unsigned int color){}
            virtual void submit(const Renderable2D *renderable) = 0;
            virtual void flush() = 0;
        };
    }
}