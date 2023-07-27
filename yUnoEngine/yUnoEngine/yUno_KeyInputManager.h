#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "KeyName.h"
#include <vector>

namespace yUno_SystemManager
{
	// 各種キー入力状態
	enum KEY_STATUS
	{
		NoStatus,	// まだ押されていない or 判定超過
		Up,			// キーが離されている
		Down,		// キーが押されている
	};

	// 各種キー情報
	struct KEY_INFO
	{
		// キーの入力状態
		KEY_STATUS KeyState = NoStatus;

		// 現在の入力状態になってからの経過時間
		double KeyState_ElapsedTime = 0.0;
	};

	class yUno_KeyInputManager
	{
		public:
			static void Update();		// 更新処理

			// 現在のキー入力状態を保存するための関数
			static void Keep_Now_KeyInfo();

			// キーの入力状態を代入する関数
			static void Set_KeyDown(int _key);
			static void Set_KeyUp(int _key);

			// キーが押された瞬間かどうかを返す関数
			static bool GetKeyDown_Trigger(PublicSystem::KeyName _key);
			// キーが押されているかどうかを返す関数
			static bool GetKeyDown(PublicSystem::KeyName _key);
			// キーが押されている時間を返す関数
			static double GetKeyDown_Time(PublicSystem::KeyName _key);

			// キーが離された瞬間かどうかを返す関数
			static bool GetKeyUp_Trigger(PublicSystem::KeyName _key);
			// キーが離されているかどうかを返す関数
			static bool GetKeyUp(PublicSystem::KeyName _key);
			// キーが離されている時間を返す関数
			static double GetKeyUp_Time(PublicSystem::KeyName _key);

		private:
			// 現在のキー情報を代入する配列
			static KEY_INFO Now_KeyInfo[400];
			// 前回のキー情報を代入する配列
			static KEY_INFO Late_KeyInfo[400];

			// 押されているキーの種類
			static std::vector<int> Down_KeyType[400];
			// 押されているキーの種類の要素数
			static int Down_KeyType_Index;
			// 離されているキーの種類
			static std::vector<int> Up_KeyType[400];
			// 離されているキーの種類の要素数
			static int Up_KeyType_Index;
	};
}

