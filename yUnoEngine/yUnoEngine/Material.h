#pragma once
//  //
// @@t@CÌCN[h@@ //
//  //
#include "EachFunction.h"
#include "Color.h"

namespace PublicSystem
{
	// IuWFNgÌFE¿´ÈÇð\·NX
	class Material : public EachFunction
	{
		public:
			// ----- variables / Ï ----- //
			Color Material_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);	// }eAÌF

			// ----- functions / Ö ----- //
			void Draw();

			/// <summary>
			/// }eAÌFðÏX·é	</summary>
			/// <param name = "_colorParam">
			///	RGBAðlÅwè	</param>
			void SetMateiralColor(PublicSystem::Color _colorParam);
	};
}

