#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "Color.h"

namespace PublicSystem
{
	// オブジェクトの色・質感などを表すクラス
	class Material : public EachFunction
	{
		public:
			// ----- variables / 変数 ----- //
			Color Material_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);	// マテリアルの色

			// ----- functions / 関数 ----- //
			/// <summary>
			/// マテリアルの色を変更する	</summary>
			/// <param name = "_colorParam">
			///	RGBAを数値で指定	</param>
			void SetMateiralColor(PublicSystem::Color _colorParam);
	};
}

