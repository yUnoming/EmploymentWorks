#pragma once
#include "C+lan.h"

class SceneLoader : public EachFunction
{
	public:
		char loadSceneName[30]{};

		void Update()
		{
			// エンターキーが押された？
			if (KeyInput::GetKeyDownTrigger(Enter))
			{
				// 設定されたシーンをロード
				SceneManager::LoadScene(loadSceneName);
			}
		}
};

