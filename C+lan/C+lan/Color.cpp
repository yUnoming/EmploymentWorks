#include "Color.h"
#include <direct.h>
#include <DirectXMath.h>

Ctlan::PublicSystem::Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
{
	// ===== 値を０～１の範囲に収める ===== //
	// ----- 赤色 ----- //
	if (r < 0.f)	// ０以下？
		this->r = 0.f;
	if (r > 1.f)	// １以上？
		this->r = 1.f;

	// ----- 青色 ----- //
	if (g < 0.f)	// ０以下？
		this->g = 0.f;
	if (g > 1.f)	// １以上？
		this->g = 1.f;

	// ----- 緑色 ----- //
	if (b < 0.f)	// ０以下？
		this->b = 0.f;
	if (b > 1.f)	// １以上？
		this->b = 1.f;

	// ----- 透明度 ----- //
	if (a < 0.f)	// ０以下？
		this->a = 0.f;
	if (a > 1.f)	// １以上？
		this->a = 1.f;
}

Ctlan::PublicSystem::Color::operator DirectX::XMFLOAT4() const
{
	DirectX::XMFLOAT4 newParam = DirectX::XMFLOAT4(r, g, b, a);
	return newParam;
}

const Ctlan::PublicSystem::Color Ctlan::PublicSystem::Color::GetColor(ColorType colorType)
{
	// 色のタイプにより処理を分岐
	switch (colorType)
	{
		case ColorType::Red:
			return Color(1.0f, 0.0f, 0.0f, 1.0f);
		case ColorType::Green:
			return Color(0.0f, 1.0f, 0.0f, 1.0f);
		case ColorType::Blue:
			return Color(0.0f, 0.0f, 1.0f, 1.0f);
		case ColorType::Yellow:
			return Color(1.0f, 1.0f, 0.0f, 1.0f);
		case ColorType::Cyan:
			return Color(0.0f, 1.0f, 1.0f, 1.0f);
		case ColorType::Magenta:
			return Color(1.0f, 0.0f, 1.0f, 1.0f);
		case ColorType::Orange:
			return Color(1.0f, 0.5f, 0.0f, 1.0f);
		case ColorType::Pink:
			return Color(1.0f, 0.753f, 0.796f, 1.0f);
		case ColorType::White:
			return Color(1.0f, 1.0f, 1.0f, 1.0f);
		case ColorType::Black:
			return Color(0.0f, 0.0f, 0.0f, 1.0f);
	}
	
	// 色の種類にない値の場合、初期カラーを返す
	return Color();
}
