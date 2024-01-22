// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "SystemTimeManager.h"
#include "Time.h"

#include <Windows.h>


// ������������������������������������ //
// �@�@   �@���C�u�����̃����N�@        //
// ������������������������������������ //
#pragma comment (lib, "winmm.lib")	// timeGetTime()���g�����߂Ƀ����N����


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
double Ctlan::PrivateSystem::SystemManager::SystemTimeManager::m_lastTime;


void Ctlan::PrivateSystem::SystemManager::SystemTimeManager::Init()
{
	// ���������Ɍ��ݎ����������Ă���
	m_lastTime = timeGetTime();
}

void Ctlan::PrivateSystem::SystemManager::SystemTimeManager::Update()
{
	timeBeginPeriod(1);				// ���x���P�~���b�ɏグ��
	DWORD nowTime = timeGetTime();	// ���ݎ������擾
	timeEndPeriod(1);				// ���x�����ɖ߂�

	// ���ݎ���-�O�񎞍��ŋ��߂��l���f���^�^�C���ɑ��
	Ctlan::PublicSystem::Time::DeltaTime = nowTime - m_lastTime;

	//��-----�f���^�^�C���̒���-----��//
	if (Ctlan::PublicSystem::Time::DeltaTime <= 0)	// �f���^�^�C�����O�ȉ��H
		Ctlan::PublicSystem::Time::DeltaTime = 1;	// �l���P�ɒ���

	m_lastTime = nowTime;			// ���ݎ�����ۑ�
}
