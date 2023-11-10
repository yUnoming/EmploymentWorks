#pragma once
/**
* @file		Component.h
* @brief	Componentクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.10.29
*/

namespace yUno_SystemManager
{
	/// <summary>
	///	ネットワークの処理を管理するクラス	</summary>
	class yUno_NetWorkManager
	{
		// ----- functions / 関数 ----- //

		/// <summary>
		///	ネットワーク通信を開始	</summary>
		int Start();
		/// <summary>
		///	ネットワーク通信を終了	</summary>
		int End();
	};
}

