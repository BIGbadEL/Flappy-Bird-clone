//
// Created by grzegorz on 21.09.18.
//

#pragma once

#include "font.h"
#include <vector>

namespace engine{
    namespace graphics{

        class FontManager{
        private:
            static std::vector<Font*> m_Fonts;
        public:
            static void add(Font *font);
            static Font* get();
            static Font* get(const std::string& name);
            static Font* get(const std::string& name, unsigned int size);
            static void clean();
        private:
            FontManager();
        };
    }
}
