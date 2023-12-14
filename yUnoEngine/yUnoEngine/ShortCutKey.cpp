#include "ShortCutKey.h"
#include "SceneManager.h"
#include "SpectatorCamera.h"

void yUno_SystemParts::ShortCutKey::Run(int key)
{
	// ===== コマンド実行 ===== //
	// 入力されたキーの種類によって処理を分岐
	switch (key)
	{
		case PublicSystem::Delete:
		{
			SpectatorCamera specCamera = *SceneManager::GetNowScene()->GetSceneObject<SpectatorCamera>("SpectatorCamera");
			if (specCamera.GetClickedObject() != nullptr)
			{
				SceneManager::GetNowScene()->DeleteSceneObject(specCamera.GetClickedObject()->GetName());
			}
		}
	}
}
