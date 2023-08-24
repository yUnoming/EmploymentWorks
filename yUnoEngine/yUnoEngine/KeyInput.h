#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "InputPartsName.h"


namespace PublicSystem
{
	// �L�[���̓N���X
	class KeyInput
	{
		public:
			// �L�[�������ꂽ�u�Ԃ��ǂ�����Ԃ��֐�
			static bool GetKeyDown_Trigger(KeyName _key);
			// �L�[��������Ă��邩�ǂ�����Ԃ��֐�
			static bool GetKeyDown(KeyName _key);
			// �L�[��������Ă��鎞�Ԃ�Ԃ��֐�
			static double GetKeyDown_Time(KeyName _key);

			// �L�[�������ꂽ�u�Ԃ��ǂ�����Ԃ��֐�
			static bool GetKeyUp_Trigger(KeyName _key);
			// �L�[��������Ă��邩�ǂ�����Ԃ��֐�
			static bool GetKeyUp(KeyName _key);
			// �L�[��������Ă��鎞�Ԃ�Ԃ��֐�
			static double GetKeyUp_Time(KeyName _key);
	};
}

