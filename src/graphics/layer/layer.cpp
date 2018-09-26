//
// Created by grzegorz on 21.09.18.
//

#include "layer.h"
#include "group.h"
#include "../shader.h"

namespace engine {
    namespace graphics {

        Layer::Layer(Renderer2D *renderer, Shader *shader, maths::Mat4 projectionMatrix)
                : m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix){

            m_Shader->enable();
            GLint texIDs[] = {0, 1, 2 , 3, 4, 5, 6, 7, 8, 9,
                              10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                              21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };


            m_Shader->setUniform1iv("textures", 32, texIDs);
            m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
            m_Shader->disable();

        }

        Layer::~Layer(){

            delete m_Shader;
            delete m_Renderer;

            while(!m_Renderables.empty()){
                delete m_Renderables.back();
                m_Renderables.pop_back();
            }
        }

        void Layer::add(Renderable2D *renderable){
            m_Renderables.push_back(renderable);
        }

        void Layer::render(){

            m_Shader->enable();

            m_Renderer->begin();

            for(const Renderable2D *renderable : m_Renderables){
                renderable->submit(m_Renderer);
            }

            m_Renderer->end();
            m_Renderer->flush();

        }

    }
}
