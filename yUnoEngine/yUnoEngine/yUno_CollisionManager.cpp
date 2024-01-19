#include "yUno_CollisionManager.h"

std::vector<BoxCollider*> yUno_SystemManager::yUno_CollisionManager::m_collisionVector;

void yUno_SystemManager::yUno_CollisionManager::Uninit()
{
	// リストをクリア
	m_collisionVector.clear();
}

void yUno_SystemManager::yUno_CollisionManager::CalculationCollision()
{
	// 当たり判定コンポーネントが追加されているオブジェクトが２つ以上ある？
	if (m_collisionVector.size() >= 2)
	{
		// ===== 当たり判定の計算 ===== //
		for (int i = 0; i < m_collisionVector.size(); i++)
		{
			for (int j = i + 1; j < m_collisionVector.size(); j++)
			{
				m_collisionVector[i]->CalcCollision(m_collisionVector[j]);
			}
		}
	}
}

void yUno_SystemManager::yUno_CollisionManager::Push(BoxCollider* boxCol)
{
	// 引数のコンポーネントを格納
	m_collisionVector.push_back(boxCol);
}

void yUno_SystemManager::yUno_CollisionManager::Erase(BoxCollider* boxCol)
{
	// 引数のコンポーネントを除外
	m_collisionVector.erase(std::find(m_collisionVector.begin(), m_collisionVector.end(), boxCol));
}
