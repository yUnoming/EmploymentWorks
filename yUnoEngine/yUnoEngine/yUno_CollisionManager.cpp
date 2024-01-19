#include "yUno_CollisionManager.h"

std::vector<BoxCollider*> yUno_SystemManager::yUno_CollisionManager::m_collisionVector;

void yUno_SystemManager::yUno_CollisionManager::Uninit()
{
	// ���X�g���N���A
	m_collisionVector.clear();
}

void yUno_SystemManager::yUno_CollisionManager::CalculationCollision()
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

void yUno_SystemManager::yUno_CollisionManager::Push(BoxCollider* boxCol)
{
	// �����̃R���|�[�l���g���i�[
	m_collisionVector.push_back(boxCol);
}

void yUno_SystemManager::yUno_CollisionManager::Erase(BoxCollider* boxCol)
{
	// �����̃R���|�[�l���g�����O
	m_collisionVector.erase(std::find(m_collisionVector.begin(), m_collisionVector.end(), boxCol));
}
