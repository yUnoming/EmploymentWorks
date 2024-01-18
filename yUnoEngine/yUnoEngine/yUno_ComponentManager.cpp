#include "yUno_NetWorkManager.h"
#include "yUno_ComponentManager.h"
#include "Transform.h"


void yUno_SystemManager::yUno_ComponentManager::SetVariableValue(Component* destComponent, Component* sourceComponent)
{
	// �l���
	// (�R���|�[�l���g�ɑ���I�y���[�^�[������ꍇ�́A������̏��������s�����)
	destComponent = sourceComponent;
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
		if (nowTransform.position != lateTransform.position ||
			nowTransform.rotation != lateTransform.rotation ||
			nowTransform.scale != lateTransform.scale)
		{
			// ----- ���M����l���� ----- //
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::UpdateComponent;
			// �I�u�W�F�N�g
			messageData.message.body.object.CopyName(nowTransform.gameObject->GetName());
			// �R���|�[�l���g�^�C�v
			strcpy_s(messageData.message.body.componentType,
				sizeof(messageData.message.body.componentType),
				componentType);
			// �R���|�[�l���g���
			messageData.message.body.transform = nowTransform;
			
			// ���b�Z�[�W�𑗂鏈�������s
			yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
	// Text�R���|�[�l���g�H
	else if (strcmp(componentType, "class PublicSystem::Text") == 0)
	{
		// Text�R���|�[�l���g�ɒu��
		Text nowText = *(Text*)nowComponent;
		Text lateText = *(Text*)lateComponent;

		// �l���X�V����Ă���H
		if (nowText.text != lateText.text ||
			nowText.fontSize != lateText.fontSize ||
			nowText.leftTopPoint != lateText.leftTopPoint)
		{
			// ----- ���M����l���� ----- //
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::UpdateComponent;
			// �I�u�W�F�N�g
			messageData.message.body.object.CopyName(nowText.gameObject->GetName());
			// �R���|�[�l���g�^�C�v
			strcpy_s(messageData.message.body.componentType,
				sizeof(messageData.message.body.componentType),
				componentType);
			// �R���|�[�l���g���
			messageData.message.body.text = nowText;

			// ���b�Z�[�W�𑗂鏈�������s
			yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
}
