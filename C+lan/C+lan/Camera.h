#pragma once
/**
* @file		Camera.h
* @brief	Cameraクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "Vector2.h"
#include "Vector3.h"


namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// カメラに持たせたい要素をまとめたクラス</summary>
		class Camera : public EachFunction
		{
			private:
				// ----- variables / 変数 ----- //
				DirectX::XMFLOAT3 m_eye;
				DirectX::XMFLOAT3 m_focus;
				DirectX::XMFLOAT3 m_up;

				Vector3 lateRotation;

				// ----- functions / 関数 ----- //
				/// <summary>
				///	初期化	</summary>
				void Init() override;
				/// <summary>
				/// 描画	</summary>
				void Draw() override;

			public:
				// ----- variables / 変数 ----- //
				/// <summary>
				/// カメラが描画する最も近い地点	</summary>
				float nearClip = 1.0f;
				/// <summary>
				///	カメラが描画する最も遠い地点	</summary>
				float farClip = 10.0f;

				/// <summary>
				/// 視野角	</summary>
				float fieldOfView = 45.0f;

				// ----- functions / 関数 ----- //
				/// <summary>
				/// 引数に指定したスクリーン座標にある一番近いオブジェクトを取得	</summary>
				/// <param name="screenPoint">
				/// スクリーン座標	</param>
				PrivateSystem::GameObject* GetScreenPointObject(Vector2 screenPoint);
				/// <summary>
				/// 引数に指定したスクリーン座標にある一番近いマニピュレーターを取得	</summary>
				/// <param name="screenPoint">
				/// スクリーン座標	</param>
				PrivateSystem::GameObject* GetScreenPointManipulator(Vector2 screenPoint);
		};
	}
}