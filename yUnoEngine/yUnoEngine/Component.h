#pragma once
class Component
{
	public:

		// ----- functions / �֐� ----- //
		Component() {};				// �R���X�g���N�^
		virtual ~Component() {};	// �f�X�g���N�^

		virtual void Init() {};		// ������
		virtual void UnInit() {};	// �I��
		virtual void Update() {};	// �X�V
		virtual void Draw() {};		// �`��
};

