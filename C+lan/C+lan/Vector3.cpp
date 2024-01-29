// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "Vector3.h"
#include <DirectXMath.h>

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::Rotate(const Vector3 &rotation)
{
    DirectX::XMFLOAT3 newVec = DirectX::XMFLOAT3(x, y, z);
    DirectX::XMVECTOR rotateVec = DirectX::XMLoadFloat3(&newVec);

    // ��]�s����쐬
    DirectX::XMMATRIX mtxRotation =
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(rotation.z)) *
        DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(rotation.y));

    // ��]�s����g���x�N�g����ϊ�
    rotateVec = DirectX::XMVector3TransformCoord(rotateVec, mtxRotation);
    DirectX::XMStoreFloat3(&newVec, rotateVec);
    
    // �l����
    x = newVec.x;
    y = newVec.y;
    z = newVec.z;
    return *this;
}

void Ctlan::PublicSystem::Vector3::Normalize()
{
    // �x�N�g���̒��������߂�
    float length = sqrtf(x * x + y * y + z * z);
    // ������0�łȂ��ꍇ�A�e�l�𒷂��Ŋ���
    if (length != 0.0f)
    {
        x /= length;
        y /= length;
        z /= length;
    }
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator=(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator=(const DirectX::XMFLOAT3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator+(int i)
{
    Vector3 tmp;
    tmp.x = x + i;
    tmp.y = y + i;
    tmp.z = z + i;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator+(float f)
{
    Vector3 tmp;
    tmp.x = x + f;
    tmp.y = y + f;
    tmp.z = z + f;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator+(const Vector3 &vec)
{
    Vector3 tmp;
    tmp.x = x + vec.x;
    tmp.y = y + vec.y;
    tmp.z = z + vec.z;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator+=(int i)
{
    x += i;
    y += i;
    z += i;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator+=(float f)
{
    x += f;
    y += f;
    z += f;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator+=(const DirectX::XMFLOAT3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator-(int i)
{
    Vector3 tmp;
    tmp.x = x - i;
    tmp.y = y - i;
    tmp.z = z - i;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator-(float f)
{
    Vector3 tmp;
    tmp.x = x - f;
    tmp.y = y - f;
    tmp.z = z - f;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator-(const Vector3& vec)
{
    Vector3 tmp;
    tmp.x = x - vec.x;
    tmp.y = y - vec.y;
    tmp.z = z - vec.z;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator-=(int i)
{
    x -= i;
    y -= i;
    z -= i;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator-=(float f)
{
    x -= f;
    y -= f;
    z -= f;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator-=(const Vector3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator*(int i)
{
    Vector3 tmp;
    tmp.x = x * i;
    tmp.y = y * i;
    tmp.z = z * i;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator*(float f)
{
    Vector3 tmp;
    tmp.x = x * f;
    tmp.y = y * f;
    tmp.z = z * f;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator*(const Vector3& vec)
{
    Vector3 tmp;
    tmp.x = x * vec.x;
    tmp.y = y * vec.y;
    tmp.z = z * vec.z;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator*=(int i)
{
    x *= i;
    y *= i;
    z *= i;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator*=(const Vector3& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator*=(const DirectX::XMFLOAT3& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator/(int i)
{
    Vector3 tmp;
    tmp.x = x / i;
    tmp.y = y / i;
    tmp.z = z / i;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator/(float f)
{
    Vector3 tmp;
    tmp.x = x / f;
    tmp.y = y / f;
    tmp.z = z / f;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator/(const Vector3& vec)
{
    Vector3 tmp;
    tmp.x = x / vec.x;
    tmp.y = y / vec.y;
    tmp.z = z / vec.z;
    return tmp;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator/=(int i)
{
    x /= i;
    y /= i;
    z /= i;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator/=(float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

Ctlan::PublicSystem::Vector3 Ctlan::PublicSystem::Vector3::operator/=(const Vector3& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

bool Ctlan::PublicSystem::Vector3::operator==(const Vector3& vec)
{
    return x == vec.x && y == vec.y && z == vec.z;
}

bool Ctlan::PublicSystem::Vector3::operator!=(const Vector3& vec)
{
    return !(x == vec.x && y == vec.y && z == vec.z);
}

Ctlan::PublicSystem::Vector3::operator DirectX::XMFLOAT3() const
{
    DirectX::XMFLOAT3 newParam = DirectX::XMFLOAT3(x, y, z);
    return newParam;
}
