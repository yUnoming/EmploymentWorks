#include "SystemCollisionManager.h"

std::vector<Ctlan::PublicSystem::BoxCollider*> Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::m_collisionVector;

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Uninit()
{
	// リストをクリア
	m_collisionVector.clear();
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::CalculationCollision()
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

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Push(Ctlan::PublicSystem::BoxCollider* boxCol)
{
	// 引数のコンポーネントを格納
	m_collisionVector.push_back(boxCol);
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Erase(Ctlan::PublicSystem::BoxCollider* boxCol)
{
	// 引数のコンポーネントを除外
	m_collisionVector.erase(std::find(m_collisionVector.begin(), m_collisionVector.end(), boxCol));
}
