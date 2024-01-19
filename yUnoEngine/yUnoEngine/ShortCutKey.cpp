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
			EngineObject::SpectatorCamera specCamera = *yUno_SceneManager::GetEditScene()->GetSceneObject<EngineObject::SpectatorCamera>("SpectatorCamera");
			if (specCamera.GetClickedObject() != nullptr)
			{
				specCamera.GetClickedObject()->Destroy();
			}
		}
	}
}
