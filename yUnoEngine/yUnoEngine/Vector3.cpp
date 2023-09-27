// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector3.h"
#include <DirectXMath.h>

PublicSystem::Vector3 PublicSystem::Vector3::operator=(const Vector3& _vec)
{
    x = _vec.x;
    y = _vec.y;
    z = _vec.z;
    return *this;
}

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
    vec.x = x - _i;
    vec.y = y - _i;
    vec.z = z - _i;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-(float _f)
{
    Vector3 vec;
    vec.x = x - _f;
    vec.y = y - _f;
    vec.z = z - _f;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-(const Vector3& _vec)
{
    Vector3 vec;
    vec.x = x - _vec.x;
    vec.y = y - _vec.y;
    vec.z = z - _vec.z;
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
    vec.x = x * _i;
    vec.y = y * _i;
    vec.z = z * _i;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*(float _f)
{
    Vector3 vec;
    vec.x = x * _f;
    vec.y = y * _f;
    vec.z = z * _f;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*(const Vector3& _vec)
{
    Vector3 vec;
    vec.x = x * _vec.x;
    vec.y = y * _vec.y;
    vec.z = z * _vec.z;
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
    vec.x = x / _i;
    vec.y = y / _i;
    vec.z = z / _i;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/(float _f)
{
    Vector3 vec;
    vec.x = x / _f;
    vec.y = y / _f;
    vec.z = z / _f;
    return vec;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/(const Vector3& _vec)
{
    Vector3 vec;
    vec.x = x / _vec.x;
    vec.y = y / _vec.y;
    vec.z = z / _vec.z;
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

PublicSystem::Vector3::operator DirectX::XMFLOAT3() const
{
    DirectX::XMFLOAT3 New_Param = DirectX::XMFLOAT3(x, y, z);
    return New_Param;
}
