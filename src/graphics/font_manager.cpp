//
// Created by grzegorz on 21.09.18.
//

#include "font_manager.h"

namespace engine {
    namespace graphics {

        std::vector<Font*> FontManager::m_Fonts;

        void FontManager::add(Font *font){
            m_Fonts.push_back(font);
        }

        void FontManager::clean(){
            while(!m_Fonts.empty()){
                delete m_Fonts.back();
                m_Fonts.pop_back();
            }
        }

        Font *FontManager::get(){
            return m_Fonts[0];
        }

        Font* FontManager::get(const std::string& name){
            for(unsigned int i = 0; i < m_Fonts.size(); i++){
                if(name == m_Fonts[i]->getName()) return m_Fonts[i];
            }
            std::cout << "[FONT MANAGER] couldn't find font: " << name << " using default one.\n";
            return m_Fonts[0];
        }

        Font* FontManager::get(const std::string& name, unsigned int size){
            for(unsigned int i = 0; i < m_Fonts.size(); i++){
                if( size == m_Fonts[i]->getSize() && name == m_Fonts[i]->getName()) return m_Fonts[i];
            }

            return NULL;
        }

    }
}