#include "LaunchSceneInformation.h"
#include "SceneManager.h"
#include <stdio.h>
#include <Windows.h>


Ctlan::PrivateSystem::Information::LaunchSceneInformation::LaunchSceneInformation()
{
	ZeroMemory(m_launchSceneName, sizeof(m_launchSceneName));
}

void Ctlan::PrivateSystem::Information::LaunchSceneInformation::Load()
{
	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, "Assets/Scenes/LaunchScene.info", "rb");

	// �J�����Ƃ��o�����H
	if (file)
	{
		// �t�@�C���ǂݎ��
		fread(m_launchSceneName, sizeof(m_launchSceneName), 1, file);
		fclose(file);
	}
}

void Ctlan::PrivateSystem::Information::LaunchSceneInformation::Save()
{
	// ���̎擾
	strcpy_s(m_launchSceneName, SceneManager::GetNowScene()->GetSceneName());

	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, "Assets/Scenes/LaunchScene.info", "wb");

	// �J�����Ƃ��o�����H
	if (file)
	{
		// �t�@�C����������
		fwrite(m_launchSceneName, sizeof(m_launchSceneName), 1, file);
		fclose(file);
	}
}

const char* Ctlan::PrivateSystem::Information::LaunchSceneInformation::GetLaunchSceneName()
{
	// �J���V�[�������݂��Ȃ��H
	if (strlen(m_launchSceneName) == 0)
		return nullptr;			// nullptr��Ԃ�
	// �J���V�[��������΁A���̃V�[������Ԃ�
	return m_launchSceneName;
}
