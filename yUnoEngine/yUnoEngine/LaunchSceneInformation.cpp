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
	// シーンファイルを開く
	FILE* file;
	fopen_s(&file, "Assets\\LaunchScene.info", "rb");

	// 開くことが出来た？
	if (file)
	{
		// ファイル読み取り
		fread(m_launchSceneName, sizeof(m_launchSceneName), 1, file);
		fclose(file);
	}
}

void yUnoEngine::Information::LaunchSceneInformation::Save()
{
	// 情報の取得
	strcpy_s(m_launchSceneName, SceneManager::GetNowScene()->GetSceneName());

	// シーンファイルを開く
	FILE* file;
	fopen_s(&file, "Assets\\LaunchScene.info", "wb");

	// 開くことが出来た？
	if (file)
	{
		// ファイル書き込み
		fwrite(m_launchSceneName, sizeof(m_launchSceneName), 1, file);
		fclose(file);
	}
}

const char* yUnoEngine::Information::LaunchSceneInformation::GetLaunchSceneName()
{
	// 開くシーンが存在しない？
	if (strlen(m_launchSceneName) == 0)
		return nullptr;			// nullptrを返す
	// 開くシーンがあれば、そのシーン名を返す
	return m_launchSceneName;
}
