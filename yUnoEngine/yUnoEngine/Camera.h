#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Component.h"
#include "Vector3.h"
#include <SimpleMath.h>


namespace PublicSystem
{
	class Camera : public Component
	{
		private:
			// ----- variables / �ϐ� ----- //
			// �r���[�s��
			DirectX::SimpleMath::Matrix m_ViewMatrix{};

		public:
			// ----- functions / �֐� ----- //
			void Init()   override;	// ������
			void UnInit() override; // �I��
			void Update() override;	// �X�V
			void Draw()   override;	// �`��
	};
}

