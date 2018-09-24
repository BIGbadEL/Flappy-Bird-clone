//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include "buffer/index_buffer.h"
#include "buffer/vertex_array.h"
#include "shader.h"
#include "renderer_2_d.h"
#include "texture.h"

namespace engine {
    namespace graphics {

        struct VertexData{
            maths::Vec3 vertices;
            maths::Vec2 uv;
            float tid;
            unsigned int color;
        };

        class Renderable2D{
        protected:
            maths::Vec2 m_Size;
            maths::Vec3 m_Position;
            unsigned int m_Color;
            std::vector<maths::Vec2> m_UV;
            Texture *m_Texture;
        protected:
            Renderable2D() { setUVDefaults(); }

        public:

            Renderable2D(maths::Vec2 size, maths::Vec3 position,  unsigned int color)
                    : m_Size(size), m_Position(position), m_Color(color){ setUVDefaults(); }

            virtual ~Renderable2D(){ }
            virtual void submit(Renderer2D *renderer) const{
                renderer->submit(this);
            }

            void setColor(unsigned int color) { m_Color = color; }
            void setColor(const maths::Vec4 color) {
                int r = color.x * 255.0f;
                int g = color.y * 255.0f;
                int b = color.z * 255.0f;
                int a = color.w * 255.0f;

                m_Color = a << 24 | b << 16 | g << 8 | r;
            }

            inline const maths::Vec2& getSize() const{ return m_Size; }
            inline const maths::Vec3& getPosition() const{ return m_Position; }
            inline const unsigned int getColor() const{ return m_Color; }
            inline const std::vector<maths::Vec2>& getUV() const{ return m_UV; }
            inline const GLuint getTID() const{return m_Texture == NULL ? 0 : m_Texture->getID(); }
        private:
            inline void setUVDefaults(){
                m_UV.push_back(maths::Vec2(0, 0));
                m_UV.push_back(maths::Vec2(0, 1));
                m_UV.push_back(maths::Vec2(1, 1));
                m_UV.push_back(maths::Vec2(1, 0));
                m_Texture = NULL;
            }
        };
    }
}
