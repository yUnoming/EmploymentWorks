#pragma once
/**
* @file		yUno_KeyInputManager.h
* @brief	yUno_KeyInputManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"
#include <vector>

namespace yUno_SystemManager
{
	/// <summary>
	///	キー入力を判定するための処理を管理するクラス	</summary>
	class yUno_KeyInputManager
	{
		private:
			/// <summary>
			///	キー入力状態	</summary>
			enum KeyStatus
			{
				/// <summary>
				/// まだ押されていない or 判定超過</summary>
				NoStatus,
				/// <summary>
				///	キーが離されている	</summary>
				Up,
				/// <summary>
				///	キーが押されている	</summary>
				Down,
			};

			/// <summary>
			/// キー情報	</summary>
			struct KeyInfo
			{
				/// <summary>
				///	キーの入力状態	</summary>
				KeyStatus keyState = NoStatus;
				/// <summary>
				///	現在の入力状態になってからの経過時間	</summary>
				double nowStateElapsedTime = 0.0;
			};

			/// <summary>
			/// 入力判定中のキー情報	</summary>
			struct CheckKeyInfo
			{
				/// <summary>
				///	判定中のキーの種類	</summary>
				std::vector<int> keyType[400];
				/// <summary>
				///	判定中のキーの種類	</summary>
				int keyIndex;
			};

			// ----- variables / 変数 ----- //
			/// <summary>
			/// 現在の各種キー情報	</summary>
			static KeyInfo m_nowKeyInfo[400];
			 /// <summary>
			 /// 前回の各種キー情報	</summary>
			static KeyInfo m_lateKeyInfo[400];

			/// <summary>
			///	現在押されていると判定中のキー情報	</summary>
			static CheckKeyInfo m_downStateKeyInfo;
			/// <summary>
			/// 現在離されていると判定中のキー情報	</summary>
			static CheckKeyInfo m_upStateKeyInfo;

		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			///	更新	</summary>
			static void Update();
			/// <summary>
			/// 現在のキー入力状態を保存	</summary>
			static void KeepNowKeyInfo();

			/// <summary>
			/// 指定したキーを押された状態に遷移	</summary>
			/// <param name="key">
			/// キー名	</param>
			static void SetKeyDown(int key);
			/// <summary>
			///	指定したキーを離された状態に遷移	</summary>
			/// <param name="key">
			/// キー名	</param>
			static void SetKeyUp(int key);

			/// <summary>
			/// キーが押された瞬間かどうかを判定	</summary>
			/// <param name="key">
			///	判定したいキー名	</param>
			/// <returns>
			///	押された瞬間ならtrue、それ以外ならfalse	</returns>
			static bool GetKeyDownTrigger(PublicSystem::KeyName key);
			/// <summary>
			/// キーが押されているかどうかを判定	</summary>
			/// <param name="key">
			///	判定したいキー名	</param>
			/// <returns>
			///	押されていたらtrue、それ以外ならfalse	</returns>
			static bool GetKeyDown(PublicSystem::KeyName key);
			/// <summary>
			/// キーが押されている時間を取得	</summary>
			/// <param name="key">
			///	取得したいキー名	</param>
			/// <returns>
			///	押されている時間、押されていない場合は0	</returns>
			static double GetKeyDownTime(PublicSystem::KeyName key);

			/// <summary>
			/// キーが離された瞬間かどうかを判定	</summary>
			/// <param name="key">
			///	判定したいキー名	</param>
			/// <returns>
			/// 離された瞬間ならtrue、それ以外ならfalse	</returns>
			static bool GetKeyUpTrigger(PublicSystem::KeyName key);
			/// <summary>
			/// キーが離されているかどうかを判定	</summary>
			/// <param name="key">
			/// 判定したいキー名	</param>
			/// <returns>
			///	離されていたらtrue、それ以外ならfalse	</returns>
			static bool GetKeyUp(PublicSystem::KeyName key);
			/// <summary>
			/// キーが離されている時間を取得　※一定時間超過で計測終了することに注意	</summary>
			/// <param name="key">
			/// 取得したいキー名	</param>
			/// <returns>
			/// 離されている時間、離されていないor時間超過の場合は0</returns>
			static double GetKeyUpTime(PublicSystem::KeyName key);
	};
}

