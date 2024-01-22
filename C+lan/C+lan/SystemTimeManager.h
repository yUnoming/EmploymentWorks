#pragma once
/**
* @file		SystemTimeManager.h
* @brief	SystemTimeManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.07
*/

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			///	時間を管理するクラス	</summary>
			class SystemTimeManager
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

	}
}

