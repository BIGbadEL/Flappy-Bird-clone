//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include <GL/glew.h>

namespace engine{
    namespace graphics{

        class IndexBuffer{
        private:
            GLuint m_BufferID;
            GLuint m_Count;
        public:
            IndexBuffer(GLushort *data, GLsizei count);
            IndexBuffer(GLuint *data, GLsizei count);
            ~IndexBuffer();
            void bind() const;
            void unbind() const;
            inline GLuint getCount() const { return m_Count; }
        };
    }
};


