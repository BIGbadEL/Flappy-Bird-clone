//
// Created by grzegorz on 21.09.18.
//

#include "file_utils.h"


namespace engine{

    std::string read_file( const char *filepath){

        FILE *file = fopen(filepath,"rt");
        fseek(file, 0, SEEK_END);
        unsigned long length = ftell(file);

        char *data = new char[length + 1];
        memset(data, 0, length + 1);

        fseek(file, 0, SEEK_SET);

        if(!fread(data, 1, length, file)){
            printf("[FILE_UTILS]: could not open a file!!!");
        }

        fclose(file);

        std::string result(data);

        delete[] data;
        return result;
    }
}