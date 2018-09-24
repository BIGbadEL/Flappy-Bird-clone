//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include <FreeImage.h>
#include <string>
#include <GL/glew.h>

namespace engine{
    BYTE* load_image(const char *filename, GLsizei *width, GLsizei *height);
}


