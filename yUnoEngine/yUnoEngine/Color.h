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


namespace PublicSystem
{
	/// <summary>
	///	Firgbajπ\·NX	</summary>
	class Color
	{
		public:
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


			// ----- LXgZq ----- //
			// **  XMFLOAT4  ** //
			operator DirectX::XMFLOAT4() const;


	};
}

