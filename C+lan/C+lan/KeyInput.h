#pragma once
/**
* @file		KeyInput.h
* @brief	KeyInput�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.05
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "InputPartsName.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	�L�[���͂𔻒肷�邽�߂̋@�\���܂Ƃ߂��N���X	</summary>
		class KeyInput
		{
			public:
				// ----- functions / �֐� ----- //
				/// <summary>
				/// �L�[�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
				/// <param name="key">
				///	���肵�����L�[��	</param>
				/// <returns>
				///	�����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
				static bool GetKeyDownTrigger(KeyName key);
				/// <summary>
				/// �L�[��������Ă��邩�ǂ����𔻒�	</summary>
				/// <param name="key">
				///	���肵�����L�[��	</param>
				/// <returns>
				///	������Ă�����true�A����ȊO�Ȃ�false	</returns>
				static bool GetKeyDown(KeyName key);
				/// <summary>
				/// �L�[��������Ă��鎞�Ԃ��擾	</summary>
				/// <param name="key">
				///	�擾�������L�[��	</param>
				/// <returns>
				///	������Ă��鎞�ԁA������Ă��Ȃ��ꍇ��0	</returns>
				static double GetKeyDownTime(KeyName key);

				/// <summary>
				/// �L�[�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
				/// <param name="key">
				///	���肵�����L�[��	</param>
				/// <returns>
				/// �����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
				static bool GetKeyUpTrigger(KeyName key);
				/// <summary>
				/// �L�[��������Ă��邩�ǂ����𔻒�	</summary>
				/// <param name="key">
				/// ���肵�����L�[��	</param>
				/// <returns>
				///	������Ă�����true�A����ȊO�Ȃ�false	</returns>
				static bool GetKeyUp(KeyName key);
				/// <summary>
				/// �L�[��������Ă��鎞�Ԃ��擾�@����莞�Ԓ��߂Ōv���I�����邱�Ƃɒ���	</summary>
				/// <param name="key">
				/// �擾�������L�[��	</param>
				/// <returns>
				/// ������Ă��鎞�ԁA������Ă��Ȃ�or���Ԓ��߂̏ꍇ��0</returns>
				static double GetKeyUpTime(KeyName key);
		};
	}
}