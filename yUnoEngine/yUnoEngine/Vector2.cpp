// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector2.h"

PublicSystem::Vector2 PublicSystem::Vector2::operator+(int _i)
{
    Vector2 vec;
    vec.x = x + _i;
    vec.y = y + _i;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+(float _f)
{
    Vector2 vec;
    vec.x = x + _f;
    vec.y = y + _f;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+(const Vector2& _vec)
{
    Vector2 vec;
    vec.x = x + _vec.x;
    vec.y = y + _vec.y;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+=(int _i)
{
    x += _i;
    y += _i;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+=(float _f)
{
    x += _f;
    y += _f;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator+=(const Vector2& _vec)
{
    x += _vec.x;
    y += _vec.y;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-(int _i)
{
    Vector2 vec;
    vec.x = vec.x - _i;
    vec.y = vec.y - _i;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-(float _f)
{
    Vector2 vec;
    vec.x = vec.x - _f;
    vec.y = vec.y - _f;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-(const Vector2& _vec)
{
    Vector2 vec;
    vec.x = vec.x - _vec.x;
    vec.y = vec.y - _vec.y;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-=(int _i)
{
    x -= _i;
    y -= _i;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-=(float _f)
{
    x -= _f;
    y -= _f;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator-=(const Vector2& _vec)
{
    x -= _vec.x;
    y -= _vec.y;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*(int _i)
{
    Vector2 vec;
    vec.x = vec.x * _i;
    vec.y = vec.y * _i;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*(float _f)
{
    Vector2 vec;
    vec.x = vec.x * _f;
    vec.y = vec.y * _f;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*(const Vector2& _vec)
{
    Vector2 vec;
    vec.x = vec.x * _vec.x;
    vec.y = vec.y * _vec.y;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*=(int _i)
{
    x *= _i;
    y *= _i;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*=(float _f)
{
    x *= _f;
    y *= _f;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator*=(const Vector2& _vec)
{
    x *= _vec.x;
    y *= _vec.y;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/(int _i)
{
    Vector2 vec;
    vec.x = vec.x / _i;
    vec.y = vec.y / _i;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/(float _f)
{
    Vector2 vec;
    vec.x = vec.x / _f;
    vec.y = vec.y / _f;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/(const Vector2& _vec)
{
    Vector2 vec;
    vec.x = vec.x / _vec.x;
    vec.y = vec.y / _vec.y;
    return vec;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/=(int _i)
{
    x /= _i;
    y /= _i;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/=(float _f)
{
    x /= _f;
    y /= _f;
    return *this;
}

PublicSystem::Vector2 PublicSystem::Vector2::operator/=(const Vector2& _vec)
{
    x /= _vec.x;
    y /= _vec.y;
    return *this;
}

bool PublicSystem::Vector2::operator==(const Vector2& _vec)
{
    return x == _vec.x && y == _vec.y;
}

bool PublicSystem::Vector2::operator!=(const Vector2& _vec)
{
    return !(x == _vec.x && y == _vec.y);
}

