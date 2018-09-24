//
// Created by grzegorz on 21.09.18.
//

#include "string_utils.h"

namespace engine{
    std::vector<std::string> split(const std::string &s, char delim){
        std::vector<std::string> elems;
        std::stringstream ss(s);
        std::string item;
        while(std::getline(ss, item, delim)){
            elems.push_back(item);
        }
        return elems;
    }
}