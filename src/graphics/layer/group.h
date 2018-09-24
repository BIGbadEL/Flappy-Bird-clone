//
// Created by grzegorz on 21.09.18.
//

#pragma once

#include "../renderable_2_d.h"

namespace engine {
    namespace graphics {

        class Group : public Renderable2D{
        private:
            std::vector<Renderable2D *> m_Renderables;
            maths::Mat4 m_TransformationMatrix;
        public:
            Group(const maths::Mat4 &matrix);
            ~Group();
            void submit(Renderer2D *renderer) const override;
            void add(Renderable2D* renderable);
        };

    }
}
