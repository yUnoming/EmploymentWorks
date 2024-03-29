#include "ShortCutKey.h"
#include "SceneManager.h"
#include "SpectatorCamera.h"

void Ctlan::PrivateSystem::ApplicationSystem::ShortCutKey::Run(int key)
{
	// ===== コマンド実行 ===== //
	// 入力されたキーの種類によって処理を分岐
	switch (key)
	{
		// Deleteキーの場合
		case Ctlan::PublicSystem::Delete:
		{
			// オブジェクトを選択している？
			Ctlan::EngineObject::SpectatorCamera* spectatorCamera = SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject<Ctlan::EngineObject::SpectatorCamera>("SpectatorCamera");
			if (spectatorCamera->GetClickedObject() != nullptr)
			{
				spectatorCamera->GetClickedObject()->Destroy();	// 選択中のオブジェクトを削除
				spectatorCamera->ReleaseClickedObject();
			}
		}
	}
}
