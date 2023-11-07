#include "Color.h"
#include <direct.h>
#include <DirectXMath.h>

PublicSystem::Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
{
	// ===== �l���O�`�P�͈̔͂Ɏ��߂� ===== //
	// ----- �ԐF ----- //
	if (r < 0.f)	// �O�ȉ��H
		this->r = 0.f;
	if (r > 1.f)	// �P�ȏ�H
		this->r = 1.f;

	// ----- �F ----- //
	if (g < 0.f)	// �O�ȉ��H
		this->g = 0.f;
	if (g > 1.f)	// �P�ȏ�H
		this->g = 1.f;

	// ----- �ΐF ----- //
	if (b < 0.f)	// �O�ȉ��H
		this->b = 0.f;
	if (b > 1.f)	// �P�ȏ�H
		this->b = 1.f;

	// ----- �����x ----- //
	if (a < 0.f)	// �O�ȉ��H
		this->a = 0.f;
	if (a > 1.f)	// �P�ȏ�H
		this->a = 1.f;
}

PublicSystem::Color::operator DirectX::XMFLOAT4() const
{
	DirectX::XMFLOAT4 New_Param = DirectX::XMFLOAT4(r, g, b, a);
	return New_Param;
}
