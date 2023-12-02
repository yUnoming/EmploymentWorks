#include "yUno_ComponentManager.h"
#include "yUno_NetWorkManager.h"
#include "Message.h"
#include "Transform.h"


void yUno_SystemManager::yUno_ComponentManager::SetVariableValue(Component* destComponent, Component* sourceComponent)
{
	// �R���|�[�l���g�̃^�C�v�擾
	const char* componentType = typeid(*destComponent).name();

	// ===== �R���|�[�l���g�̃^�C�v���珈���𕪊� ===== //
	// Transform�R���|�[�l���g�H
	if (strcmp(componentType, "class PublicSystem::Transform") == 0)
	{
		// Transform�R���|�[�l���g�ɒu��
		Transform* destTransform = (Transform*)destComponent;
		Transform* sourceTransform = (Transform*)sourceComponent;

		// �e�l����
		destTransform->Position = sourceTransform->Position;
		destTransform->Rotation = destTransform->Rotation;
		destTransform->Scale = destTransform->Scale;
	}
}

void yUno_SystemManager::yUno_ComponentManager::SendMessageBasedOnType(Component* lateComponent, Component* nowComponent)
{
	// �R���|�[�l���g�̃^�C�v�擾
	const char* componentType = typeid(*lateComponent).name();
	// ���b�Z�[�W�f�[�^
	MessageData messageData;
	
	// ===== �R���|�[�l���g�̃^�C�v���珈���𕪊� ===== //
	// Transform�R���|�[�l���g�H
	if (strcmp(componentType, "class PublicSystem::Transform") == 0)
	{
		// Transform�R���|�[�l���g�ɒu��
		Transform nowTransform = *(Transform*)nowComponent;
		Transform lateTransform = *(Transform*)lateComponent;

		// �l���X�V����Ă���H
		if (nowTransform.Position != lateTransform.Position ||
			nowTransform.Rotation != lateTransform.Rotation ||
			nowTransform.Scale != lateTransform.Scale)
		{
			// ----- ���M����l���� ----- //
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::UpdateComponent;
			// �I�u�W�F�N�g
			messageData.message.body.object.SetName(nowTransform.gameObject->GetName());
			// �R���|�[�l���g�^�C�v
			strcpy_s(messageData.message.body.componentType,
				sizeof(messageData.message.body.componentType),
				componentType);
			// �R���|�[�l���g���
			messageData.message.body.transform = nowTransform;
			
			// ���b�Z�[�W�𑗂鏈�������s
			yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData.data, sizeof(messageData.data));
		}
	}
}
