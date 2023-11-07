#include "Color.h"
#include <direct.h>
#include <DirectXMath.h>

PublicSystem::Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
{
	// ===== ’l‚ğ‚O`‚P‚Ì”ÍˆÍ‚Éû‚ß‚é ===== //
	// ----- ÔF ----- //
	if (r < 0.f)	// ‚OˆÈ‰ºH
		this->r = 0.f;
	if (r > 1.f)	// ‚PˆÈãH
		this->r = 1.f;

	// ----- ÂF ----- //
	if (g < 0.f)	// ‚OˆÈ‰ºH
		this->g = 0.f;
	if (g > 1.f)	// ‚PˆÈãH
		this->g = 1.f;

	// ----- —ÎF ----- //
	if (b < 0.f)	// ‚OˆÈ‰ºH
		this->b = 0.f;
	if (b > 1.f)	// ‚PˆÈãH
		this->b = 1.f;

	// ----- “§–¾“x ----- //
	if (a < 0.f)	// ‚OˆÈ‰ºH
		this->a = 0.f;
	if (a > 1.f)	// ‚PˆÈãH
		this->a = 1.f;
}

PublicSystem::Color::operator DirectX::XMFLOAT4() const
{
	DirectX::XMFLOAT4 New_Param = DirectX::XMFLOAT4(r, g, b, a);
	return New_Param;
}
