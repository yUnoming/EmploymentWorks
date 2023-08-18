#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"


namespace PublicSystem
{
	class Camera : public EachFunction
	{
		private:
			void Draw() override;

		public:
			// ----- variables / 変数 ----- //
			float NearClip = 1.0f;		// カメラが描画する最も近い地点
			float FarClip = 10.0f;	// カメラが描画する最も遠い地点
			
			float FieldOfView = 45.0f;	// 視野角
	};
}

