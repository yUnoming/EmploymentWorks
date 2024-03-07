#pragma once
/**
* @file		Message.h
* @brief	�l�b�g���[�N�ʐM�Ŏg�p���郁�b�Z�[�W���܂Ƃ߂��t�@�C��
* @author	Kojima, Kosei
* @date		2023.12.11
*/

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "Transform.h"
#include "Text.h"

// ������������������������������ //
// �@		 �񋓌^�錾	   	�@�@  //
// ������������������������������ //
namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		///	���b�Z�[�W�̎��	</summary>
		enum MessageType
		{
			// ----- �ʐM���� ----- //
			/// <summary>
			///	�ʐM�J�n	</summary>
			CommunicationStart,
			/// <summary>
			///	�ʐM����	</summary>
			CommunicationSuccess,
			/// <summary>
			///	�ʐM�I��	</summary>
			CommunicationEnd,

			// ----- �R���|�[�l���g ----- //
			/// <summary>
			///	�R���|�[�l���g�X�V	</summary>
			UpdateComponent,

			// ----- �I�u�W�F�N�g�S�� ----- //
			/// <summary>
			///	�I�u�W�F�N�g�N���b�N	</summary>
			ClickObject,
			/// <summary>
			/// �I�u�W�F�N�g�폜	</summary>
			ObjectDelete,

			// ----- �e���v���[�g�I�u�W�F�N�g ----- //
			/// <summary>
			///	�L���[�u�쐬	</summary>
			CreateCube,
			/// <summary>
			///	�e�L�X�g�쐬	</summary>
			CreateText
		};

		// ������������������������������ //
		// �@		 �\���̐錾	   	�@�@  //
		// ������������������������������ //
		/// <summary>
		/// ���b�Z�[�W�w�b�_�[
		///�F���b�Z�[�W�̊�b�I�ȏ�񂪓����Ă���	</summary>
		struct Header
		{
			Header() {};
			~Header() {};

			/// <summary>
			/// ����M���郁�b�Z�[�W�̎��	</summary>
			int type = 0;
			/// <summary>
			///	���M�����[�U�[�̃����N	</summary>
			int userRank = 0;
			/// <summary>
			///	���M�����[�U�[�ԍ�	</summary>
			int userNo = 0;
		};

		/// <summary>
		/// �I�u�W�F�N�g�֌W�̃��b�Z�[�W�{�f�B�[
		/// �F���b�Z�[�W�̋�̓I�ȏ�񂪓����Ă���	</summary>
		struct BodyObject
		{
			BodyObject() { transform = 0; text = 0; };
			~BodyObject() {};

			/// <summary>
			///	�I�u�W�F�N�g���	</summary>
			GameObject object;
			/// <summary>
			///	�R���|�[�l���g�̎��	</summary>
			char componentType[50]{};
			/// <summary>
			///	�e�R���|�[�l���g���	</summary>
			union
			{
				Ctlan::PublicSystem::Transform transform;
				Ctlan::PublicSystem::Text text;
			};
		};

		/// <summary>
		/// �V�[���֌W�̃��b�Z�[�W�{�f�B�[
		/// �F���b�Z�[�W�̋�̓I�ȏ�񂪓����Ă���	</summary>
		struct BodyScene
		{
			BodyScene() {};
			~BodyScene() {};

			/// <summary>
			///	�V�[����	</summary>
			char sceneName[30]{};
			/// <summary>
			///	�V�[���f�[�^	</summary>
			char sceneData[1024]{};
		};

		/// <summary>
		///	���b�Z�[�W���e	</summary>
		struct Message
		{
			Message(){};
			~Message(){};

			/// <summary>
			///	���b�Z�[�W�w�b�_�[	</summary>
			Header header;
			/// <summary>
			///	���b�Z�[�W�{�f�B�[	</summary>
			union
			{
				BodyObject   bodyObject;
				BodyScene	 bodyScene;
			};
		};

		/// <summary>
		///	����M�p�̃��b�Z�[�W���	</summary>
		struct MessageData
		{
			MessageData() {};
			~MessageData() {};
			union
			{
				/// <summary>
				///	���b�Z�[�W���e	</summary>
				Message message;
				/// <summary>
				///	����M�ň������	</summary>
				char data[sizeof(Message)]{};
			};
		};
	}
}