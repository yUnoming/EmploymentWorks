#pragma once
/**
* @file		SystemKeyInputManager.h
* @brief	SystemKeyInputManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "InputPartsName.h"
#include <vector>

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			///	�L�[���͂𔻒肷�邽�߂̏������Ǘ�����N���X	</summary>
			class SystemKeyInputManager
			{
				private:
					/// <summary>
					///	�L�[���͏��	</summary>
					enum KeyStatus
					{
						/// <summary>
						/// �܂�������Ă��Ȃ� or ���蒴��</summary>
						NoStatus,
						/// <summary>
						///	�L�[��������Ă���	</summary>
						Up,
						/// <summary>
						///	�L�[��������Ă���	</summary>
						Down,
					};

					/// <summary>
					/// �L�[���	</summary>
					struct KeyInfo
					{
						/// <summary>
						///	�L�[�̓��͏��	</summary>
						KeyStatus keyState = NoStatus;
						/// <summary>
						///	���݂̓��͏�ԂɂȂ��Ă���̌o�ߎ���	</summary>
						double nowStateElapsedTime = 0.0;
					};

					/// <summary>
					/// ���͔��蒆�̃L�[���	</summary>
					struct CheckKeyInfo
					{
						/// <summary>
						///	���蒆�̃L�[�̎��	</summary>
						std::vector<int> keyType[400];
						/// <summary>
						///	���蒆�̃L�[�̎��	</summary>
						int keyIndex;
					};

					// ----- variables / �ϐ� ----- //
					/// <summary>
					/// ���݂̊e��L�[���	</summary>
					static KeyInfo m_nowKeyInfo[400];
					/// <summary>
					/// �O��̊e��L�[���	</summary>
					static KeyInfo m_lateKeyInfo[400];

					/// <summary>
					///	���݉�����Ă���Ɣ��蒆�̃L�[���	</summary>
					static CheckKeyInfo m_downStateKeyInfo;
					/// <summary>
					/// ���ݗ�����Ă���Ɣ��蒆�̃L�[���	</summary>
					static CheckKeyInfo m_upStateKeyInfo;

				public:
					// ----- functions / �֐� ----- //
					/// <summary>
					///	�X�V	</summary>
					static void Update();
					/// <summary>
					/// ���݂̃L�[���͏�Ԃ�ۑ�	</summary>
					static void KeepNowKeyInfo();

					/// <summary>
					/// �w�肵���L�[�������ꂽ��ԂɑJ��	</summary>
					/// <param name="key">
					/// �L�[��	</param>
					static void SetKeyDown(int key);
					/// <summary>
					///	�w�肵���L�[�𗣂��ꂽ��ԂɑJ��	</summary>
					/// <param name="key">
					/// �L�[��	</param>
					static void SetKeyUp(int key);

					/// <summary>
					/// �L�[�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
					/// <param name="key">
					///	���肵�����L�[��	</param>
					/// <returns>
					///	�����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
					static bool GetKeyDownTrigger(Ctlan::PublicSystem::KeyName key);
					/// <summary>
					/// �L�[��������Ă��邩�ǂ����𔻒�	</summary>
					/// <param name="key">
					///	���肵�����L�[��	</param>
					/// <returns>
					///	������Ă�����true�A����ȊO�Ȃ�false	</returns>
					static bool GetKeyDown(Ctlan::PublicSystem::KeyName key);
					/// <summary>
					/// �L�[��������Ă��鎞�Ԃ��擾	</summary>
					/// <param name="key">
					///	�擾�������L�[��	</param>
					/// <returns>
					///	������Ă��鎞�ԁA������Ă��Ȃ��ꍇ��0	</returns>
					static double GetKeyDownTime(Ctlan::PublicSystem::KeyName key);

					/// <summary>
					/// �L�[�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
					/// <param name="key">
					///	���肵�����L�[��	</param>
					/// <returns>
					/// �����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
					static bool GetKeyUpTrigger(Ctlan::PublicSystem::KeyName key);
					/// <summary>
					/// �L�[��������Ă��邩�ǂ����𔻒�	</summary>
					/// <param name="key">
					/// ���肵�����L�[��	</param>
					/// <returns>
					///	������Ă�����true�A����ȊO�Ȃ�false	</returns>
					static bool GetKeyUp(Ctlan::PublicSystem::KeyName key);
					/// <summary>
					/// �L�[��������Ă��鎞�Ԃ��擾�@����莞�Ԓ��߂Ōv���I�����邱�Ƃɒ���	</summary>
					/// <param name="key">
					/// �擾�������L�[��	</param>
					/// <returns>
					/// ������Ă��鎞�ԁA������Ă��Ȃ�or���Ԓ��߂̏ꍇ��0</returns>
					static double GetKeyUpTime(Ctlan::PublicSystem::KeyName key);
			};
		}
	}
}

