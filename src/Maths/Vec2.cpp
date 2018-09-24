//
// Created by grzegorz on 21.09.18.
//

#include "Vec2.h"


namespace engine{
    namespace maths{

        Vec2::Vec2(){
            x = 0.0f;
            y = 0.0f;
        }

        Vec2::Vec2(const float &x, const float &y){
            this->x = x;
            this->y = y;
        }

        Vec2& Vec2::add(const Vec2 &other){
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2& Vec2::subtract(const Vec2 &other){
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vec2& Vec2::multiply(const Vec2 &other){
            x *= other.x;
            y *= other.y;
            return *this;
        }

        Vec2& Vec2::divide(const Vec2 &other){
            x /= other.x;
            y /= other.y;
            return *this;
        }

        Vec2& Vec2::operator+=(const Vec2 &right){
            return add(right);
        }

        Vec2& Vec2::operator-=(const Vec2 &right){
            return subtract(right);
        }

        Vec2& Vec2::operator*=(const Vec2 &right){
            return multiply(right);
        }

        Vec2& Vec2::operator/=(const Vec2 &right){
            return divide(right);
        }

        bool Vec2::operator==(const Vec2 &other){
            return x == other.x && y == other.y;
        }

        bool Vec2::operator!=(const Vec2 &other){
            return !(x == other.x && y == other.y);
        }

        Vec2 operator+(Vec2 left, const Vec2& right){
            return left.add(right);
        }

        Vec2 operator-(Vec2 left, const Vec2 &right){
            return left.subtract(right);
        }

        Vec2 operator*(Vec2 left, const Vec2 &right){
            return left.multiply(right);
        }

        Vec2 operator/(Vec2 left, const Vec2 &right){
            return left.divide(right);
        }





        std::ostream& operator<<(std::ostream& stream, const Vec2 & vector){
            stream << "vec2: (" << vector.x << ", " << vector.y << ")";
            return stream;
        }

    }
}