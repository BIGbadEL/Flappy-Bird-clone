//
// Created by grzegorz on 21.09.18.
//

#include "label.h"

namespace engine {
    namespace graphics{

        Label::Label(std::string text, float x, float y, unsigned int color)
                : Renderable2D(), text(text), position(m_Position){
            m_Position = maths::Vec3(x, y, 0);
            m_Color = color;
            m_Font = FontManager::get("default");


        }

        Label::Label(std::string text, float x, float y, Font *font, unsigned int color)
                : Renderable2D(), m_Font(font), text(text), position(m_Position){
            m_Position = maths::Vec3(x, y, 0);
            m_Color = color;


        }

        Label::Label(std::string text, float x, float y, const std::string& font, unsigned int color)
                : Renderable2D(), m_Font(FontManager::get(font)), text(text), position(m_Position){
            m_Position = maths::Vec3(x, y, 0);
            m_Color = color;
            if(!m_Font)    validateFont(font);

        }

        Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color)
                : Renderable2D(), m_Font(FontManager::get(font, size)), text(text), position(m_Position){
            m_Position = maths::Vec3(x, y, 0);
            m_Color = color;
            if(!m_Font)    validateFont(font, size);
        }

        void Label::submit(Renderer2D *renderer) const{
            renderer->drawString(text, position, *m_Font, m_Color);
        }

        void Label::validateFont(const std::string& name, unsigned int size){
            std::cout << "NULL FONT! Font=" << name;
            if(size){
                std::cout << ", Size: " << size << std::endl;
            }else{
                std::cout << std::endl;
            }

            m_Font = FontManager::get("default");
        }
    }
}
