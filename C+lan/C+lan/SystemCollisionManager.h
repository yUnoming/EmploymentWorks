#pragma once
/**
* @file		SystemCollisionManager.h
* @brief	SystemCollisionManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
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
					// ----- variables / �ϐ� ----- //
					/// <summary>
					/// // �����蔻��R���|�[�l���g�̊i�[�p�z��	</summary>
					static std::vector<Ctlan::PublicSystem::BoxCollider*> m_collisionVector;

				public:
					// ----- functions / �֐� ----- //	
					/// <summary>
					///	�I��	</summary>
					static void Uninit();
					/// <summary>
					///	�����蔻��̌v�Z	</summary>
					static void CalculationCollision();

					/// <summary>
					///	�����蔻��R���|�[�l���g���i�[	</summary>
					/// <param name="boxCol">
					///	�i�[���铖���蔻��R���|�[�l���g	</param>
					static void Push(Ctlan::PublicSystem::BoxCollider* boxCol);
					/// <summary>
					///	�����蔻��R���|�[�l���g�����O	</summary>
					/// <param name="boxCol">
					///	���O���铖���蔻��R���|�[�l���g	</param>
					static void Erase(Ctlan::PublicSystem::BoxCollider* boxCol);
			};
		}
	}
}