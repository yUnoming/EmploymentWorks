#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "Vector2.h"
#include "Vector3.h"


namespace PublicSystem
{
	class Camera : public EachFunction
	{
		private:
			void Draw() override;

		public:
			// ----- variables / 変数 ----- //
			float NearClip = 1.0f;		// カメラが描画する最も近い地点
			float FarClip = 10.0f;		// カメラが描画する最も遠い地点
			
			float FieldOfView = 45.0f;	// 視野角

			// ----- functions / 関数 ----- //
			/// <summary>
			/// 引数に指定したスクリーン座標にある一番近いオブジェクトを取得する関数
			/// 引数：指定したいスクリーン座標
			/// </summary>
			GameObject* GetScreenPointObject(Vector2 _screenPoint);
	};
}

