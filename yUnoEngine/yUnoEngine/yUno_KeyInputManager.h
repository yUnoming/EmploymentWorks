#pragma once
// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "KeyName.h"
#include <vector>

namespace yUno_SystemManager
{
	// �e��L�[���͏��
	enum KEY_STATUS
	{
		NoStatus,	// �܂�������Ă��Ȃ� or ���蒴��
		Up,			// �L�[��������Ă���
		Down,		// �L�[��������Ă���
	};

	// �e��L�[���
	struct KEY_INFO
	{
		// �L�[�̓��͏��
		KEY_STATUS KeyState = NoStatus;

		// ���݂̓��͏�ԂɂȂ��Ă���̌o�ߎ���
		double KeyState_ElapsedTime = 0.0;
	};

	class yUno_KeyInputManager
	{
		public:
			static void Update();		// �X�V����

			// ���݂̃L�[���͏�Ԃ�ۑ����邽�߂̊֐�
			static void Keep_Now_KeyInfo();

			// �L�[�̓��͏�Ԃ�������֐�
			static void Set_KeyDown(int _key);
			static void Set_KeyUp(int _key);

			// �L�[�������ꂽ�u�Ԃ��ǂ�����Ԃ��֐�
			static bool GetKeyDown_Trigger(PublicSystem::KeyName _key);
			// �L�[��������Ă��邩�ǂ�����Ԃ��֐�
			static bool GetKeyDown(PublicSystem::KeyName _key);
			// �L�[��������Ă��鎞�Ԃ�Ԃ��֐�
			static double GetKeyDown_Time(PublicSystem::KeyName _key);

			// �L�[�������ꂽ�u�Ԃ��ǂ�����Ԃ��֐�
			static bool GetKeyUp_Trigger(PublicSystem::KeyName _key);
			// �L�[��������Ă��邩�ǂ�����Ԃ��֐�
			static bool GetKeyUp(PublicSystem::KeyName _key);
			// �L�[��������Ă��鎞�Ԃ�Ԃ��֐�
			static double GetKeyUp_Time(PublicSystem::KeyName _key);

		private:
			// ���݂̃L�[����������z��
			static KEY_INFO Now_KeyInfo[400];
			// �O��̃L�[����������z��
			static KEY_INFO Late_KeyInfo[400];

			// ������Ă���L�[�̎��
			static std::vector<int> Down_KeyType[400];
			// ������Ă���L�[�̎�ނ̗v�f��
			static int Down_KeyType_Index;
			// ������Ă���L�[�̎��
			static std::vector<int> Up_KeyType[400];
			// ������Ă���L�[�̎�ނ̗v�f��
			static int Up_KeyType_Index;
	};
}

