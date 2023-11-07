#pragma once
/**
* @file		Component.h
* @brief	Component�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.10.29
*/

/// <summary>
/// �R���|�[�l���g�N���X	</summary>
class Component
{
	public:
		// ----- functions / �֐� ----- //
		/// <summary>
		/// �R���X�g���N�^		</summary>
		Component() {};
		/// <summary>
		/// �f�X�g���N�^		</summary>
		virtual ~Component() {};

		/// <summary>
		/// ������		</summary>
		virtual void Init() {};
		/// <summary>
		/// �I��		</summary>
		virtual void UnInit() {};
		/// <summary>
		/// �X�V		</summary>
		virtual void Update() {};
		/// <summary>
		/// �`��		</summary>
		virtual void Draw() {};
		/// <summary>
		/// �Փ˔��莞	</summary>
		virtual void HitCollision() {};
};

