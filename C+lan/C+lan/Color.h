#pragma once
/**
* @file		Color.h
* @brief	ColorNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.05
*/
//  //
// @@t@CΜCN[h@@ //
//  //
#include <DirectXMath.h>

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	Firgbajπ\·NX	</summary>
		class Color
		{
			public:
				// ----- enum / ρ^ ----- //
				/// <summary>
				///	FΜνή	</summary>
				enum ColorType
				{
					Red,
					Green,
					Blue,
					Yellow,
					Cyan,
					Magenta,
					Orange,
					Pink,
					White,
					Black,
				};

				// ----- variables / Ο ----- //
				/// <summary>
				///	Red / Τ	</summary>
				float r = 1.0f;
				/// <summary>
				///	Green / Ξ	</summary>
				float g = 1.0f;
				/// <summary>
				///	Blue / Β	</summary>
				float b = 1.0f;
				/// <summary>
				///	Alpha / §Ύx	</summary>
				float a = 1.0f;


				// ----- functions / Φ ----- //
				/// <summary>
				/// ΚνRXgN^	</summary>
				Color() {};
				/// <summary>
				/// ψt«RXgN^	</summary>
				///<param name = "r">
				/// ΤFΜ­³	</param>
				///<param name = "g">
				/// ΞFΜ­³	</param>
				///<param name = "b">
				/// ΒFΜ­³	</param>
				///<param name = "a">
				/// §ΎxΜ­³	</param>
				Color(float r, float g, float b, float a);

				/// <summary>
				///	J[Μνή©ηlπζΎ	</summary>
				/// <param name="colorType">
				/// J[Μνή	</param>
				/// <returns>
				/// J[l(R,G,B,A)</returns>
				static const Ctlan::PublicSystem::Color GetColor(ColorType colorType);

				// ----- LXgZq ----- //
				// **  XMFLOAT4  ** //
				operator DirectX::XMFLOAT4() const;
		};
	}
}