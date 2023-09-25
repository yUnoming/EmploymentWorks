#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "Vector2.h"
#include "Vector3.h"


namespace PublicSystem
{
	class Camera : public EachFunction
	{
		private:
			void Draw() override;

		public:
			// ----- variables / �ϐ� ----- //
			float NearClip = 1.0f;		// �J�������`�悷��ł��߂��n�_
			float FarClip = 10.0f;		// �J�������`�悷��ł������n�_
			
			float FieldOfView = 45.0f;	// ����p

			// ----- functions / �֐� ----- //
			/// <summary>
			/// �����Ɏw�肵���X�N���[�����W�ɂ����ԋ߂��I�u�W�F�N�g���擾����֐�
			/// �����F�w�肵�����X�N���[�����W
			/// </summary>
			GameObject* GetScreenPointObject(Vector2 _screenPoint);
	};
}

