//
// Created by grzegorz on 21.09.18.
//

#include "sprite.h"

namespace engine {
    namespace graphics {
        Sprite::Sprite(float x, float y, float width, float height, const unsigned int color)
                : Renderable2D(maths::Vec2(width,height), maths::Vec3(x, y, 0), color), position(m_Position){

        }

        Sprite::Sprite(float x, float y, float width, float height, Texture *texture)
                : Renderable2D(maths::Vec2(width,height), maths::Vec3(x, y, 0), 0xffffffff), position(m_Position){
            m_Texture = texture;
        }

    }
}