#pragma once
/**
* @file		SpectatorCamera.h
* @brief	SpectatorCamera�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "SceneBase.h"

namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	�G���W�����Ŏg���J�����I�u�W�F�N�g	</summary>
		class SpectatorCamera : public Ctlan::PrivateSystem::GameObject
		{
		private:
			// ----- variables / �ϐ� ----- //
			///<summary>
			///�N���b�N���ꂽ�I�u�W�F�N�g	</summary>
			GameObject* m_clickedObject = nullptr;
			/// <summary>
			///	�N���b�N���ꂽ�}�j�s�����[�^�[	</summary>
			GameObject* m_clickedManipulator = nullptr;

		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			///	�R���X�g���N�^	</summary>
			SpectatorCamera() : GameObject() {};
			/// <summary>
			///	�����t���R���X�g���N�^	</summary>
			/// <param name="nowScene">
			///	�I�u�W�F�N�g���������ꂽ�V�[��	</param>
			SpectatorCamera(SceneBase* nowScene) : GameObject(nowScene) {};

			/// <summary>
			///	������	</summary>
			void Init();
			/// <summary>
			///	�X�V	</summary>
			void Update();

			/// <summary>
			///	�N���b�N����Ă���I�u�W�F�N�g��Ԃ�	</summary>
			/// <returns>
			///	�I�u�W�F�N�g������΃I�u�W�F�N�g���A�Ȃ����nullptr��Ԃ�	</returns>
			GameObject* GetClickedObject() const;
			/// <summary>
			///	�N���b�N���ꂽ�}�j�s�����[�^�[�I�u�W�F�N�g��Ԃ�	</summary>
			/// <returns>
			///	�I�u�W�F�N�g������΃I�u�W�F�N�g���A�Ȃ����nullptr��Ԃ�	</returns>
			GameObject* GetClickedManipulator() const;
			/// <summary>
			///	�N���b�N��Ԃ�����	</summary>
			void ReleaseClickedObject() { m_clickedObject = nullptr;};
		};
	}
}

