#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "Vector3.h"

using namespace PublicSystem;

class Transform : public EachFunction
{
	public:

		// ----- variables / �ϐ� ----- //
		Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);	// �ʒu
		Vector3 Rotation = Vector3(0.0f, 0.0f, 0.0f);	// ��]
		Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);		// �傫��
};


namespace PublicSystem
{

}

