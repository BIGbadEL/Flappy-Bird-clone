//
// Created by grzegorz on 21.09.18.
//

#pragma once

#include <GL/glew.h>

namespace engine{
    namespace graphics{

        class Buffer{
        private:
            GLuint m_BufferID;
            GLuint m_CompontntCount;
        public:
            Buffer(GLfloat *data, GLsizei count, GLuint componetCount);
            ~Buffer();

            void bind() const;
            void unbind() const;
            inline GLuint getComponentCount() const { return m_CompontntCount; }
        };
    }
};


