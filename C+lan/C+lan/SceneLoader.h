#pragma once
#include "C+lan.h"

class SceneLoader : public EachFunction
{
	public:
		char loadSceneName[30]{};

		void Update()
		{
			// �G���^�[�L�[�������ꂽ�H
			if (KeyInput::GetKeyDownTrigger(Enter))
			{
				// �ݒ肳�ꂽ�V�[�������[�h
				SceneManager::LoadScene(loadSceneName);
			}
		}
};

