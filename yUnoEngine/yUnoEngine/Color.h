#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <DirectXMath.h>


namespace PublicSystem
{
	// 色（rgba）を表すクラス
	class Color
	{
		public:
			// ----- variables / 変数 ----- //
			float r = 1.0f;		//   Red / 赤
			float g = 1.0f;		// Green / 緑
			float b = 1.0f;		//  Blue / 青
			float a = 1.0f;		// Alpha / 透明度


			// ----- functions / 関数 ----- //
			/// <summary>
			/// 通常コンストラクタ	</summary>
			Color() {};
			/// <summary>
			/// 各値に代入が行えるコンストラクタ	</summary>
			///<param name = "_r">
			/// ／赤色の強さ	</param>
			///<param name = "_g">
			/// ／緑色の強さ	</param>
			///<param name = "_b">
			/// ／青色の強さ	</param>
			///<param name = "_a">
			/// ／透明度の強さ	</param>
			Color(float _r, float _g, float _b, float _a);


			// ----- キャスト演算子 ----- //
			// **  XMFLOAT4  ** //
			operator DirectX::XMFLOAT4() const;


	};
}

