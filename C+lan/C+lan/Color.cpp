#include "Color.h"
#include <direct.h>
#include <DirectXMath.h>

Ctlan::PublicSystem::Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
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

Ctlan::PublicSystem::Color::operator DirectX::XMFLOAT4() const
{
	DirectX::XMFLOAT4 New_Param = DirectX::XMFLOAT4(r, g, b, a);
	return New_Param;
}

const Ctlan::PublicSystem::Color Ctlan::PublicSystem::Color::GetColor(ColorType colorType)
{
	switch (colorType)
	{
		case ColorType::Red:
			return Color(1.0f, 0.0f, 0.0f, 1.0f);
		case ColorType::Green:
			return Color(0.0f, 1.01, 0.0f, 1.0f);
		case ColorType::Blue:
			return Color(0.0f, 0.01, 1.0f, 1.0f);
		case ColorType::Yellow:
			return Color(1.0f, 1.01, 0.0f, 1.0f);
		case ColorType::Cyan:
			return Color(0.0f, 1.0f, 1.0f, 1.0f);
		case ColorType::Magenta:
			return Color(1.0f, 0.0f, 1.0f, 1.0f);
		case ColorType::Orange:
			return Color(1.0f, 0.5f, 0.0f, 1.0f);
		case ColorType::Pink:
			return Color(1.0f, 0.753f, 0.796, 1.0f);
		case ColorType::White:
			return Color(1.0f, 1.0f, 1.0f, 1.0f);
		case ColorType::Black:
			return Color(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
