#include "Color.h"
#include <direct.h>
#include <DirectXMath.h>

PublicSystem::Color::Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a)
{
	// ===== ’l‚ğ‚O`‚P‚Ì”ÍˆÍ‚Éû‚ß‚é ===== //
	// ----- ÔF ----- //
	if (r < 0.f)	// ‚OˆÈ‰ºH
		r = 0.f;
	if (r > 1.f)	// ‚PˆÈãH
		r = 1.f;

	// ----- ÂF ----- //
	if (g < 0.f)	// ‚OˆÈ‰ºH
		g = 0.f;
	if (g > 1.f)	// ‚PˆÈãH
		g = 1.f;

	// ----- —ÎF ----- //
	if (b < 0.f)	// ‚OˆÈ‰ºH
		b = 0.f;
	if (b > 1.f)	// ‚PˆÈãH
		b = 1.f;

	// ----- “§–¾“x ----- //
	if (a < 0.f)	// ‚OˆÈ‰ºH
		a = 0.f;
	if (a > 1.f)	// ‚PˆÈãH
		a = 1.f;
}

PublicSystem::Color::operator DirectX::XMFLOAT4() const
{
	DirectX::XMFLOAT4 New_Param = DirectX::XMFLOAT4(r, g, b, a);
	return New_Param;
}
