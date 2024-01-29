#pragma once
/**
* @file		EditScene.h
* @brief	EditScene�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.12.25
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SceneBase.h"

#include "SpectatorCamera.h"
#include "PositionXGizmo.h"
#include "PositionYGizmo.h"
#include "PositionZGizmo.h"

#include "Camera.h"


namespace Ctlan
{
	namespace EngineScene
	{
		/// <summary>
		///	�G�f�B�b�g�V�[��	</summary>
		class EditScene : public Ctlan::PrivateSystem::SceneBase
		{
			private:
				// ----- structs / �\���� ----- //
				/// <summary>
				///	�V�[���ҏW���Ɏg���f�[�^	</summary>
				struct SceneEditorData
				{
					/// <summary>
					///	�ҏW���Ɏg�p����J�����̃R���|�[�l���g���	</summary>
					Transform transformComponent;	// �g�����X�t�H�[��
					Camera cameraComponent;			// �J����
				};

				// ----- variables / �ϐ� ----- //
				/// <summary>
				///	�V�[���ҏW�Ɏg�p����f�[�^	</summary>
				SceneEditorData m_sceneEditorData;
				/// <summary>
				///	�G�f�B�b�g���Ɏg�p����J����	</summary>
				Ctlan::EngineObject::SpectatorCamera* m_spectatorCamera;
				/// <summary>
				///	X���ړ��M�Y��	</summary>
				Ctlan::EngineObject::Gizmo::PositionXGizmo* m_positionXGizmo;
				/// <summary>
				///	Y���ړ��M�Y��	</summary>
				Ctlan::EngineObject::Gizmo::PositionYGizmo* m_positionYGizmo;
				/// <summary>
				///	Z���ړ��M�Y��	</summary>
				Ctlan::EngineObject::Gizmo::PositionZGizmo* m_positionZGizmo;

				// �f���v���C�����ǂ���
				bool isDemoPlay;

			public:
				// ----- functions / �֐� ----- //
				void Init() override;
				void Uninit() override;
				void Update() override;
				void Draw() override;

				/// <summary>
				///	�f���v���C�����ǂ������擾	</summary>
				/// <returns>
				///	�f���v���C���Ȃ�true�A����ȊO��false	</returns>
				bool IsDemoPlay() { return isDemoPlay; };
		};
	}
};

