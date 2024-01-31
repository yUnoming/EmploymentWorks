#pragma once
/**
* @file		PositionXGizmo.h
* @brief	PositionXGizmoクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.12.24
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
			///	X軸移動ギズモ	</summary>
			class PositionXGizmo : public PositionGizmo
			{
				public:
					PositionXGizmo(SceneBase* nowScene) : PositionGizmo(nowScene) {};

					void Init()
					{
						// マテリアルカラー変更
						mat->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
						transform->rotation.z = -90.0f;
					};

					void ClickAction()
					{
						// ラジアン角に直す
						float rotY = spectatorCamera->transform->rotation.y * 3.14f / 180.0f;
						// マウスの座標を元に移動量を計算
						float addX = cosf(rotY) * (lateCursorPos.x - nowCursorPos.x) * -0.01f;
						float addY = sinf(rotY) * (lateCursorPos.y - nowCursorPos.y) * 0.01f;

						// X座標方向へ親オブジェクトを移動
						transform->parent->transform->position.x += addX + addY;
					}
			};
		}

	}
}


