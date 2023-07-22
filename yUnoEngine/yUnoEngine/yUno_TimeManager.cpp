// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "yUno_TimeManager.h"
#include "Time.h"

#include <Windows.h>


// ������������������������������������ //
// �@�@   �@���C�u�����̃����N�@        //
// ������������������������������������ //
#pragma comment (lib, "winmm.lib")	// timeGetTime()���g�����߂Ƀ����N����


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
double yUno_SystemManager::yUno_TimeManager::m_Last_Time;


void yUno_SystemManager::yUno_TimeManager::Init()
{
	// ���������Ɍ��ݎ����������Ă���
	m_Last_Time = timeGetTime();
}

void yUno_SystemManager::yUno_TimeManager::Update()
{
	timeBeginPeriod(1);				// ���x���P�~���b�ɏグ��
	DWORD Now_Time = timeGetTime();	// ���ݎ������擾
	timeEndPeriod(1);				// ���x�����ɖ߂�

	// ���ݎ���-�O�񎞍��ŋ��߂��l���f���^�^�C���ɑ��
	System::Time::DeltaTime = Now_Time - m_Last_Time;

	//��-----�f���^�^�C���̒���-----��//
	if (System::Time::DeltaTime <= 0)	// �f���^�^�C�����O�ȉ��H
		System::Time::DeltaTime = 1;	// �l���P�ɒ���

	m_Last_Time = Now_Time;			// ���ݎ�����ۑ�
}
