//
// Created by grzegorz on 21.09.18.
//

#pragma once

#include "renderable_2_d.h"

namespace engine {
    namespace graphics{

        class Sprite : public Renderable2D{
        public:
            maths::Vec3& position;

        public:
            Sprite(float x, float y, float width, float height, const unsigned int color);
            Sprite(float x, float y, float width, float height, Texture *texture);
        };

    }
}
