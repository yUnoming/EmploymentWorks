#pragma once
/**
* @file		PositionYGizmo.h
* @brief	PositionYGizmoクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.12.31
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "PositionGizmo.h"

/// <summary>
///	エンジン群	</summary>
namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	ギズモ群	</summary>
		namespace Gizmo
		{
			/// <summary>
			///	Y軸移動ギズモ	</summary>
			class PositionYGizmo : public PositionGizmo
			{
				public:
					PositionYGizmo(SceneBase* nowScene) : PositionGizmo(nowScene) {};

					void Init()
					{
						// マテリアル追加
						Material* mat = AddComponent<Material>();
						mat->materialColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
					};

					void ClickAction()
					{
						// Y座標方向へ親オブジェクトを移動
						transform->parent->transform->position.y += (lateCursorPos.y - nowCursorPos.y) * 0.01f;
					}
			};
		}
	}
}

