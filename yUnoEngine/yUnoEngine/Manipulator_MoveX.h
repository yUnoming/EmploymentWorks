#pragma once
/**
* @file		Manipulator_MoveX.h
* @brief	Manipulator_MoveXNXÌwb_[t@C
* @author	Kojima, Kosei
* @date		2023.12.24
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
		///	XÀWûüÌÚ®}js[^[	</summary>
		class Manipulator_MoveX : public Manipulator
		{
			public :
				void Init()
				{
					// }eAÇÁ
					Material *mat = AddComponent<Material>();
					mat->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
					transform->rotation.z = -90.0f;
				};

				void ClickAction()
				{
					// XÀWûüÖeIuWFNgðÚ®
					transform->parent->transform->position.x -= (lateCursorPos.x - nowCursorPos.x) * 0.01f;
				}
		};
	}
}


