#pragma once
//  //
// @@t@CÌCN[h@@ //
//  //
#include <DirectXMath.h>


namespace PublicSystem
{
	// Firgbajð\·NX
	class Color
	{
		public:
			// ----- variables / Ï ----- //
			float r = 1.0f;		//   Red / Ô
			float g = 1.0f;		// Green / Î
			float b = 1.0f;		//  Blue / Â
			float a = 1.0f;		// Alpha / §¾x


			// ----- functions / Ö ----- //
			/// <summary>
			/// ÊíRXgN^	</summary>
			Color() {};
			/// <summary>
			/// elÉãüªs¦éRXgN^	</summary>
			///<param name = "_r">
			/// ^ÔFÌ­³	</param>
			///<param name = "_g">
			/// ^ÎFÌ­³	</param>
			///<param name = "_b">
			/// ^ÂFÌ­³	</param>
			///<param name = "_a">
			/// ^§¾xÌ­³	</param>
			Color(float _r, float _g, float _b, float _a);


			// ----- LXgZq ----- //
			// **  XMFLOAT4  ** //
			operator DirectX::XMFLOAT4() const;


	};
}

