#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"


namespace PublicSystem
{
	class Camera : public EachFunction
	{
		private:
			void Draw() override;

		public:
			// ----- variables / �ϐ� ----- //
			float NearClip = 1.0f;		// �J�������`�悷��ł��߂��n�_
			float FarClip = 10.0f;	// �J�������`�悷��ł������n�_
			
			float FieldOfView = 45.0f;	// ����p
	};
}

