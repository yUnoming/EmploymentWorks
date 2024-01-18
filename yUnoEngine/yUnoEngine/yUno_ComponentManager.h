#pragma once
/**
* @file		Component.h
* @brief	Componentクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Component.h"


namespace yUno_SystemManager
{
	/// <summary>
	///	コンポーネントの処理を管理するクラス	</summary>
	class yUno_ComponentManager
	{
		public:
			/// <summary>
			///	コンポーネントの変数の値を別のコンポーネントに代入	</summary>
			/// <param name="destComponent">
			///	コピー先のコンポーネント情報	</param>
			/// <param name="sourceComponent">
			/// コピー元のコンポーネント情報	</param>
			static void SetVariableValue(Component* destComponent, Component* sourceComponent);
			/// <summary>
			///	コンポーネントの種類を元にメッセージを送る	</summary>
			/// <param name="lateComponent">
			///	値更新前のコンポーネント情報	</param>
			/// <param name="nowComponent">
			/// 値更新後のコンポーネント情報	</param>
			static void SendMessageBasedOnType(Component* lateComponent, Component* nowComponent);
	};
}

