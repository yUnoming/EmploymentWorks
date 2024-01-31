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
			// 経過時間を計算
			elapsedTime += Time::DeltaTime * 0.001f;

			// 時間をテキストとして描画
			Text* text = GetComponent<Text>();
			std::string timeString(std::to_string(TimeLimit - elapsedTime));
			text->ChangeText(timeString.c_str());

			// 制限時間を超えた？
			if (elapsedTime >= TimeLimit)
			{
				// クリアシーンをロード
				SceneManager::LoadScene("GameClearScene");
			}
		}
};

