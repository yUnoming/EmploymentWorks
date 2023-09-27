#include "Color.h"
#include <direct.h>
#include <DirectXMath.h>

PublicSystem::Color::Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a)
{
	// ===== �l���O�`�P�͈̔͂Ɏ��߂� ===== //
	// ----- �ԐF ----- //
	if (r < 0.f)	// �O�ȉ��H
		r = 0.f;
	if (r > 1.f)	// �P�ȏ�H
		r = 1.f;

	// ----- �F ----- //
	if (g < 0.f)	// �O�ȉ��H
		g = 0.f;
	if (g > 1.f)	// �P�ȏ�H
		g = 1.f;

	// ----- �ΐF ----- //
	if (b < 0.f)	// �O�ȉ��H
		b = 0.f;
	if (b > 1.f)	// �P�ȏ�H
		b = 1.f;

	// ----- �����x ----- //
	if (a < 0.f)	// �O�ȉ��H
		a = 0.f;
	if (a > 1.f)	// �P�ȏ�H
		a = 1.f;
}

PublicSystem::Color::operator DirectX::XMFLOAT4() const
{
	DirectX::XMFLOAT4 New_Param = DirectX::XMFLOAT4(r, g, b, a);
	return New_Param;
}
