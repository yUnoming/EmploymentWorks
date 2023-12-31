#pragma once
/**
* @file		Text.h
* @brief	Textクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.07
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "TextRenderer.h"


namespace PublicSystem
{
	/// <summary>
	/// テキストに関する操作をまとめたクラス	</summary>
	class Text : public TextRenderer
	{
		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			///	現在のテキストに新たにテキストを追加	</summary>
			/// <param name="addText">
			/// 追加するテキスト	</param>
			void AddText(const char* addText);
	};
}

