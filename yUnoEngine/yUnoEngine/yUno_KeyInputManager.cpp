// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "yUno_KeyInputManager.h"
#include "KeyInput.h"
#include "Time.h"

#include <Windows.h>


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
yUno_SystemManager::yUno_KeyInputManager::KeyInfo yUno_SystemManager::yUno_KeyInputManager::m_nowKeyInfo[400];
yUno_SystemManager::yUno_KeyInputManager::KeyInfo yUno_SystemManager::yUno_KeyInputManager::m_lateKeyInfo[400];
yUno_SystemManager::yUno_KeyInputManager::CheckKeyInfo yUno_SystemManager::yUno_KeyInputManager::m_upStateKeyInfo;
yUno_SystemManager::yUno_KeyInputManager::CheckKeyInfo yUno_SystemManager::yUno_KeyInputManager::m_downStateKeyInfo;


void yUno_SystemManager::yUno_KeyInputManager::Update()
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
			m_nowKeyInfo[m_downStateKeyInfo.keyType->at(i)].nowStateElapsedTime += PublicSystem::Time::DeltaTime * 0.0001f;
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
			m_nowKeyInfo[m_upStateKeyInfo.keyType->at(i)].nowStateElapsedTime += PublicSystem::Time::DeltaTime * 0.0001f;
		}
	}
}

void yUno_SystemManager::yUno_KeyInputManager::KeepNowKeyInfo()
{
	// ���݂̃L�[��Ԃ�ۑ�
	memcpy(m_lateKeyInfo, m_nowKeyInfo, sizeof(m_nowKeyInfo));
}

void yUno_SystemManager::yUno_KeyInputManager::SetKeyDown(int key)
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
	}
}

void yUno_SystemManager::yUno_KeyInputManager::SetKeyUp(int key)
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

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyDownTrigger(PublicSystem::KeyName key)
{
	// �O��L�[�͗�����Ă������A���݂͉�����Ă���Ȃ�true
	return m_lateKeyInfo[key].keyState != Down && m_nowKeyInfo[key].keyState == Down;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyDown(PublicSystem::KeyName key)
{
	// ���݃L�[�͉�����Ă���Ȃ�true
	return m_nowKeyInfo[key].keyState == Down;
}

double yUno_SystemManager::yUno_KeyInputManager::GetKeyDownTime(PublicSystem::KeyName key)
{
	// �L�[��������Ă���H
	if (m_nowKeyInfo[key].keyState == Down)
		// �o�ߎ��Ԃ�Ԃ�
		return m_nowKeyInfo[key].nowStateElapsedTime;
	
	return 0;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyUpTrigger(PublicSystem::KeyName key)
{
	// �O��L�[�͉�����Ă������A���݂͗�����Ă���Ȃ�true
	return m_lateKeyInfo[key].keyState == Down && m_nowKeyInfo[key].keyState != Down;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyUp(PublicSystem::KeyName key)
{
	// ���݃L�[�͗�����Ă���H
	return m_nowKeyInfo[key].keyState == NoStatus || m_nowKeyInfo[key].keyState == Up;
}

double yUno_SystemManager::yUno_KeyInputManager::GetKeyUpTime(PublicSystem::KeyName key)
{
	// �L�[��������Ă���H
	if (m_nowKeyInfo[key].keyState == Up)
		// �o�ߎ��Ԃ�Ԃ�
		return m_nowKeyInfo[key].nowStateElapsedTime;

	return 0;
}
