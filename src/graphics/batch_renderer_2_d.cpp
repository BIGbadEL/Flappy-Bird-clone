//
// Created by grzegorz on 21.09.18.
//

#include "batch_renderer_2_d.h"



namespace engine {
    namespace graphics{

        BatchRenderer2D::BatchRenderer2D(): Renderer2D(){
            init();
        }

        BatchRenderer2D::~BatchRenderer2D(){
            delete m_IBO;
            glDeleteBuffers(1, &m_VBO);
        }

        void BatchRenderer2D::begin(){
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            m_Buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

            if(!m_Buffer) std::cout << "[RENDERER]: ERROR glMapBuffer returned NULL" << std::endl;
        }

        void BatchRenderer2D::submit(const Renderable2D *renderable){

            const maths::Vec3& position = renderable->getPosition();
            const unsigned int color = renderable->getColor();
            const maths::Vec2& size = renderable->getSize();
            const std::vector<maths::Vec2>& uv = renderable->getUV();
            const GLuint tid = renderable->getTID();

            float ts = 0;

            if(tid > 0){

                bool found = false;
                for(unsigned int i = 0; i < m_TextureSlots.size(); i++){
                    if(tid == m_TextureSlots[i]){
                        ts = (float)(i + 1);
                        found = true;
                        break;
                    }
                }

                if(!found){

                    if(m_TextureSlots.size() >= RENDERER_MAX_TEXTURES){
                        end();
                        flush();
                        begin();
                    }
                    m_TextureSlots.push_back(tid);
                    ts = (float)(m_TextureSlots.size());
                }

            }

            m_Buffer->vertices = (*m_TransformationStackBack) * position;
            m_Buffer->uv = uv[0];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertices = (*m_TransformationStackBack) * maths::Vec3(position.x, position.y + size.y, position.z);
            m_Buffer->uv = uv[1];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertices = (*m_TransformationStackBack) * maths::Vec3(size.x + position.x, position.y + size.y, position.z);
            m_Buffer->uv = uv[2];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertices = (*m_TransformationStackBack) * maths::Vec3(size.x + position.x, position.y, position.z);
            m_Buffer->uv = uv[3];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndexCount += 6;

        }

        void BatchRenderer2D::end(){
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void BatchRenderer2D::flush(){

            for(unsigned int i = 0; i < m_TextureSlots.size(); i++){
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
            }


            glBindVertexArray(m_VAO);
            m_IBO->bind();

            glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);

            glBindVertexArray(0);
            m_IBO->unbind();
            m_IndexCount = 0;
            m_TextureSlots.clear();
        }


        void BatchRenderer2D::init(){

            glGenBuffers(1, &m_VBO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            glEnableVertexAttribArray(SHADER_UV_INDEX);
            glEnableVertexAttribArray(SHADER_TID_INDEX);
            glEnableVertexAttribArray(SHADER_COLOR_INDEX);

            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)nullptr);
            glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::uv));
            glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tid));
            glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));


            glBindBuffer(GL_ARRAY_BUFFER, 0);

            auto *indices = new GLuint[RENDERER_INDICES_SIZE];

            int offset = 0;
            for(int i = 0; i < RENDERER_INDICES_SIZE; i += 6, offset += 4){

                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;
                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

            }

            m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
            m_IndexCount = 0;

            glBindVertexArray(0);

            delete [] indices;
        }

        void BatchRenderer2D::drawString(const std::string& text, const maths::Vec3& position, const Font &font, const unsigned int color){
            using namespace ftgl;

            const maths::Vec2& scale = font.getScale();
            float scaleX = scale.x;
            float scaleY = scale.y;

            texture_font_t *ft_font = font.getFTGLfont();

            float x = position.x;

            float ts = 0;

            bool found = false;
            for(unsigned int i = 0; i < m_TextureSlots.size(); i++){
                if(m_TextureSlots[i] == font.getID()){
                    ts = (float)(i + 1);
                    found = true;
                    break;
                }
            }
            for(unsigned int i = 0; i < text.size(); i++){
                const char c = text.at(i);
                const texture_glyph_t *glyph = texture_font_get_glyph(ft_font, &c);
                if(!found){
                    if(m_TextureSlots.size() >= RENDERER_MAX_TEXTURES){
                        end();
                        flush();
                        begin();
                    }

                    m_TextureSlots.push_back(font.getID());
                    ts = (float)(m_TextureSlots.size());

                }

                if(i > 0){
                    float kerning = texture_glyph_get_kerning(glyph, &(text.at(i - 1)));
                    x += kerning / scaleX;
                }


                float x0 = x + glyph->offset_x / scaleX;
                float y0 = position.y + glyph->offset_y / scaleY;
                float x1 = x0 + glyph->width / scaleX;
                float y1 = y0 - glyph->height / scaleY;

                float u0 = glyph->s0;
                float v0 = glyph->t0;
                float u1 = glyph->s1;
                float v1 = glyph->t1;

                m_Buffer->vertices = *m_TransformationStackBack * maths::Vec3(x0, y0, 0);
                m_Buffer->uv = maths::Vec2(u0, v0);
                m_Buffer->tid = ts;
                m_Buffer->color = color;
                m_Buffer++;

                m_Buffer->vertices = *m_TransformationStackBack * maths::Vec3(x0, y1, 0);
                m_Buffer->uv = maths::Vec2(u0, v1);
                m_Buffer->tid = ts;
                m_Buffer->color = color;
                m_Buffer++;

                m_Buffer->vertices = *m_TransformationStackBack * maths::Vec3(x1, y1, 0);
                m_Buffer->uv = maths::Vec2(u1, v1);
                m_Buffer->tid = ts;
                m_Buffer->color = color;
                m_Buffer++;

                m_Buffer->vertices = *m_TransformationStackBack * maths::Vec3(x1, y0, 0);
                m_Buffer->uv = maths::Vec2(u1, v0);
                m_Buffer->tid = ts;
                m_Buffer->color = color;
                m_Buffer++;

                x += (glyph->width + glyph->offset_x + (glyph->advance_x - glyph->width - glyph->offset_x) / 5) / scaleX;
                m_IndexCount += 6;

            }


        }

    }
}