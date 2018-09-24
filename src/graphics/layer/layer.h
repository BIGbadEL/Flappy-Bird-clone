//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include "../renderer_2_d.h"
#include <vector>
#include "../batch_renderer_2_d.h"

namespace engine {
    namespace graphics {

        class Layer{
        protected:
            Renderer2D *m_Renderer;
            std::vector<Renderable2D*> m_Renderables;
            Shader *m_Shader;
            maths::Mat4 m_ProjectionMatrix;

        public:
            Layer(Renderer2D *renderer, Shader *shader, maths::Mat4 projectronMatrix);
            virtual ~Layer();
            virtual void add(Renderable2D *renderable);
            virtual void render();

            inline const std::vector<Renderable2D*>& getRenderable() const { return m_Renderables; }
            inline const Shader* getShader() const { return m_Shader; }
        };

    }
}
