#pragma once
/**
* @file		Material.h
* @brief	MaterialNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.02
*/
//  //
// @@t@CΜCN[h@@ //
//  //
#include "EachFunction.h"
#include "Color.h"

namespace PublicSystem
{
	/// <summary>
	/// IuWFNgΜFEΏ΄ΘΗπ\·NX	</summary>
	class Material : public EachFunction
	{
		public:
			// ----- variables / Ο ----- //
			/// <summary>
			///}eAΜF	</summary>
			Color materialColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

			// ----- functions / Φ ----- //
			/// <summary>
			/// `ζ	</summary>
			void Draw();

			/// <summary>
			/// }eAΜFπΟX·ι	</summary>
			/// <param name = "_colorParam">
			///	RGBAΜliColorNXIuWFNgΕwθj	</param>
			void SetMaterialColor(PublicSystem::Color colorParam);
	};
}

