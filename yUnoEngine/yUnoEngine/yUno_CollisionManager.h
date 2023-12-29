#pragma once
/**
* @file		yUno_CollisionManager.h
* @brief	yUno_CollisionManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <vector>
#include "BoxCollider.h"


namespace yUno_SystemManager
{
	class yUno_CollisionManager
	{
		private:
			// ----- variables / 変数 ----- //
			/// <summary>
			/// // 当たり判定コンポーネントの格納用配列	</summary>
			static std::vector<BoxCollider*> m_collisionVector;

		public:
			// ----- functions / 関数 ----- //	
			/// <summary>
			///	終了	</summary>
			static void UnInit();
			/// <summary>
			///	当たり判定の計算	</summary>
			static void CalculationCollision();

			/// <summary>
			///	当たり判定コンポーネントを格納	</summary>
			/// <param name="boxCol">
			///	格納する当たり判定コンポーネント	</param>
			static void Push(BoxCollider* boxCol);
			/// <summary>
			///	当たり判定コンポーネントを除外	</summary>
			/// <param name="boxCol">
			///	除外する当たり判定コンポーネント	</param>
			static void Erase(BoxCollider* boxCol);
	};
}

