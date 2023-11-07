#pragma once
/**
* @file		yUno_TimeManager.h
* @brief	yUno_TimeManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.07
*/
namespace yUno_SystemManager
{
	/// <summary>
	///	時間を管理するクラス	</summary>
	class yUno_TimeManager
	{
		private:
			// ----- variables / 変数 ----- //
			/// <summary>
			///	前回の時間	</summary>
			static double m_lastTime;

		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			///	初期化	</summary>
			static void Init();
			/// <summary>
			///	更新	</summary>
			static void Update();
	};
}

