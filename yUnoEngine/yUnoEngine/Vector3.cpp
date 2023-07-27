// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector3.h"

PublicSystem::Vector3 PublicSystem::Vector3::operator+(int _i)
{
    Vector3 vec;
    vec.x = x + _i;
    vec.y = y + _i;
    vec.z = z + _i;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+(float _f)
{
    Vector3 vec;
    vec.x = x + _f;
    vec.y = y + _f;
    vec.z = z + _f;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+(const Vector3 &_vec)
{
    Vector3 vec;
    vec.x = x + _vec.x;
    vec.y = y + _vec.y;
    vec.z = z + _vec.z;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+=(int _i)
{
    x += _i;
    y += _i;
    z += _i;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+=(float _f)
{
    x += _f;
    y += _f;
    z += _f;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+=(const Vector3& _vec)
{
    x += _vec.x;
    y += _vec.y;
    z += _vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-(int _i)
{
    Vector3 vec;
    vec.x = vec.x - _i;
    vec.y = vec.y - _i;
    vec.z = vec.z - _i;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-(float _f)
{
    Vector3 vec;
    vec.x = vec.x - _f;
    vec.y = vec.y - _f;
    vec.z = vec.z - _f;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-(const Vector3& _vec)
{
    Vector3 vec;
    vec.x = vec.x - _vec.x;
    vec.y = vec.y - _vec.y;
    vec.z = vec.z - _vec.z;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-=(int _i)
{
    x -= _i;
    y -= _i;
    z -= _i;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-=(float _f)
{
    x -= _f;
    y -= _f;
    z -= _f;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-=(const Vector3& _vec)
{
    x -= _vec.x;
    y -= _vec.y;
    z -= _vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*(int _i)
{
    Vector3 vec;
    vec.x = vec.x * _i;
    vec.y = vec.y * _i;
    vec.z = vec.z * _i;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*(float _f)
{
    Vector3 vec;
    vec.x = vec.x * _f;
    vec.y = vec.y * _f;
    vec.z = vec.z * _f;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*(const Vector3& _vec)
{
    Vector3 vec;
    vec.x = vec.x * _vec.x;
    vec.y = vec.y * _vec.y;
    vec.z = vec.z * _vec.z;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*=(int _i)
{
    x *= _i;
    y *= _i;
    z *= _i;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*=(float _f)
{
    x *= _f;
    y *= _f;
    z *= _f;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*=(const Vector3& _vec)
{
    x *= _vec.x;
    y *= _vec.y;
    z *= _vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/(int _i)
{
    Vector3 vec;
    vec.x = vec.x / _i;
    vec.y = vec.y / _i;
    vec.z = vec.z / _i;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/(float _f)
{
    Vector3 vec;
    vec.x = vec.x / _f;
    vec.y = vec.y / _f;
    vec.z = vec.z / _f;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/(const Vector3& _vec)
{
    Vector3 vec;
    vec.x = vec.x / _vec.x;
    vec.y = vec.y / _vec.y;
    vec.z = vec.z / _vec.z;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/=(int _i)
{
    x /= _i;
    y /= _i;
    z /= _i;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/=(float _f)
{
    x /= _f;
    y /= _f;
    z /= _f;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/=(const Vector3& _vec)
{
    x /= _vec.x;
    y /= _vec.y;
    z /= _vec.z;
    return *this;
}

bool PublicSystem::Vector3::operator==(const Vector3& _vec)
{
    return x == _vec.x && y == _vec.y && z == _vec.z;
}

bool PublicSystem::Vector3::operator!=(const Vector3& _vec)
{
    return !(x == _vec.x && y == _vec.y && z == _vec.z);
}
