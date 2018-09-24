//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include <string>

#include "../../freetype_GL/freetype-gl.h"
#include "../Maths/maths.h"


namespace engine {
    namespace graphics {

        class Font{
        private:
            ftgl::texture_atlas_t *m_FTAtlas;
            ftgl::texture_font_t *m_FTFont;
            std::string m_Name;
            std::string m_FileName;
            maths::Vec2 m_Scale;
            unsigned int m_Size;


        public:
            Font(std::string name, std::string filename, unsigned int size);
            ~Font();

            void setScale(maths::Vec2 scale) { m_Scale = scale; }

            inline ftgl::texture_font_t* getFTGLfont() const { return m_FTFont; }

            inline const std::string& getName() const { return m_Name; }
            inline const std::string& getFileName() const { return m_FileName; }
            inline const maths::Vec2& getScale() const { return m_Scale; }
            inline const unsigned int getSize() const { return m_Size; }
            inline const unsigned int getID() const { return m_FTAtlas->id; }
            inline const ftgl::texture_glyph_t* getGlyph(const char character) const { return texture_font_get_glyph(m_FTFont, &character); }

        };
    }
}
