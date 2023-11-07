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
double yUno_SystemManager::yUno_TimeManager::m_lastTime;


void yUno_SystemManager::yUno_TimeManager::Init()
{
	// ���������Ɍ��ݎ����������Ă���
	m_lastTime = timeGetTime();
}

void yUno_SystemManager::yUno_TimeManager::Update()
{
	timeBeginPeriod(1);				// ���x���P�~���b�ɏグ��
	DWORD nowTime = timeGetTime();	// ���ݎ������擾
	timeEndPeriod(1);				// ���x�����ɖ߂�

	// ���ݎ���-�O�񎞍��ŋ��߂��l���f���^�^�C���ɑ��
	PublicSystem::Time::DeltaTime = nowTime - m_lastTime;

	//��-----�f���^�^�C���̒���-----��//
	if (PublicSystem::Time::DeltaTime <= 0)	// �f���^�^�C�����O�ȉ��H
		PublicSystem::Time::DeltaTime = 1;	// �l���P�ɒ���

	m_lastTime = nowTime;			// ���ݎ�����ۑ�
}
