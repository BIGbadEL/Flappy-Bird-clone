//
// Created by grzegorz on 21.09.18.
//

#include "window.h"

namespace engine {
    namespace graphics{

        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->m_Keys[key] = action != GLFW_RELEASE;
        }

        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->m_MouseButtons[button] = action != GLFW_RELEASE;
        }

        void window_resize(GLFWwindow *window, int width, int haight){
            glViewport(0,0, width, haight);
            Window *win = (Window*)(glfwGetWindowUserPointer(window));
            win->m_Width = width;
            win->m_Height = haight;
        }

        void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->m_Mx = xpos;
            win->m_My = ypos;
        }

        Window::Window(const char *title, int width, int height){

            m_Title = title;
            m_Height = height;
            m_Width = width;

            if(!init()) glfwTerminate();

            FontManager::add(new Font("default", "font/Lato-Bold.ttf", 50));
            audio::SoundManager::init();

            for(int i = 0; i < MAX_KEYS; i++){
                m_Keys[i] = false;
                m_KeyState[i] = false;
                m_KeyTyped[i] = false;
            }

            for(int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
                m_MouseButtons[i] = false;
                m_MouseButtonsState[i] = false;
                m_MouseButtonsTyped[i] = false;
            }


        }

        bool Window::init(){

            if(!glfwInit()) {
                std::cout << "Failed to init GLFW!" << std::endl;
                return false;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);

            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

            if(!m_Window){
                std::cout << "Fail to create GLFW window" << std::endl;
                return false;
            }

            glfwMakeContextCurrent(m_Window);
            glfwSetFramebufferSizeCallback(m_Window, window_resize);
            glfwSetKeyCallback(m_Window, key_callback);
            glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
            glfwSetCursorPosCallback(m_Window, cursor_position_callback);
            glfwSetWindowUserPointer(m_Window,this);
            glfwSwapInterval(0);


            if(glewInit() != GLEW_OK){
                std::cout << "Fail to initialize GLEW!" << std::endl;
                return false;
            }

            glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE);


            std::cout << "OpenGL " <<  glGetString(GL_VERSION) << std::endl;
            return true;
        }

        Window::~Window(){
            glfwTerminate();
            FontManager::clean();
            audio::SoundManager::clean();
        }

        void Window::clear() const{
            glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        }

        void Window::update(){

            for(int i = 0; i < MAX_KEYS; i++){
                m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];
            }

            for(int i = 0; i < MAX_MOUSE_BUTTONS; i++){
                m_MouseButtonsTyped[i] = m_MouseButtons[i] && !m_MouseButtonsState[i];
            }

            memcpy(m_KeyState, m_Keys, MAX_KEYS);
            memcpy(m_MouseButtonsState, m_MouseButtons, MAX_MOUSE_BUTTONS);

            GLenum error = glGetError();
            if(error != GL_NO_ERROR){
                std::cout << "OpenGL ERROR:" << error << std::endl;
            }

            audio::SoundManager::update();
            glfwPollEvents();
            glfwSwapBuffers(m_Window);
        }


        bool Window::closed() const{
            return glfwWindowShouldClose(m_Window);
        }

        bool Window::isKeyPressed(int keycode){
            if(keycode >= MAX_KEYS){
                return false;
            }
            return m_Keys[keycode];
        }

        bool Window::isKeyTyped(int keycode){
            if(keycode >= MAX_KEYS){
                return false;
            }
            return m_KeyTyped[keycode];
        }

        bool Window::isMouseButtonPressed(int buttoncode){
            if(buttoncode >= MAX_MOUSE_BUTTONS){
                return false;
            }

            return m_MouseButtons[buttoncode];
        }

        bool Window::isMouseButtonTyped(int buttoncode){
            if(buttoncode >= MAX_MOUSE_BUTTONS){
                return false;
            }

            return m_MouseButtonsTyped[buttoncode];
        }

        void Window::getMousePosition(double& x, double& y) const{
            x = m_Mx;
            y = m_My;
        }

    };
};