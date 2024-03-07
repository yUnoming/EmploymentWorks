#include "SystemCollisionManager.h"
#include "SystemSceneManager.h"
#include "EditScene.h"

std::vector<Ctlan::PublicSystem::BoxCollider*> Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::m_collisionVector;

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Uninit()
{
	// ���X�g���N���A
	m_collisionVector.clear();
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::CalculationCollision()
{
// �f�o�b�O��
#if _DEBUG
	// �f���v���C���H
	if (dynamic_cast<EngineScene::EditScene*>(SystemSceneManager::GetEditScene())->IsDemoPlay())
	{
		// �����蔻��R���|�[�l���g���ǉ�����Ă���I�u�W�F�N�g���Q�ȏ゠��H
		if (m_collisionVector.size() >= 2)
		{
			// ===== �����蔻��̌v�Z ===== //
			for (int i = 0; i < m_collisionVector.size(); i++)
			{
				// �����蔻�肪��A�N�e�B�u�Ȃ玟��
				if (!m_collisionVector[i]->isActive) continue;

				for (int j = i + 1; j < m_collisionVector.size(); j++)
				{
					// �����蔻���S�Čv�Z�����H
					if (j >= m_collisionVector.size()) return;	// ����I��
					// �����蔻�肪��A�N�e�B�u�Ȃ玟��
					if (!m_collisionVector[j]->isActive) continue;

					// �����蔻��̌v�Z��
					m_collisionVector[i]->CalcCollision(m_collisionVector[j]);
				}
			}
		}
	}
#else
	// �����蔻��R���|�[�l���g���ǉ�����Ă���I�u�W�F�N�g���Q�ȏ゠��H
	if (m_collisionVector.size() >= 2)
	{
		// ===== �����蔻��̌v�Z ===== //
		for (int i = 0; i < m_collisionVector.size(); i++)
		{
			// �����蔻�肪��A�N�e�B�u�Ȃ玟��
			if (!m_collisionVector[i]->isActive) continue;

			for (int j = i + 1; j < m_collisionVector.size(); j++)
			{
				// �����蔻���S�Čv�Z�����H
				if (j >= m_collisionVector.size()) return;	// ����I��
				// �����蔻�肪��A�N�e�B�u�Ȃ玟��
				if (!m_collisionVector[j]->isActive) continue;

				// �����蔻��̌v�Z��
				m_collisionVector[i]->CalcCollision(m_collisionVector[j]);
			}
		}
	}
#endif // _DEBUG
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Push(Ctlan::PublicSystem::BoxCollider* boxCol)
{
	// �����̃R���|�[�l���g���i�[
	m_collisionVector.push_back(boxCol);
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Erase(Ctlan::PublicSystem::BoxCollider* boxCol)
{
	if(!m_collisionVector.empty())
		// �����̃R���|�[�l���g�����O
		m_collisionVector.erase(std::find(m_collisionVector.begin(), m_collisionVector.end(), boxCol));
}
