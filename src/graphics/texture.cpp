//
// Created by grzegorz on 21.09.18.
//

#include "texture.h"

namespace engine {
    namespace graphics{


        Texture::Texture(const std::string &filename, bool isRGBA)
                : m_FileName(filename), m_isRGBA(isRGBA) {
            m_TID = load();
        }

        Texture::~Texture(){
            glDeleteTextures(1, &m_TID);
        }

        void Texture::bind() const{
            glBindTexture(GL_TEXTURE_2D, m_TID);
        }

        void Texture::unbind() const{
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        GLuint Texture::load(){
            GLuint result;
            BYTE *pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height);
            glGenTextures(1, &result);

            glBindTexture(GL_TEXTURE_2D, result);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            if(m_isRGBA){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
            }else{
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
            }



            glBindTexture(GL_TEXTURE_2D, 0);

            return result;
        }



    }
}
