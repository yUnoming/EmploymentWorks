// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "SystemKeyInputManager.h"
#include "SystemTextRendererManager.h"
#include "KeyInput.h"
#include "ShortCutKey.h"
#include "Time.h"

#include <Windows.h>


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::KeyInfo Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::m_nowKeyInfo[400];
Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::KeyInfo Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::m_lateKeyInfo[400];
Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::CheckKeyInfo Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::m_upStateKeyInfo;
Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::CheckKeyInfo Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::m_downStateKeyInfo;


void Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::Update()
{
	// ===== �e�L�[��Ԃ̌o�ߎ��Ԃ𑪒� ===== //
	//**  ������Ă���L�[  **//
	// �L�[��������Ă���H�i������Ă��Ȃ��ꍇ�͏������s��Ȃ��j
	if (!m_downStateKeyInfo.keyType->empty())
	{
		// ������Ă���L�[�̐��������[�v
		for (int i = 0; i < m_downStateKeyInfo.keyIndex; i++)
		{
			// �L�[�̉�����Ă��鎞�Ԃ��v�Z
			m_nowKeyInfo[m_downStateKeyInfo.keyType->at(i)].nowStateElapsedTime += Ctlan::PublicSystem::Time::DeltaTime * 0.0001f;
		}
	}
	//**  ������Ă���L�[  **//
	// �L�[��������Ă���i������s���Ă���L�[�����݂���j�H�i������Ă��Ȃ��i������s���Ă���L�[�����݂��Ȃ��j�ꍇ�͏������s��Ȃ��j
	if (!m_upStateKeyInfo.keyType->empty())
	{
		// ������Ă���L�[�̐��������[�v
		for (int i = 0; i < m_upStateKeyInfo.keyIndex; i++)
		{
			// �L�[�̗�����Ă��鎞�Ԃ��v�Z
			m_nowKeyInfo[m_upStateKeyInfo.keyType->at(i)].nowStateElapsedTime += Ctlan::PublicSystem::Time::DeltaTime * 0.0001f;
		}
	}
}

void Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::KeepNowKeyInfo()
{
	// ���݂̃L�[��Ԃ�ۑ�
	memcpy(m_lateKeyInfo, m_nowKeyInfo, sizeof(m_nowKeyInfo));
}

void Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::SetKeyDown(int key)
{
	// �����������@����̃��Z�b�g�����@���������� //
	// �����ꂽ����̓r���ŃL�[�������ꂽ�H
	if (m_nowKeyInfo[key].keyState == Up)
	{
		// ����Ă���L�[�̔��肩�珜�O
		m_upStateKeyInfo.keyType->erase(std::find(m_upStateKeyInfo.keyType->begin(), m_upStateKeyInfo.keyType->end(), key));
		// �v�f�������炷
		m_upStateKeyInfo.keyIndex--;
		// �o�ߎ��Ԃ����Z�b�g
		m_nowKeyInfo[key].nowStateElapsedTime = 0.0;
	}

	// �����������@�����ꂽ�L�[�̏����@���������� //
	// �O��L�[�͗�����Ă����H
	if (m_nowKeyInfo[key].keyState != Down)
	{
		// �L�[��������Ă��邱�Ƃ�ۑ�
		m_nowKeyInfo[key].keyState = Down;
		// ������Ă���L�[�̎�ނ�ۑ�
		m_downStateKeyInfo.keyType->emplace_back(key);
		// �v�f���𑝂₷
		m_downStateKeyInfo.keyIndex++;
		
#if _DEBUG
		// �V���[�g�J�b�g�R�}���h�̎��s
		ApplicationSystem::ShortCutKey::Run(key);
		// �e�L�X�g�̓��͏���
		SystemTextRendererManager::Input(key);
#endif
	}
}

void Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::SetKeyUp(int key)
{
	// �����������@����̕ύX�����@���������� //
	// �O��L�[�͉�����Ă����H
	if (m_nowKeyInfo[key].keyState == Down)
	{
		// ����Ă���L�[�̔��肩�珜�O
		m_downStateKeyInfo.keyType->erase(std::find(m_downStateKeyInfo.keyType->begin(), m_downStateKeyInfo.keyType->end(), key));

		// �v�f�������炷
		m_downStateKeyInfo.keyIndex--;

		// �o�ߎ��Ԃ����Z�b�g
		m_nowKeyInfo[key].nowStateElapsedTime = 0.0;


		// �����������@�����ꂽ�L�[�̏����@���������� //
		// �L�[��������Ă��邱�Ƃ�ۑ�
		m_nowKeyInfo[key].keyState = Up;

		// �����ꂽ�L�[�̎�ނ�ۑ�
		m_upStateKeyInfo.keyType->emplace_back(key);

		// �v�f���𑝂₷
		m_upStateKeyInfo.keyIndex++;
	}
}

bool Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyDownTrigger(Ctlan::PublicSystem::KeyName key)
{
	if (m_lateKeyInfo[key].keyState != m_nowKeyInfo[key].keyState)
	{
		int a = 0;
		a = a;
	}

	// �O��L�[�͗�����Ă������A���݂͉�����Ă���Ȃ�true
	return m_lateKeyInfo[key].keyState != Down && m_nowKeyInfo[key].keyState == Down;
}

bool Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyDown(Ctlan::PublicSystem::KeyName key)
{
	// ���݃L�[�͉�����Ă���Ȃ�true
	return m_nowKeyInfo[key].keyState == Down;
}

double Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyDownTime(Ctlan::PublicSystem::KeyName key)
{
	// �L�[��������Ă���H
	if (m_nowKeyInfo[key].keyState == Down)
		// �o�ߎ��Ԃ�Ԃ�
		return m_nowKeyInfo[key].nowStateElapsedTime;
	
	return 0;
}

bool Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyUpTrigger(Ctlan::PublicSystem::KeyName key)
{
	// �O��L�[�͉�����Ă������A���݂͗�����Ă���Ȃ�true
	return m_lateKeyInfo[key].keyState == Down && m_nowKeyInfo[key].keyState != Down;
}

bool Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyUp(Ctlan::PublicSystem::KeyName key)
{
	// ���݃L�[�͗�����Ă���H
	return m_nowKeyInfo[key].keyState == NoStatus || m_nowKeyInfo[key].keyState == Up;
}

double Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyUpTime(Ctlan::PublicSystem::KeyName key)
{
	// �L�[��������Ă���H
	if (m_nowKeyInfo[key].keyState == Up)
		// �o�ߎ��Ԃ�Ԃ�
		return m_nowKeyInfo[key].nowStateElapsedTime;

	return 0;
}
