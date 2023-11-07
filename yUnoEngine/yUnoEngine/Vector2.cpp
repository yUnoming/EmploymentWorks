// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector2.h"

PublicSystem::Vector2 PublicSystem::Vector2::operator=(const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+(int i)
{
    Vector2 tmp;
    tmp.x = x + i;
    tmp.y = y + i;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+(float f)
{
    Vector2 tmp;
    tmp.x = x + f;
    tmp.y = y + f;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+(const Vector2& vec)
{
    Vector2 tmp;
    tmp.x = x + vec.x;
    tmp.y = y + vec.y;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+=(int i)
{
    x += i;
    y += i;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+=(float f)
{
    x += f;
    y += f;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+=(const Vector2& vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-(int i)
{
    Vector2 tmp;
    tmp.x = x - i;
    tmp.y = y - i;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-(float f)
{
    Vector2 tmp;
    tmp.x = x - f;
    tmp.y = y - f;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-(const Vector2& vec)
{
    Vector2 tmp;
    tmp.x = x - vec.x;
    tmp.y = y - vec.y;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-=(int i)
{
    x -= i;
    y -= i;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-=(float f)
{
    x -= f;
    y -= f;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-=(const Vector2& vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*(int i)
{
    Vector2 tmp;
    tmp.x = x * i;
    tmp.y = y * i;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*(float f)
{
    Vector2 tmp;
    tmp.x = x * f;
    tmp.y = y * f;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*(const Vector2& vec)
{
    Vector2 tmp;
    tmp.x = x * vec.x;
    tmp.y = y * vec.y;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*=(int i)
{
    x *= i;
    y *= i;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*=(float f)
{
    x *= f;
    y *= f;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*=(const Vector2& vec)
{
    x *= vec.x;
    y *= vec.y;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/(int i)
{
    Vector2 tmp;
    tmp.x = x / i;
    tmp.y = y / i;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/(float f)
{
    Vector2 tmp;
    tmp.x = x / f;
    tmp.y = y / f;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/(const Vector2& vec)
{
    Vector2 tmp;
    tmp.x = x / vec.x;
    tmp.y = y / vec.y;
    return tmp;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/=(int i)
{
    x /= i;
    y /= i;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/=(float f)
{
    x /= f;
    y /= f;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/=(const Vector2& vec)
{
    x /= vec.x;
    y /= vec.y;
    return *this;
}

bool PublicSystem::Vector2::operator==(const Vector2& vec)
{
    return x == vec.x && y == vec.y;
}

bool PublicSystem::Vector2::operator!=(const Vector2& vec)
{
    return !(x == vec.x && y == vec.y);
}

