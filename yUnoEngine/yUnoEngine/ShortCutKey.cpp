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
			SpectatorCamera specCamera = *SceneManager::GetNowScene()->GetSceneObject<SpectatorCamera>("SpectatorCamera");
			if (specCamera.GetClickedObject() != nullptr)
			{
				SceneManager::GetNowScene()->DeleteSceneObject(specCamera.GetClickedObject()->GetName());
			}
		}
	}
}
