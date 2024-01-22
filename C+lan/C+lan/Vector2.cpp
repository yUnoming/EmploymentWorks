// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector2.h"

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator=(const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator+(int i)
{
    Vector2 tmp;
    tmp.x = x + i;
    tmp.y = y + i;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator+(float f)
{
    Vector2 tmp;
    tmp.x = x + f;
    tmp.y = y + f;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator+(const Vector2& vec)
{
    Vector2 tmp;
    tmp.x = x + vec.x;
    tmp.y = y + vec.y;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator+=(int i)
{
    x += i;
    y += i;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator+=(float f)
{
    x += f;
    y += f;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator+=(const Vector2& vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator-(int i)
{
    Vector2 tmp;
    tmp.x = x - i;
    tmp.y = y - i;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator-(float f)
{
    Vector2 tmp;
    tmp.x = x - f;
    tmp.y = y - f;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator-(const Vector2& vec)
{
    Vector2 tmp;
    tmp.x = x - vec.x;
    tmp.y = y - vec.y;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator-=(int i)
{
    x -= i;
    y -= i;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator-=(float f)
{
    x -= f;
    y -= f;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator-=(const Vector2& vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator*(int i)
{
    Vector2 tmp;
    tmp.x = x * i;
    tmp.y = y * i;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator*(float f)
{
    Vector2 tmp;
    tmp.x = x * f;
    tmp.y = y * f;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator*(const Vector2& vec)
{
    Vector2 tmp;
    tmp.x = x * vec.x;
    tmp.y = y * vec.y;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator*=(int i)
{
    x *= i;
    y *= i;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator*=(float f)
{
    x *= f;
    y *= f;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator*=(const Vector2& vec)
{
    x *= vec.x;
    y *= vec.y;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator/(int i)
{
    Vector2 tmp;
    tmp.x = x / i;
    tmp.y = y / i;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator/(float f)
{
    Vector2 tmp;
    tmp.x = x / f;
    tmp.y = y / f;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator/(const Vector2& vec)
{
    Vector2 tmp;
    tmp.x = x / vec.x;
    tmp.y = y / vec.y;
    return tmp;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator/=(int i)
{
    x /= i;
    y /= i;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator/=(float f)
{
    x /= f;
    y /= f;
    return *this;
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::Vector2::operator/=(const Vector2& vec)
{
    x /= vec.x;
    y /= vec.y;
    return *this;
}

bool Ctlan::PublicSystem::Vector2::operator==(const Vector2& vec)
{
    return x == vec.x && y == vec.y;
}

bool Ctlan::PublicSystem::Vector2::operator!=(const Vector2& vec)
{
    return !(x == vec.x && y == vec.y);
}

Ctlan::PublicSystem::Vector2::operator Ctlan::PublicSystem::Vector3() const
{
    Vector3 newVec = Vector3(x, y);
    return newVec;
}

