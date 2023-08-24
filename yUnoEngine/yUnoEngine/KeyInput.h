#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"


namespace PublicSystem
{
	// キー入力クラス
	class KeyInput
	{
		public:
			// キーが押された瞬間かどうかを返す関数
			static bool GetKeyDown_Trigger(KeyName _key);
			// キーが押されているかどうかを返す関数
			static bool GetKeyDown(KeyName _key);
			// キーが押されている時間を返す関数
			static double GetKeyDown_Time(KeyName _key);

			// キーが離された瞬間かどうかを返す関数
			static bool GetKeyUp_Trigger(KeyName _key);
			// キーが離されているかどうかを返す関数
			static bool GetKeyUp(KeyName _key);
			// キーが離されている時間を返す関数
			static double GetKeyUp_Time(KeyName _key);
	};
}

