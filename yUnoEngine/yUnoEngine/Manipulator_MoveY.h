#pragma once
/**
* @file		Manipulator_MoveY.h
* @brief	Manipulator_MoveYNXÌwb_[t@C
* @author	Kojima, Kosei
* @date		2023.12.31
*/
//  //
// @@t@CÌCN[h@@ //
//  //
#include "Manipulator.h"

/// <summary>
///	GWQ	</summary>
namespace yUnoEngine
{
	/// <summary>
	///	}js[^[Q	</summary>
	namespace Manipulator
	{
		/// <summary>
		///	YÀWûüÌÚ®}js[^[	</summary>
		class Manipulator_MoveY : public Manipulator
		{
			public:
				void Init()
				{
					// }eAÇÁ
					Material* mat = AddComponent<Material>();
					mat->materialColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
				};

				void ClickAction()
				{
					// YÀWûüÖeIuWFNgðÚ®
					transform->parent->transform->position.y += (lateCursorPos.y - nowCursorPos.y) * 0.01f;
				}
		};
	}
}

