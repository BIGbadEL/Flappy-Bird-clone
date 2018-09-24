//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include <cmath>
#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include <cstring>


namespace engine {
    namespace maths{

        struct Mat4{

            union{
                float elements[4 * 4];
                Vec4 columns[4];
            };

            Mat4();

            explicit Mat4(float diagonal);

            Vec4 getColumn(int n){  return columns[n]; }
            static Mat4 identity();
            static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
            static Mat4 perspective(float fov, float aspectRatio, float near, float far);
            static Mat4 translation(const Vec3 &translation);
            static Mat4 roatation(float angle, const Vec3 &axis);
            static Mat4 scale(const Vec3& scale);

            Mat4& multiply(const Mat4& other);
            friend Mat4 operator*(Mat4 left, const Mat4 &right);
            Mat4& operator*=(const Mat4& other);

            Vec3 multiply(const Vec3 &other) const;
            friend Vec3 operator*(const Mat4& left, const Vec3 &right);

            Vec4 multiply(const Vec4 &other) const;
            friend Vec4 operator*(const Mat4& left, const Vec4 &right);


        };

        inline float to_Radians(float degrees){ return degrees * (M_PI / 180.0f); }



    }
}



