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

namespace yUno_SystemManager
{
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�Ɋւ���@�\���܂Ƃ߂��N���X	</summary>
	class yUno_GameObjectManager
	{
		public:
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
				/// ���ʗp�̃I�u�W�F�N�g�ԍ�	</summary>
				int number;
			};

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
			///	�I�u�W�F�N�g�������擾	</summary>
			/// <param name="name">
			///	�擾����I�u�W�F�N�g��	</param>
			/// <returns>
			/// �I�u�W�F�N�g�����	</returns>
			static ObjectNameData GetObjectNameData(const char* name);
			/// <summary>
			///	�I�u�W�F�N�g������ݒ�	</summary>
			/// <param name="objNameData">
			/// �ݒ肷��I�u�W�F�N�g�����	</param>
			static void SetObjectNameData(ObjectNameData objNameData);
			/// <summary>
			/// �I�u�W�F�N�g�������폜	/// </summary>
			/// <param name="name"></param>
			static void DeleteObjectNameData(const char* name);
		
		private:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			///	�I�u�W�F�N�g�����X�g	</summary>
			static std::list<ObjectNameData>m_objectNameList;
	};
}

