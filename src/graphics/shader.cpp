//
// Created by grzegorz on 21.09.18.
//

#include "shader.h"

namespace engine{
    namespace graphics{

        Shader::Shader(const char *vertPath, const char *fragPath): m_VertPath(vertPath), m_FragPath(fragPath){
            m_ShaderID = load();
        }

        GLuint Shader::load(){
            GLuint program = glCreateProgram();
            GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

            //std::cout << program << vertex << fragment << std::endl;

            std::string tempV = read_file(m_VertPath);
            std::string tempF = read_file(m_FragPath);

            // std::cout << tempV << std::endl;

            const char *vertSource = tempV.c_str();
            const char *fragSource = tempF.c_str();

            glShaderSource(vertex, 1, &vertSource, NULL);
            glCompileShader(vertex);

            GLint result;
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
            if(result == GL_FALSE){
                GLint length;
                glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> error(length);
                glGetShaderInfoLog(vertex, length, &length, &error[0]);

                std::cout << "Failed to compile vertax shader: \n" << &error[0] << std::endl;

                glDeleteShader(vertex);

                return 0;
            }

            glShaderSource(fragment, 1, &fragSource, NULL);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
            if(result == GL_FALSE){
                GLint length;
                glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> error(length);
                glGetShaderInfoLog(fragment, length, &length, &error[0]);

                std::cout << "Failed to compile fragment shader: \n" << &error[0] << std::endl;

                glDeleteShader(fragment);

                return 0;
            }

            glAttachShader(program, vertex);
            glAttachShader(program, fragment);

            glLinkProgram(program);
            glValidateProgram(program);

            glDeleteShader(fragment);
            glDeleteShader(vertex);

            return program;
        }

        Shader::~Shader(){
            glDeleteProgram(m_ShaderID);
        }

        void Shader::enable() const{
            glUseProgram(m_ShaderID);
        }

        void Shader::disable() const{
            glUseProgram(0);
        }

        GLint Shader::getUniformLocation(const GLchar *name){
            return glGetUniformLocation(m_ShaderID, name);
        }

        void Shader::setUniformMat4(const GLchar *name, const maths::Mat4 &matrix){
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
        }

        void Shader::setUniform1f(const GLchar *name, const float &value){
            glUniform1f(getUniformLocation(name), value);
        }

        void Shader::setUniform2f(const GLchar *name, const maths::Vec2 &values){
            glUniform2f(getUniformLocation(name), values.x, values.y);
        }

        void Shader::setUniform3f(const GLchar *name, const maths::Vec3 &values){
            glUniform3f(getUniformLocation(name), values.x, values.y, values.z);
        }

        void Shader::setUniform4f(const GLchar *name, const maths::Vec4 &values){
            glUniform4f(getUniformLocation(name), values.x, values.y, values.z, values.w);
        }

        void Shader::setUniform1fv(const GLchar *name,const int& count, float *values){
            glUniform1fv(getUniformLocation(name), count, values);
        }

        void Shader::setUniform1iv(const GLchar *name,const int& count, int *values){
            glUniform1iv(getUniformLocation(name), count, values);
        }

        void Shader::setUniform1i(const GLchar *name, const int &value){
            glUniform1i(getUniformLocation(name), value);
        }


    }
}