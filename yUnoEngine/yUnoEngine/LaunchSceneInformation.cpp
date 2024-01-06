#include "LaunchSceneInformation.h"
#include "SceneManager.h"
#include <stdio.h>
#include <Windows.h>


yUnoEngine::Information::LaunchSceneInformation::LaunchSceneInformation()
{
	ZeroMemory(m_launchSceneName, sizeof(m_launchSceneName));
}

void yUnoEngine::Information::LaunchSceneInformation::Load()
{
	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, "Assets\\LaunchScene.info", "rb");

	// �J�����Ƃ��o�����H
	if (file)
	{
		// �t�@�C���ǂݎ��
		fread(m_launchSceneName, sizeof(m_launchSceneName), 1, file);
		fclose(file);
	}
}

void yUnoEngine::Information::LaunchSceneInformation::Save()
{
	// ���̎擾
	strcpy_s(m_launchSceneName, SceneManager::GetNowScene()->GetSceneName());

	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, "Assets\\LaunchScene.info", "wb");

	// �J�����Ƃ��o�����H
	if (file)
	{
		// �t�@�C����������
		fwrite(m_launchSceneName, sizeof(m_launchSceneName), 1, file);
		fclose(file);
	}
}

const char* yUnoEngine::Information::LaunchSceneInformation::GetLaunchSceneName()
{
	// �J���V�[�������݂��Ȃ��H
	if (strlen(m_launchSceneName) == 0)
		return nullptr;			// nullptr��Ԃ�
	// �J���V�[��������΁A���̃V�[������Ԃ�
	return m_launchSceneName;
}