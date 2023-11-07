#pragma once
/**
* @file		Color.h
* @brief	Colorクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.05
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <DirectXMath.h>


namespace PublicSystem
{
	/// <summary>
	///	色（rgba）を表すクラス	</summary>
	class Color
	{
		public:
			// ----- variables / 変数 ----- //
			/// <summary>
			///	Red / 赤	</summary>
			float r = 1.0f;
			/// <summary>
			///	Green / 緑	</summary>
			float g = 1.0f;
			/// <summary>
			///	Blue / 青	</summary>
			float b = 1.0f;
			/// <summary>
			///	Alpha / 透明度	</summary>
			float a = 1.0f;


			// ----- functions / 関数 ----- //
			/// <summary>
			/// 通常コンストラクタ	</summary>
			Color() {};
			/// <summary>
			/// 引数付きコンストラクタ	</summary>
			///<param name = "r">
			/// 赤色の強さ	</param>
			///<param name = "g">
			/// 緑色の強さ	</param>
			///<param name = "b">
			/// 青色の強さ	</param>
			///<param name = "a">
			/// 透明度の強さ	</param>
			Color(float r, float g, float b, float a);


			// ----- キャスト演算子 ----- //
			// **  XMFLOAT4  ** //
			operator DirectX::XMFLOAT4() const;


	};
}

