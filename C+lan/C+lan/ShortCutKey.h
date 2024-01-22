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


namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		///	アプリケーションを支えるシステム	</summary>
		namespace ApplicationSystem
		{
			/// <summary>
			///	ショートカットキーの操作を扱うクラス	</summary>
			class ShortCutKey
			{
				public:
					/// <summary>
					///	実行	</summary>
					/// <param name="keyCommand">
					///	キーの値	</param>
					static void Run(int keyCommand);
			};
		}
	}
}