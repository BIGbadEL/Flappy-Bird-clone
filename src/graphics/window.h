//
// Created by grzegorz on 21.09.18.
//

#pragma once

#include <GL/glew.h>
#include <GL/glu_mangle.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <iostream>

#include "../audio/sound_manager.h"
#include "font_manager.h"


#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32

namespace engine {
    namespace graphics {

class Window {
private:
    int m_Width, m_Height;
    const char* m_Title;
    GLFWwindow* m_Window;
    bool m_MouseButtons[MAX_MOUSE_BUTTONS];
    bool m_MouseButtonsState[MAX_MOUSE_BUTTONS];
    bool m_MouseButtonsTyped[MAX_MOUSE_BUTTONS];
    bool m_Keys[MAX_KEYS];
    bool m_KeyState[MAX_KEYS];
    bool m_KeyTyped[MAX_KEYS];

    double m_Mx, m_My;
public:
    Window(const char *title, int width, int height);
    ~Window();
    inline int getWidth() const { return m_Width; };
    inline int getHeight() const { return m_Height; };
    void getMousePosition(double& x, double& y) const;

    void clear() const;
    bool closed() const;
    void update();

    bool isKeyPressed(int keycode);
    bool isKeyTyped(int keycode);
    bool isMouseButtonPressed(int buttoncode);
    bool isMouseButtonTyped(int buttoncode);
private:
    friend void window_resize(GLFWwindow *window, int width, int haight);
    friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    bool init();
};

    }
}


