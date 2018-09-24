//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include <vector>
#include <iostream>
#include <GL/glew.h>
#include "../utils/file_utils.h"
#include "../Maths/maths.h"

namespace engine {
    namespace graphics {

        class Shader{
        private:
            GLuint m_ShaderID;
            const char *m_VertPath;
            const char *m_FragPath;
        public:
            Shader(const char *vertPath, const char *fragPath);
            ~Shader();


            void setUniformMat4(const GLchar *name, const maths::Mat4 &matrix);
            void setUniform1f(const GLchar *name, const float &value);
            void setUniform2f(const GLchar *name, const maths::Vec2 &values);
            void setUniform3f(const GLchar *name, const maths::Vec3 &values);
            void setUniform4f(const GLchar *name, const maths::Vec4 &values);
            void setUniform1fv(const GLchar *name,const int &count, float *values);
            void setUniform1iv(const GLchar *name, const int &count, int *value);
            void setUniform1i(const GLchar *name, const int &value);

            void enable() const;
            void disable() const;


        private:
            GLuint load();
            GLint getUniformLocation(const GLchar *name);
        };

    }
}
