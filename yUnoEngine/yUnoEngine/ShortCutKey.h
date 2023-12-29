#pragma once
/**
* @file		ShortCutKey.h
* @brief	ShortCutKeyクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"


/// <summary>
///	アプリケーションを支えるシステムの一部	</summary>
namespace yUno_SystemParts
{
	/// <summary>
	///	ショートカットキーの操作を扱うクラス	</summary>
	class ShortCutKey
	{
		public:
			/// <summary>
			///	実行	</summary>
			static void Run(int keyCommand);
	};
}


