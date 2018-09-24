//
// Created by grzegorz on 21.09.18.
//

#include "image_load.h"

namespace engine{
    BYTE* load_image(const char *filename, GLsizei *width, GLsizei *height){
        FreeImage_Initialise();

        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

        FIBITMAP *dib = nullptr;

        fif = FreeImage_GetFileType(filename, 0);

        if(fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(filename);

        if(fif == FIF_UNKNOWN) return NULL;

        if(FreeImage_FIFSupportsReading(fif))
            dib = FreeImage_Load(fif, filename);

        if(!dib) return NULL;

        *height = FreeImage_GetHeight(dib);
        *width = FreeImage_GetWidth(dib);
        BYTE *bytes = (BYTE*)FreeImage_GetBits(dib);
        FreeImage_Unload(dib);
        FreeImage_DeInitialise();
        return bytes;


    }
}