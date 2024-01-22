#include "ShortCutKey.h"
#include "SceneManager.h"
#include "SpectatorCamera.h"

void Ctlan::PrivateSystem::ApplicationSystem::ShortCutKey::Run(int key)
{
	// ===== �R�}���h���s ===== //
	// ���͂��ꂽ�L�[�̎�ނɂ���ď����𕪊�
	switch (key)
	{
		// Delete�L�[�̏ꍇ
		case Ctlan::PublicSystem::Delete:
		{
			// �I�u�W�F�N�g��I�����Ă���H
			Ctlan::EngineObject::SpectatorCamera specCamera = *SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject<Ctlan::EngineObject::SpectatorCamera>("SpectatorCamera");
			if (specCamera.GetClickedObject() != nullptr)
			{
				specCamera.GetClickedObject()->Destroy();	// �I�𒆂̃I�u�W�F�N�g���폜
			}
		}
	}
}
