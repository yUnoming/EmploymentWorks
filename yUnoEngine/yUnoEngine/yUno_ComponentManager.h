#pragma once
/**
* @file		Component.h
* @brief	Component�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Component.h"


namespace yUno_SystemManager
{
	/// <summary>
	///	�R���|�[�l���g�̏������Ǘ�����N���X	</summary>
	class yUno_ComponentManager
	{
		public:
			/// <summary>
			///	�R���|�[�l���g�̕ϐ��̒l��ʂ̃R���|�[�l���g�ɑ��	</summary>
			/// <param name="destComponent">
			///	�R�s�[��̃R���|�[�l���g���	</param>
			/// <param name="sourceComponent">
			/// �R�s�[���̃R���|�[�l���g���	</param>
			static void SetVariableValue(Component* destComponent, Component* sourceComponent);
			/// <summary>
			///	�R���|�[�l���g�̎�ނ����Ƀ��b�Z�[�W�𑗂�	</summary>
			/// <param name="lateComponent">
			///	�l�X�V�O�̃R���|�[�l���g���	</param>
			/// <param name="nowComponent">
			/// �l�X�V��̃R���|�[�l���g���	</param>
			static void SendMessageBasedOnType(Component* lateComponent, Component* nowComponent);
	};
}

