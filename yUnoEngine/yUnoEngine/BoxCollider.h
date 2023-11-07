#pragma once
/**
* @file		BoxCollider.h
* @brief	BoxColliderクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"

/// <summary>
///	ボックス状の当たり判定クラス	</summary>
class BoxCollider : public EachFunction
{
	public:
		// ----- functions / 関数 ----- //
		/// <summary>
		/// 当たり判定の計算	</summary>
		/// <param name="other">
		/// 衝突した相手の当たり判定	</param>
		void CalcCollision(BoxCollider* other);

};

