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
yUno_SystemManager::KEY_INFO yUno_SystemManager::yUno_KeyInputManager::Now_KeyInfo[400];
yUno_SystemManager::KEY_INFO yUno_SystemManager::yUno_KeyInputManager::Late_KeyInfo[400];
std::vector<int> yUno_SystemManager::yUno_KeyInputManager::Down_KeyType[400];
std::vector<int> yUno_SystemManager::yUno_KeyInputManager::Up_KeyType[400];
int yUno_SystemManager::yUno_KeyInputManager::Down_KeyType_Index;
int yUno_SystemManager::yUno_KeyInputManager::Up_KeyType_Index;


// ������������������������������������ //
//	�@�@�@�@�@�O���[�o���錾			//
// ������������������������������������ //
// ����CPP����KeyInput�̕ϐ����g�p���邽�߂ɃO���[�o���錾
System::KeyInput g_KeyInput;


void yUno_SystemManager::yUno_KeyInputManager::Update()
{
	// ���������� �e�L�[��Ԃ̌o�ߎ��Ԃ𑪒� ���������� //
	// �� ������Ă���L�[ �� //
	// �L�[��������Ă���H�i������Ă��Ȃ��ꍇ�͏������s��Ȃ��j
	if (!Down_KeyType->empty())
	{
		// ������Ă���L�[�̐��������[�v
		for (int i = 0; i < Down_KeyType_Index; i++)
		{
			// �L�[�̉�����Ă��鎞�Ԃ��v�Z
			Now_KeyInfo[Down_KeyType->at(i)].KeyState_ElapsedTime += System::Time::DeltaTime * 0.0001f;
		}
	}
	// �� ������Ă���L�[ �� //
	// �L�[��������Ă���i������s���Ă���L�[�����݂���j�H�i������Ă��Ȃ��i������s���Ă���L�[�����݂��Ȃ��j�ꍇ�͏������s��Ȃ��j
	if (!Up_KeyType->empty())
	{
		// ������Ă���L�[�̐��������[�v
		for (int i = 0; i < Up_KeyType_Index; i++)
		{
			// �L�[�̗�����Ă��鎞�Ԃ��v�Z
			Now_KeyInfo[Up_KeyType->at(i)].KeyState_ElapsedTime += System::Time::DeltaTime * 0.0001f;
		}
	}
}

void yUno_SystemManager::yUno_KeyInputManager::Keep_Now_KeyInfo()
{
	// ���݂̃L�[��Ԃ�ۑ�
	memcpy(Late_KeyInfo, Now_KeyInfo, sizeof(Now_KeyInfo));
}

void yUno_SystemManager::yUno_KeyInputManager::Set_KeyDown(int _key)
{
	// �����������@����̃��Z�b�g�����@���������� //
	// �����ꂽ����̓r���ŃL�[�������ꂽ�H
	if (Now_KeyInfo[_key].KeyState == Up)
	{
		// ����Ă���L�[�̔��肩�珜�O
		Up_KeyType->erase(std::find(Up_KeyType->begin(), Up_KeyType->end(), _key));

		// �v�f�������炷
		Up_KeyType_Index--;

		// �o�ߎ��Ԃ����Z�b�g
		Now_KeyInfo[_key].KeyState_ElapsedTime = 0.0;
	}

	// �����������@�����ꂽ�L�[�̏����@���������� //
	// �O��L�[�͗�����Ă����H
	if (Now_KeyInfo[_key].KeyState != Down)
	{
		// �L�[��������Ă��邱�Ƃ�ۑ�
		Now_KeyInfo[_key].KeyState = Down;

		// ������Ă���L�[�̎�ނ�ۑ�
		Down_KeyType->emplace_back(_key);

		// �v�f���𑝂₷
		Down_KeyType_Index++;
	}
	else
	{
		int a = 0;
		a = a;
	}
}

void yUno_SystemManager::yUno_KeyInputManager::Set_KeyUp(int _key)
{
	// �����������@����̕ύX�����@���������� //
	// �O��L�[�͉�����Ă����H
	if (Now_KeyInfo[_key].KeyState == Down)
	{
		// ����Ă���L�[�̔��肩�珜�O
		Down_KeyType->erase(std::find(Down_KeyType->begin(), Down_KeyType->end(), _key));

		// �v�f�������炷
		Down_KeyType_Index--;

		// �o�ߎ��Ԃ����Z�b�g
		Now_KeyInfo[_key].KeyState_ElapsedTime = 0.0;


		// �����������@�����ꂽ�L�[�̏����@���������� //
		// �L�[��������Ă��邱�Ƃ�ۑ�
		Now_KeyInfo[_key].KeyState = Up;

		// �����ꂽ�L�[�̎�ނ�ۑ�
		Up_KeyType->emplace_back(_key);

		// �v�f���𑝂₷
		Up_KeyType_Index++;
	}
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyDown_Trigger(System::KeyName _key)
{
	// �O��L�[�͗�����Ă������A���݂͉�����Ă���H
	if (Late_KeyInfo[_key].KeyState != Down && Now_KeyInfo[_key].KeyState == Down)
		return true;
	return false;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyDown(System::KeyName _key)
{
	// ���݃L�[�͉�����Ă���H
	if (Now_KeyInfo[_key].KeyState == Down)
		return true;
	return false;
}

double yUno_SystemManager::yUno_KeyInputManager::GetKeyDown_Time(System::KeyName _key)
{
	// �L�[��������Ă���H
	if (Now_KeyInfo[_key].KeyState == Down)
	{
		return Now_KeyInfo[_key].KeyState_ElapsedTime;
	}

	return 0;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyUp_Trigger(System::KeyName _key)
{
	// �O��L�[�͉�����Ă������A���݂͗�����Ă���H
	if (Late_KeyInfo[_key].KeyState == Down && Now_KeyInfo[_key].KeyState != Down)
		return true;
	return false;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyUp(System::KeyName _key)
{
	// ���݃L�[�͗�����Ă���H
	if (Now_KeyInfo[_key].KeyState == NoStatus || Now_KeyInfo[_key].KeyState == Up)
		return true;
	return false;
}

double yUno_SystemManager::yUno_KeyInputManager::GetKeyUp_Time(System::KeyName _key)
{
	// �L�[��������Ă���H
	if (Now_KeyInfo[_key].KeyState == Up)
	{
		return Now_KeyInfo[_key].KeyState_ElapsedTime;
	}

	return 0;
}
