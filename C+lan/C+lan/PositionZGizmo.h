#pragma once
/**
* @file		PositionZGizmo.h
* @brief	PositionZGizmoNXÌwb_[t@C
* @author	Kojima, Kosei
* @date		2024.1.3
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
			///	Z²Ú®MY	</summary>
			class PositionZGizmo : public PositionGizmo
			{
			public:
				PositionZGizmo(SceneBase* nowScene) : PositionGizmo(nowScene) {};

				void Init()
				{
					// }eAJ[ÏX
					mat->materialColor = Color(0.0f, 0.0f, 1.0f, 1.0f);
					transform->rotation.x = 90.0f;
				};

				void ClickAction()
				{
					// WApÉ¼·a
					float rotX = spectatorCamera->transform->rotation.x * 3.14f / 180.0f;
					float rotY = spectatorCamera->transform->rotation.y * 3.14f / 180.0f;
					// }EXÌÀWð³ÉÚ®ÊðvZ
					float addX = sinf(rotY) * (lateCursorPos.x - nowCursorPos.x) * 0.01f;
					float addY = cosf(rotY) * (lateCursorPos.y - nowCursorPos.y) * 0.01f;

					// ZÀWûüÖeIuWFNgðÚ®
					transform->parent->transform->position.z += addX + addY;
				}
			};
		}
	}
}