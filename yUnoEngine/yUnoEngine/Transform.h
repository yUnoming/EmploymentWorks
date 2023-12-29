#pragma once
/**
* @file		Transform.h
* @brief	Transformクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.02
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "Vector3.h"


namespace PublicSystem
{
	/// <summary>
	///	位置・回転・大きさを表すクラス	</summary>
	class Transform : public EachFunction
	{
	public:

		// ----- variables / 変数 ----- //
		/// <summary>
		/// 位置	</summary>
		Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
		/// <summary>
		/// 回転	</summary>
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
		/// <summary>
		///	大きさ	</summary>
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
	};
}

