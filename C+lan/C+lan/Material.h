#pragma once
/**
* @file		Material.h
* @brief	Material�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.02
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "Color.h"


namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// �I�u�W�F�N�g�̐F�E�����Ȃǂ�\���N���X	</summary>
		class Material : public EachFunction
		{
			public:
				// ----- variables / �ϐ� ----- //
				/// <summary>
				///�}�e���A���̐F	</summary>
				Color materialColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

				// ----- functions / �֐� ----- //
				/// <summary>
				/// �`��	</summary>
				void Draw();

				/// <summary>
				/// �}�e���A���̐F��ύX����	</summary>
				/// <param name = "_colorParam">
				///	RGBA�̒l�iColor�N���X�I�u�W�F�N�g�Ŏw��j	</param>
				void SetMaterialColor(Ctlan::PublicSystem::Color colorParam);
		};
	}
}