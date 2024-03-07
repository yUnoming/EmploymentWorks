#pragma once
#include "C+lan.h"

class Player : public EachFunction
{
	private:
		float speed = 0.0065f;
		Vector3 latePos = Vector3();

		Vector3 dashVec = Vector3();
		float dashElapsedTime = 0;
		bool isDash;

	public:
		void Update()
		{
			// 現在の座標を保存
			latePos = transform->position;

			// ----- WASD移動 ----- //
			if (KeyInput::GetKeyDown(W))
			{
				transform->position.y += speed * Ctlan::PublicSystem::Time::DeltaTime * 0.3f;
			}
			if (KeyInput::GetKeyDown(A))
			{
				transform->position.x -= speed * Ctlan::PublicSystem::Time::DeltaTime * 0.3f;
			}
			if (KeyInput::GetKeyDown(S))
			{
				transform->position.y -= speed * Ctlan::PublicSystem::Time::DeltaTime * 0.3f;
			}
			if (KeyInput::GetKeyDown(D))
			{
				transform->position.x += speed * Ctlan::PublicSystem::Time::DeltaTime * 0.3f;
			}

			// ----- Spaceダッシュ ----- //
			// ダッシュ開始？
			if (KeyInput::GetKeyDownTrigger(Space) && !isDash)
			{
				// ダッシュする方向を取得
				dashVec = (transform->position - latePos) * 10.0f;
				isDash = true;	// ダッシュ状態に切り替え
			}

			// ダッシュしている？
			if (isDash)
			{
				// 移動
				transform->position += dashVec * Ctlan::PublicSystem::Time::DeltaTime;
				// ベクトルを軽減
				dashVec -= dashVec + dashElapsedTime;
				// ダッシュの経過時間を計算
				dashElapsedTime = Ctlan::PublicSystem::Time::DeltaTime * 0.01f;

				// ベクトルの値がマイナスになった？
				if (dashVec.x < 0.0f)
					isDash = false;	// ダッシュ状態を切り替え
			}

		};

		void HitCollision(GameObject* other)
		{
			// ゲームオーバーシーンをロード
			SceneManager::LoadScene("GameOverScene");
		};
};

