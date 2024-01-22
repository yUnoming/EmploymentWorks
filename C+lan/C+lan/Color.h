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

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	色（rgba）を表すクラス	</summary>
		class Color
		{
			public:
				// ----- enum / 列挙型 ----- //
				/// <summary>
				///	色の種類	</summary>
				enum ColorType
				{
					Red,
					Green,
					Blue,
					Yellow,
					Cyan,
					Magenta,
					Orange,
					Pink,
					White,
					Black,
				};

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

				/// <summary>
				///	カラーの種類から値を取得	</summary>
				/// <param name="colorType">
				/// カラーの種類	</param>
				/// <returns>
				/// カラー値(R,G,B,A)</returns>
				static const Ctlan::PublicSystem::Color GetColor(ColorType colorType);

				// ----- キャスト演算子 ----- //
				// **  XMFLOAT4  ** //
				operator DirectX::XMFLOAT4() const;
		};
	}
}