//
// Created by grzegorz on 21.09.18.
//

#pragma once

#include <string>

#include "../Maths/maths.h"
#include "renderable_2_d.h"
#include "font_manager.h"


namespace engine {
    namespace graphics{

        class Label : public Renderable2D{
        public:
            Font *m_Font;
            std::string text;
            maths::Vec3 &position;
            float x, y;
        public:
            Label(std::string text, float x, float y, unsigned int color);
            Label(std::string text, float x, float y, Font *font, unsigned int color);
            Label(std::string text, float x, float y, const std::string& font, unsigned int color);
            Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color);

            void submit(Renderer2D *renderer) const override;
            void validateFont(const std::string& name, unsigned int size = 0);
        private:
        };
    }
}
