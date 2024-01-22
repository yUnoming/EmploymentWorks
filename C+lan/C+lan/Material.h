#pragma once
/**
* @file		Material.h
* @brief	Materialクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.02
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "Color.h"


namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// オブジェクトの色・質感などを表すクラス	</summary>
		class Material : public EachFunction
		{
			public:
				// ----- variables / 変数 ----- //
				/// <summary>
				///マテリアルの色	</summary>
				Color materialColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

				// ----- functions / 関数 ----- //
				/// <summary>
				/// 描画	</summary>
				void Draw();

				/// <summary>
				/// マテリアルの色を変更する	</summary>
				/// <param name = "_colorParam">
				///	RGBAの値（Colorクラスオブジェクトで指定）	</param>
				void SetMaterialColor(Ctlan::PublicSystem::Color colorParam);
		};
	}
}