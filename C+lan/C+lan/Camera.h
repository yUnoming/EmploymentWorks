#pragma once
/**
* @file		Camera.h
* @brief	Camera�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "Vector2.h"
#include "Vector3.h"


namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// �J�����Ɏ����������v�f���܂Ƃ߂��N���X</summary>
		class Camera : public EachFunction
		{
			private:
				// ----- functions / �֐� ----- //
				/// <summary>
				/// �`��	</summary>
				void Draw() override;

			public:
				// ----- variables / �ϐ� ----- //
				/// <summary>
				/// �J�������`�悷��ł��߂��n�_	</summary>
				float nearClip = 1.0f;
				/// <summary>
				///	�J�������`�悷��ł������n�_	</summary>
				float farClip = 10.0f;

				/// <summary>
				/// ����p	</summary>
				float fieldOfView = 45.0f;

				// ----- functions / �֐� ----- //
				/// <summary>
				/// �����Ɏw�肵���X�N���[�����W�ɂ����ԋ߂��I�u�W�F�N�g���擾	</summary>
				/// <param name="screenPoint">
				/// �X�N���[�����W	</param>
				PrivateSystem::GameObject* GetScreenPointObject(Vector2 screenPoint);
				/// <summary>
				/// �����Ɏw�肵���X�N���[�����W�ɂ����ԋ߂��}�j�s�����[�^�[���擾	</summary>
				/// <param name="screenPoint">
				/// �X�N���[�����W	</param>
				PrivateSystem::GameObject* GetScreenPointManipulator(Vector2 screenPoint);
		};
	}
}