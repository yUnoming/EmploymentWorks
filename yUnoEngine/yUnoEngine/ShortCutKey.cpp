#include "ShortCutKey.h"
#include "SceneManager.h"
#include "SpectatorCamera.h"

void yUno_SystemParts::ShortCutKey::Run(int key)
{
	// ===== �R�}���h���s ===== //
	// ���͂��ꂽ�L�[�̎�ނɂ���ď����𕪊�
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
