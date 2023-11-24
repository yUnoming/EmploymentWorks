// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "renderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "yUno_SceneManager.h"
#include "yUno_ComponentManager.h"

#include <algorithm>

using namespace PublicSystem;

GameObject::GameObject()
{
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <PublicSystem::Transform> ();
}

GameObject::GameObject(yUno_SceneManager* nowScene)
{
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <PublicSystem::Transform>();
	// ���݃V�[����������
	m_myScene = nowScene;
}

void GameObject::InitBase()
{
	// �I�u�W�F�N�g�̏���������
	Init();
}

void GameObject::UnInitBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_componentList)
	{
		com->UnInit();	// �I������
		delete com;		// �폜
	}

	// ���X�g���N���A
	m_componentList.clear();
	m_lateCompoenntList.clear();

	// �I�u�W�F�N�g�̏I������
	UnInit();
}


Component* Test(Component* component)
{
	const char* componentType = typeid(*component).name();

	if (strcmp(componentType, "class PublicSystem::Transform") == 0)
	{
		Transform* returnComponent = new Transform();
		Transform* baseComponent = (Transform*)component;
		returnComponent->Position = baseComponent->Position;
		returnComponent->Rotation = baseComponent->Rotation;
		returnComponent->Scale = baseComponent->Scale;
		return returnComponent;
	}
	return 0;
}

Component* comp;
void GameObject::UpdateBase()
{
	int index = 0;	// �v�f��

	// �e�R���|�[�l���g�̍X�V����
	for (auto com : m_componentList)
	{
		com->Update();
		
		// �l���X�V����Ă����烁�b�Z�[�W�𑗂�
		yUno_SystemManager::yUno_ComponentManager::SendMessageBasedOnType(*std::next(m_lateCompoenntList.begin(), index), com);
		// ���݂̒l��ۑ�
		yUno_SystemManager::yUno_ComponentManager::SetVariableValue(*std::next(m_lateCompoenntList.begin(), index), com);
		// �J�E���g�𑝂₷
		index++;
	}
	// �I�u�W�F�N�g�̍X�V����
	Update();
}

void GameObject::DrawBase(DirectX::SimpleMath::Matrix _parentMatrix)
{
	// �}�g���b�N�X�ݒ�
	DirectX::SimpleMath::Matrix world, trans, rot, scl;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(transform->Position.x, transform->Position.y, transform->Position.z);
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(transform->Rotation.y, transform->Rotation.x, transform->Rotation.z);
	scl = DirectX::SimpleMath::Matrix::CreateScale(transform->Scale.x, transform->Scale.y, transform->Scale.z);
	world = rot * trans * scl * _parentMatrix;

	Renderer::SetWorldMatrix(&world);

	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_componentList)
		com->Draw();	// �`�揈��

	// �I�u�W�F�N�g�̕`�揈��
	Draw();
}
