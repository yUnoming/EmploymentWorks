#include "SystemCollisionManager.h"

std::vector<Ctlan::PublicSystem::BoxCollider*> Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::m_collisionVector;

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Uninit()
{
	// ���X�g���N���A
	m_collisionVector.clear();
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::CalculationCollision()
{
	// �����蔻��R���|�[�l���g���ǉ�����Ă���I�u�W�F�N�g���Q�ȏ゠��H
	if (m_collisionVector.size() >= 2)
	{
		// ===== �����蔻��̌v�Z ===== //
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
	// �����̃R���|�[�l���g���i�[
	m_collisionVector.push_back(boxCol);
}

void Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Erase(Ctlan::PublicSystem::BoxCollider* boxCol)
{
	// �����̃R���|�[�l���g�����O
	m_collisionVector.erase(std::find(m_collisionVector.begin(), m_collisionVector.end(), boxCol));
}
