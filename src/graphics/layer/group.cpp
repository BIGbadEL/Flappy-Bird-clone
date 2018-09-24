//
// Created by grzegorz on 21.09.18.
//

#include "group.h"

namespace engine {
    namespace graphics {

        Group::Group(const maths::Mat4 &matrix): m_TransformationMatrix(matrix) {

        }

        Group::~Group(){
            while(!m_Renderables.empty()){
                delete m_Renderables.back();
                m_Renderables.pop_back();
            }
        }

        void Group::submit(Renderer2D *renderer) const{
            renderer->push(m_TransformationMatrix);

            for(const Renderable2D *renderable : m_Renderables){
                renderable->submit(renderer);
            }

            renderer->pop();
        }

        void Group::add(Renderable2D* renderable){
            m_Renderables.push_back(renderable);
        }


    }
}