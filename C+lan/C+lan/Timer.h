#pragma once
#include "EachFunction.h"
#include "C+lan.h"

class Timer : public EachFunction
{
	private:
		float TimeLimit = 30.0f;
		float elapsedTime = 0.0f;
	
	public:
		void Update()
		{
			// �o�ߎ��Ԃ��v�Z
			elapsedTime += Time::DeltaTime * 0.001f;

			// ���Ԃ��e�L�X�g�Ƃ��ĕ`��
			Text* text = GetComponent<Text>();
			std::string timeString(std::to_string(TimeLimit - elapsedTime));
			text->ChangeText(timeString.c_str());

			// �������Ԃ𒴂����H
			if (elapsedTime >= TimeLimit)
			{
				// �N���A�V�[�������[�h
				SceneManager::LoadScene("GameClearScene");
			}
		}
};

