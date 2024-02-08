#pragma once
/**
* @file		EachFunction.h
* @brief	EachFunction�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Component.h"
#include "GameObject.h"

namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		/// �R���|�[�l���g�Ŏg���������̂��܂Ƃ߂��N���X	</summary>
		class EachFunction : public Component
		{
			private:
				/// <summary>
				///	������	</summary>
				void Init() override {};
				/// <summary>				
				///	�I��	</summary>
				void Uninit() override {};
				/// <summary>
				///	�X�V	</summary>
				void Update() override {};
				/// <summary>
				/// �`��	</summary>
				void Draw() override {};

			public:
				// ----- variables / �ϐ� ----- //
				//! ���g�̐e�ł���I�u�W�F�N�g
				Ctlan::PrivateSystem::GameObject* parent = nullptr;

				//! �g�����X�t�H�[��
				class Transform* transform = nullptr;

				// ----- functions / �֐� ----- //
				using Component::Component;
				/// <summary>
				/// �R���X�g���N�^		</summary>
				EachFunction() {};

				//**  �R���|�[�l���g����  **//
				/// <summary>
				/// �R���|�[�l���g���擾 </summary>
				/// <param name="GetComponent&lt;&gt;();">
				/// &lt;&gt;���Ɏ擾�������R���|�[�l���g���L�q		</param>
				/// <returns>
				/// �擾�����R���|�[�l���g </returns>
				template<class T>
				T* GetComponent()
				{
					return gameObject->GetComponent<T>();
				}
				/// <summary>
				/// �R���|�[�l���g��ǉ�
				/// </summary>
				/// <param name="AddComponent&lt;&gt;();">
				/// &lt;&gt;���ɒǉ��������R���|�[�l���g���L�q		</param>
				/// <returns>
				/// �ǉ������R���|�[�l���g		</returns>
				template<class T>
				T* AddComponent()
				{
					return gameObject->AddComponent<T>();
				}
				/// <summary>
				/// �R���|�[�l���g���폜
				/// </summary>
				/// <param name="DeleteComponent&lt;&gt;();">
				/// &lt;&gt;���ɍ폜�������R���|�[�l���g���L�q		</param>
				template<class T>
				void DeleteComponent()
				{
					gameObject->DeleteComponent<T>();
				}
		};
	}
}
