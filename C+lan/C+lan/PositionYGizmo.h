#pragma once
/**
* @file		PositionYGizmo.h
* @brief	PositionYGizmoNXÌwb_[t@C
* @author	Kojima, Kosei
* @date		2023.12.31
*/
//  //
// @@t@CÌCN[h@@ //
//  //
#include "PositionGizmo.h"

/// <summary>
///	GWQ	</summary>
namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	MYQ	</summary>
		namespace Gizmo
		{
			/// <summary>
			///	Y²Ú®MY	</summary>
			class PositionYGizmo : public PositionGizmo
			{
				public:
					PositionYGizmo(SceneBase* nowScene) : PositionGizmo(nowScene) {};

					void Init()
					{
						// }eAJ[ÏX
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
}

