//
// Created by grzegorz on 21.09.18.
//

#include "font.h"


namespace engine {
    namespace graphics {
        Font::Font(std::string name, std::string filename, unsigned int size)
                : m_Name(name), m_FileName(filename), m_Size(size) {
            m_FTAtlas = ftgl::texture_atlas_new(512, 512, 4);
            m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_Size,  m_FileName.c_str());
        }
        Font::~Font(){
            texture_atlas_delete(m_FTAtlas);
            texture_font_delete(m_FTFont);
        }
    }
}