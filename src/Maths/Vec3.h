//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include <iostream>

namespace engine {
    namespace maths {
        struct Vec3{
            float x, y, z;

            Vec3();
            inline Vec3(const float &x, const float &y, const float &z){
                this->x = x;
                this->y = y;
                this->z = z;
            }

            Vec3& add(const Vec3 &other);
            Vec3& subtract(const Vec3 &other);
            Vec3& multiply(const Vec3 &other);
            Vec3& divide(const Vec3 &other);

            bool operator==(const Vec3 &other);
            bool operator!=(const Vec3 &other);

            Vec3& operator+=(const Vec3 &right);
            Vec3& operator-=(const Vec3 &right);
            Vec3& operator*=(const Vec3 &right);
            Vec3& operator/=(const Vec3 &right);

            friend Vec3 operator+(Vec3 left, const Vec3 &right);
            friend Vec3 operator-(Vec3 left, const Vec3 &right);
            friend Vec3 operator*(Vec3 left, const Vec3 &right);
            friend Vec3 operator/(Vec3 left, const Vec3 &right);

            friend std::ostream& operator<<(std::ostream& stream, const Vec3 & vector);

        };

    }
}



