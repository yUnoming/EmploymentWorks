#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "Color.h"

namespace PublicSystem
{
	// �I�u�W�F�N�g�̐F�E�����Ȃǂ�\���N���X
	class Material : public EachFunction
	{
		public:
			// ----- variables / �ϐ� ----- //
			Color Material_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);	// �}�e���A���̐F

			// ----- functions / �֐� ----- //
			/// <summary>
			/// �}�e���A���̐F��ύX����	</summary>
			/// <param name = "_colorParam">
			///	RGBA�𐔒l�Ŏw��	</param>
			void SetMateiralColor(PublicSystem::Color _colorParam);
	};
}

