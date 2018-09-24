//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include "../utils/image_load.h"
#include <GL/glew.h>
#include <string>

namespace engine {
    namespace graphics{

        class Texture{
        private:
            std::string m_FileName;
            GLuint m_TID;
            GLsizei m_Width, m_Height;
            bool m_isRGBA;
        public:
            explicit Texture(const std::string &filename, bool isRGBA = false);
            ~Texture();

            void bind() const;
            void unbind() const;

            inline const GLuint getID() const{ return m_TID; }
            inline const GLsizei getWidth() const{ return m_Width; }
            inline const GLsizei getHeight() const{ return m_Height; }
        private:
            GLuint load();

        };

    }
}
