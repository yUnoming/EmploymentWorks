#pragma once
#include "C+lan.h"

class Player : public EachFunction
{
	private:
		float speed = 0.0065f;
		Vector3 latePos = Vector3();

		Vector3 dashVec = Vector3();
		float dashElapsedTime = 0;
		bool isDash;

	public:
		void Update()
		{
			// ���݂̍��W��ۑ�
			latePos = transform->position;

			// ----- WASD�ړ� ----- //
			if (KeyInput::GetKeyDown(W))
			{
				transform->position.y += speed * Ctlan::PublicSystem::Time::DeltaTime * 0.3f;
			}
			if (KeyInput::GetKeyDown(A))
			{
				transform->position.x -= speed * Ctlan::PublicSystem::Time::DeltaTime * 0.3f;
			}
			if (KeyInput::GetKeyDown(S))
			{
				transform->position.y -= speed * Ctlan::PublicSystem::Time::DeltaTime * 0.3f;
			}
			if (KeyInput::GetKeyDown(D))
			{
				transform->position.x += speed * Ctlan::PublicSystem::Time::DeltaTime * 0.3f;
			}

			// ----- Space�_�b�V�� ----- //
			// �_�b�V���J�n�H
			if (KeyInput::GetKeyDownTrigger(Space) && !isDash)
			{
				// �_�b�V������������擾
				dashVec = (transform->position - latePos) * 10.0f;
				isDash = true;	// �_�b�V����Ԃɐ؂�ւ�
			}

			// �_�b�V�����Ă���H
			if (isDash)
			{
				// �ړ�
				transform->position += dashVec * Ctlan::PublicSystem::Time::DeltaTime;
				// �x�N�g�����y��
				dashVec -= dashVec + dashElapsedTime;
				// �_�b�V���̌o�ߎ��Ԃ��v�Z
				dashElapsedTime = Ctlan::PublicSystem::Time::DeltaTime * 0.01f;

				// �x�N�g���̒l���}�C�i�X�ɂȂ����H
				if (dashVec.x < 0.0f)
					isDash = false;	// �_�b�V����Ԃ�؂�ւ�
			}

		};

		void HitCollision(GameObject* other)
		{
			// �Q�[���I�[�o�[�V�[�������[�h
			SceneManager::LoadScene("GameOverScene");
		};
};

