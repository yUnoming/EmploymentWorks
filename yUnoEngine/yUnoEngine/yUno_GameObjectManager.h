#pragma once
/**
* @file		yUno_GameObjectManager.h
* @brief	yUno_GameObjectManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.12.08
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <list>
#include <vector>
#include "GameObject.h"

namespace yUno_SystemManager
{
	/// <summary>
/// �Q�[���I�u�W�F�N�g�Ɋւ���@�\���܂Ƃ߂��N���X	</summary>
	class yUno_GameObjectManager
	{
	private:
		// ----- structs / �\���� ----- //
		/// <summary>
		/// �I�u�W�F�N�g�����	</summary>
		struct ObjectNameData
		{
			/// <summary>
			///	���g�̃I�u�W�F�N�g��	</summary>
			char myName[30];
			/// <summary>
			///	���̃I�u�W�F�N�g��	</summary>
			char baseName[30];
			/// <summary>
			///	�I�u�W�F�N�g���ɕt�^����ԍ��i���̔��h�~�j	</summary>
			int objectNameNumber;
		};
		/// <summary>
		/// �I�u�W�F�N�g�ԍ����	</summary>
		struct ObjectNumberData
		{
			/// <summary>
			///	�I�u�W�F�N�g��	</summary>
			const char* name;
			/// <summary>
			///	�󂫔ԍ�	</summary>
			std::vector<int> emptyNumber;
			/// <summary>
			///	�ԍ��̍ő�l	</summary>
			int maxNumber;
		};

		// ----- variables / �ϐ� ----- //
		/// <summary>
		///	�I�u�W�F�N�g�����X�g	</summary>
		static std::list<ObjectNameData>m_objectNameList;
		/// <summary>
		///	�I�u�W�F�N�g�ԍ����X�g	</summary>
		static std::list<ObjectNumberData>m_objectNumberList;

	public:
		// ----- functions / �֐� ----- //
		static void UnInit();

		/// <summary>
		///	�I�u�W�F�N�g�������ɑ��݂��邩�ǂ����m�F	</summary>
		/// <param name="name">
		/// �m�F����I�u�W�F�N�g��	</param>
		/// <returns>
		///	���ۂɕt����I�u�W�F�N�g��	</returns>
		static const char* CheckObjectName(const char* name);
		/// <summary>
		///	�I�u�W�F�N�g���ɕt�^����ԍ����擾	</summary>
		/// <param name="name">
		///	�擾����I�u�W�F�N�g��	</param>
		/// <returns>
		/// �t�^����ԍ�	</returns>
		static int GetObjectNumber(const char* name);
		/// <summary>
		///	�I�u�W�F�N�g���ɕt�^����ԍ���ݒ�	</summary>
		/// <param name="name">
		/// �ݒ肷��I�u�W�F�N�g��	</param>
		static void SetObjectNumber(const char* name);
	};
}

