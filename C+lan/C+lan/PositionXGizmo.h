#pragma once
/**
* @file		PositionXGizmo.h
* @brief	PositionXGizmoNXÌwb_[t@C
* @author	Kojima, Kosei
* @date		2023.12.24
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
			///	X²Ú®MY	</summary>
			class PositionXGizmo : public PositionGizmo
			{
				public:
					PositionXGizmo(SceneBase* nowScene) : PositionGizmo(nowScene) {};

					void Init()
					{
						// }eAJ[ÏX
						mat->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
						transform->rotation.z = -90.0f;
					};

					void ClickAction()
					{
						// WApÉ¼·
						float rotY = spectatorCamera->transform->rotation.y * 3.14f / 180.0f;
						// }EXÌÀWð³ÉÚ®ÊðvZ
						float addX = cosf(rotY) * (lateCursorPos.x - nowCursorPos.x) * -0.01f;
						float addY = sinf(rotY) * (lateCursorPos.y - nowCursorPos.y) * 0.01f;

						// XÀWûüÖeIuWFNgðÚ®
						transform->parent->transform->position.x += addX + addY;
					}
			};
		}

	}
}


