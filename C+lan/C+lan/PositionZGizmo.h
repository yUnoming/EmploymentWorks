#pragma once
/**
* @file		PositionZGizmo.h
* @brief	PositionZGizmoクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2024.1.3
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
			///	Z軸移動ギズモ	</summary>
			class PositionZGizmo : public PositionGizmo
			{
			public:
				PositionZGizmo(SceneBase* nowScene) : PositionGizmo(nowScene) {};

				void Init()
				{
					// マテリアルカラー変更
					mat->materialColor = Color(0.0f, 0.0f, 1.0f, 1.0f);
					transform->rotation.x = 90.0f;
				};

				void ClickAction()
				{
					// ラジアン角に直すa
					float rotX = spectatorCamera->transform->rotation.x * 3.14f / 180.0f;
					float rotY = spectatorCamera->transform->rotation.y * 3.14f / 180.0f;
					// マウスの座標を元に移動量を計算
					float addX = sinf(rotY) * (lateCursorPos.x - nowCursorPos.x) * 0.01f;
					float addY = cosf(rotY) * (lateCursorPos.y - nowCursorPos.y) * 0.01f;

					// Z座標方向へ親オブジェクトを移動
					transform->parent->transform->position.z += addX + addY;
				}
			};
		}
	}
}