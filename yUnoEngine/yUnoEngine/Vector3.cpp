// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector3.h"
#include <DirectXMath.h>

PublicSystem::Vector3 PublicSystem::Vector3::operator=(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator=(const DirectX::XMFLOAT3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+(int i)
{
    Vector3 tmp;
    tmp.x = x + i;
    tmp.y = y + i;
    tmp.z = z + i;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+(float f)
{
    Vector3 tmp;
    tmp.x = x + f;
    tmp.y = y + f;
    tmp.z = z + f;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+(const Vector3 &vec)
{
    Vector3 tmp;
    tmp.x = x + vec.x;
    tmp.y = y + vec.y;
    tmp.z = z + vec.z;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+=(int i)
{
    x += i;
    y += i;
    z += i;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+=(float f)
{
    x += f;
    y += f;
    z += f;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator+=(const DirectX::XMFLOAT3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-(int i)
{
    Vector3 tmp;
    tmp.x = x - i;
    tmp.y = y - i;
    tmp.z = z - i;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-(float f)
{
    Vector3 tmp;
    tmp.x = x - f;
    tmp.y = y - f;
    tmp.z = z - f;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-(const Vector3& vec)
{
    Vector3 tmp;
    tmp.x = x - vec.x;
    tmp.y = y - vec.y;
    tmp.z = z - vec.z;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-=(int i)
{
    x -= i;
    y -= i;
    z -= i;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-=(float f)
{
    x -= f;
    y -= f;
    z -= f;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator-=(const Vector3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*(int i)
{
    Vector3 tmp;
    tmp.x = x * i;
    tmp.y = y * i;
    tmp.z = z * i;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*(float f)
{
    Vector3 tmp;
    tmp.x = x * f;
    tmp.y = y * f;
    tmp.z = z * f;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*(const Vector3& vec)
{
    Vector3 tmp;
    tmp.x = x * vec.x;
    tmp.y = y * vec.y;
    tmp.z = z * vec.z;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*=(int i)
{
    x *= i;
    y *= i;
    z *= i;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*=(const Vector3& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator*=(const DirectX::XMFLOAT3& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/(int i)
{
    Vector3 tmp;
    tmp.x = x / i;
    tmp.y = y / i;
    tmp.z = z / i;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/(float f)
{
    Vector3 tmp;
    tmp.x = x / f;
    tmp.y = y / f;
    tmp.z = z / f;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/(const Vector3& vec)
{
    Vector3 tmp;
    tmp.x = x / vec.x;
    tmp.y = y / vec.y;
    tmp.z = z / vec.z;
    return tmp;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/=(int i)
{
    x /= i;
    y /= i;
    z /= i;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/=(float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

PublicSystem::Vector3 PublicSystem::Vector3::operator/=(const Vector3& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

bool PublicSystem::Vector3::operator==(const Vector3& vec)
{
    return x == vec.x && y == vec.y && z == vec.z;
}

bool PublicSystem::Vector3::operator!=(const Vector3& vec)
{
    return !(x == vec.x && y == vec.y && z == vec.z);
}

PublicSystem::Vector3::operator DirectX::XMFLOAT3() const
{
    DirectX::XMFLOAT3 newParam = DirectX::XMFLOAT3(x, y, z);
    return newParam;
}
