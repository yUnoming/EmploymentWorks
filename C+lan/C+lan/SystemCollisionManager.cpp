#include "SystemCollisionManager.h"
#include "SystemSceneManager.h"
#include "EditScene.h"

std::vector<Ctlan::PublicSystem::BoxCollider*> Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::m_collisionVector;

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Uninit()
{
	// リストをクリア
	m_collisionVector.clear();
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::CalculationCollision()
{
// デバッグ時
#if _DEBUG
	// デモプレイ中？
	if (dynamic_cast<EngineScene::EditScene*>(SystemSceneManager::GetEditScene())->IsDemoPlay())
	{
		// 当たり判定コンポーネントが追加されているオブジェクトが２つ以上ある？
		if (m_collisionVector.size() >= 2)
		{
			// ===== 当たり判定の計算 ===== //
			for (int i = 0; i < m_collisionVector.size(); i++)
			{
				// 当たり判定が非アクティブなら次へ
				if (!m_collisionVector[i]->isActive) continue;

				for (int j = i + 1; j < m_collisionVector.size(); j++)
				{
					// 当たり判定を全て計算した？
					if (j >= m_collisionVector.size()) return;	// 判定終了
					// 当たり判定が非アクティブなら次へ
					if (!m_collisionVector[j]->isActive) continue;

					// 当たり判定の計算へ
					m_collisionVector[i]->CalcCollision(m_collisionVector[j]);
				}
			}
		}
	}
#else
	// 当たり判定コンポーネントが追加されているオブジェクトが２つ以上ある？
	if (m_collisionVector.size() >= 2)
	{
		// ===== 当たり判定の計算 ===== //
		for (int i = 0; i < m_collisionVector.size(); i++)
		{
			// 当たり判定が非アクティブなら次へ
			if (!m_collisionVector[i]->isActive) continue;

			for (int j = i + 1; j < m_collisionVector.size(); j++)
			{
				// 当たり判定を全て計算した？
				if (j >= m_collisionVector.size()) return;	// 判定終了
				// 当たり判定が非アクティブなら次へ
				if (!m_collisionVector[j]->isActive) continue;

				// 当たり判定の計算へ
				m_collisionVector[i]->CalcCollision(m_collisionVector[j]);
			}
		}
	}
#endif // _DEBUG
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Push(Ctlan::PublicSystem::BoxCollider* boxCol)
{
	// 引数のコンポーネントを格納
	m_collisionVector.push_back(boxCol);
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Erase(Ctlan::PublicSystem::BoxCollider* boxCol)
{
	if(!m_collisionVector.empty())
		// 引数のコンポーネントを除外
		m_collisionVector.erase(std::find(m_collisionVector.begin(), m_collisionVector.end(), boxCol));
}
