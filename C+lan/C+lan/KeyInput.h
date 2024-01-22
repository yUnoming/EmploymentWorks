#pragma once
/**
* @file		KeyInput.h
* @brief	KeyInputクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.05
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	キー入力を判定するための機能をまとめたクラス	</summary>
		class KeyInput
		{
			public:
				// ----- functions / 関数 ----- //
				/// <summary>
				/// キーが押された瞬間かどうかを判定	</summary>
				/// <param name="key">
				///	判定したいキー名	</param>
				/// <returns>
				///	押された瞬間ならtrue、それ以外ならfalse	</returns>
				static bool GetKeyDownTrigger(KeyName key);
				/// <summary>
				/// キーが押されているかどうかを判定	</summary>
				/// <param name="key">
				///	判定したいキー名	</param>
				/// <returns>
				///	押されていたらtrue、それ以外ならfalse	</returns>
				static bool GetKeyDown(KeyName key);
				/// <summary>
				/// キーが押されている時間を取得	</summary>
				/// <param name="key">
				///	取得したいキー名	</param>
				/// <returns>
				///	押されている時間、押されていない場合は0	</returns>
				static double GetKeyDownTime(KeyName key);

				/// <summary>
				/// キーが離された瞬間かどうかを判定	</summary>
				/// <param name="key">
				///	判定したいキー名	</param>
				/// <returns>
				/// 離された瞬間ならtrue、それ以外ならfalse	</returns>
				static bool GetKeyUpTrigger(KeyName key);
				/// <summary>
				/// キーが離されているかどうかを判定	</summary>
				/// <param name="key">
				/// 判定したいキー名	</param>
				/// <returns>
				///	離されていたらtrue、それ以外ならfalse	</returns>
				static bool GetKeyUp(KeyName key);
				/// <summary>
				/// キーが離されている時間を取得　※一定時間超過で計測終了することに注意	</summary>
				/// <param name="key">
				/// 取得したいキー名	</param>
				/// <returns>
				/// 離されている時間、離されていないor時間超過の場合は0</returns>
				static double GetKeyUpTime(KeyName key);
		};
	}
}