#pragma once
/**
* @file		SystemCollisionManager.h
* @brief	SystemCollisionManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <vector>
#include "BoxCollider.h"

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			class SystemCollisionManager
			{
				private:
					// ----- variables / 変数 ----- //
					/// <summary>
					/// // 当たり判定コンポーネントの格納用配列	</summary>
					static std::vector<Ctlan::PublicSystem::BoxCollider*> m_collisionVector;

				public:
					// ----- functions / 関数 ----- //	
					/// <summary>
					///	終了	</summary>
					static void Uninit();
					/// <summary>
					///	当たり判定の計算	</summary>
					static void CalculationCollision();

					/// <summary>
					///	当たり判定コンポーネントを格納	</summary>
					/// <param name="boxCol">
					///	格納する当たり判定コンポーネント	</param>
					static void Push(Ctlan::PublicSystem::BoxCollider* boxCol);
					/// <summary>
					///	当たり判定コンポーネントを除外	</summary>
					/// <param name="boxCol">
					///	除外する当たり判定コンポーネント	</param>
					static void Erase(Ctlan::PublicSystem::BoxCollider* boxCol);
			};
		}
	}
}