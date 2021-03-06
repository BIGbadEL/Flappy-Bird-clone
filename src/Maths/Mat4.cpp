#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-return-braced-init-list"
//
// Created by grzegorz on 21.09.18.
//

#include "Mat4.h"
namespace engine {
    namespace maths {

        Mat4::Mat4(){
            for (float &element : elements) {
                element = 0;
            }
        }

        Mat4::Mat4(float diagonal){
            for (float &element : elements) {
                element = 0;
            }

            elements[0 + 0 * 4] = diagonal;
            elements[1 + 1 * 4] = diagonal;
            elements[2 + 2 * 4] = diagonal;
            elements[3 + 3 * 4] = diagonal;
        }

        Mat4 Mat4::identity(){
            return Mat4(1.0f);
        }

        Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far){
            Mat4 result(1.0f);

            result.elements[0 + 0 * 4] = 2/(right - left);
            result.elements[1 + 1 * 4] = 2/(top - bottom);
            result.elements[2 + 2 * 4] = -2/(far - near);
            result.elements[0 + 3 * 4] = -(right + left)/(right - left);
            result.elements[1 + 3 * 4] = -(top + bottom)/(top - bottom);  //Uwaga na minusy nie wiadomo czy poprawne!!!
            result.elements[2 + 3 * 4] = -(far + near)/(far - near);

            return result;

        }

        Mat4 Mat4::perspective(float fov, float aspectRatio, float near, float far){
            Mat4 result(1.0f);
            float q = 1/tan(to_Radians(fov/2));
            float a = q/aspectRatio;

            result.elements[0 + 0 * 4] = a;
            result.elements[1 + 1 * 4] = q;
            result.elements[2 + 2 * 4] = (near + far)/(near - far); //uwaga niepewne źródło
            result.elements[2 + 3 * 4] = (2 * far * near)/(near - far);
            result.elements[3 + 2 * 4] = -1;
            result.elements[3 + 3 * 4] = 0;

            return result;
        }

        Mat4 Mat4::translation(const Vec3 &translation){
            Mat4 result(1.0f);

            result.elements[0 + 3 * 4] = translation.x;
            result.elements[1 + 3 * 4] = translation.y;
            result.elements[2 + 3 * 4] = translation.z;

            return result;
        }

        Mat4 Mat4::roatation(float angle, const Vec3 &axis){
            Mat4 result(1.0f);

            float r = to_Radians(angle);

            float c = cos(r);
            float s = sin(r);
            float omc = 1 - c;

            float x = axis.x;
            float y = axis.y;
            float z = axis.z;

            result.elements[0 + 0 * 4] = x * omc + c;
            result.elements[1 + 0 * 4] = y * x * omc + z * s;
            result.elements[2 + 0 * 4] = z * x * omc - y * s;

            result.elements[0 + 1 * 4] = x * y * omc - z * s;
            result.elements[1 + 1 * 4] = y * omc + c;
            result.elements[2 + 1 * 4] = x * s + y * z * omc;

            result.elements[0 + 2 * 4] = x * z * omc + y * s;
            result.elements[1 + 2 * 4] = y * z * omc - x * s;
            result.elements[2 + 2 * 4] = z * omc + c;

            return result;
        }

        Mat4 Mat4::scale(const Vec3& scale){
            Mat4 result(1.0f);

            result.elements[0 + 0 * 4] = scale.x;
            result.elements[1 + 1 * 4] = scale.y;
            result.elements[2 + 2 * 4] = scale.z;

            return result;
        }

        Mat4& Mat4::multiply(const Mat4& other){

            float data[16];
            for(int y = 0; y < 4; y++){
                for(int x = 0; x < 4; x++){
                    float sum = 0.0f;
                    for(int i = 0; i < 4; i++){
                        sum += elements[x + i * 4] * other.elements[i + y*4];
                    }
                    data[x+y*4] = sum;
                }

            }
            memcpy(elements, data, 16 * 4);

            return *this;
        }

        Mat4 operator*(Mat4 left, const Mat4 &right){
            return left.multiply(right);
        }

        Mat4& Mat4::operator*=(const Mat4& other){
            return multiply(other);
        }


        Vec3 Mat4::multiply(const Vec3 &other) const{
            return Vec3(
                    columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
                    columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
                    columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
            );
        }

        Vec3 operator*(const Mat4& left, const Vec3 &right){
            return left.multiply(right);
        }


        Vec4 Mat4::multiply(const Vec4 &other) const{
            return Vec4(
                    columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
                    columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
                    columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
                    columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
            );

        }

        Vec4 operator*(const Mat4& left, const Vec4 &right){
            return left.multiply(right);
        }

    }
}
#pragma clang diagnostic pop