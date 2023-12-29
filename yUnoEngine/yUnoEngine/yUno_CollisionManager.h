#pragma once
/**
* @file		yUno_CollisionManager.h
* @brief	yUno_CollisionManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <vector>
#include "BoxCollider.h"


namespace yUno_SystemManager
{
	class yUno_CollisionManager
	{
		private:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			/// // �����蔻��R���|�[�l���g�̊i�[�p�z��	</summary>
			static std::vector<BoxCollider*> m_collisionVector;

		public:
			// ----- functions / �֐� ----- //	
			/// <summary>
			///	�I��	</summary>
			static void UnInit();
			/// <summary>
			///	�����蔻��̌v�Z	</summary>
			static void CalculationCollision();

			/// <summary>
			///	�����蔻��R���|�[�l���g���i�[	</summary>
			/// <param name="boxCol">
			///	�i�[���铖���蔻��R���|�[�l���g	</param>
			static void Push(BoxCollider* boxCol);
			/// <summary>
			///	�����蔻��R���|�[�l���g�����O	</summary>
			/// <param name="boxCol">
			///	���O���铖���蔻��R���|�[�l���g	</param>
			static void Erase(BoxCollider* boxCol);
	};
}

