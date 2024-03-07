#include "SystemNetWorkManager.h"
#include "SystemComponentManager.h"
#include "Transform.h"


void Ctlan::PrivateSystem::SystemManager::SystemComponentManager::SetVariableValue(Component* destComponent, Component* sourceComponent)
{
	// �R���|�[�l���g�̃^�C�v�擾
	char baseComponentType[50] = {};
	char componentType[30] = "Component";
	strcpy_s(baseComponentType, typeid(*destComponent).name());
	char* context{};
	char* token = strtok_s(baseComponentType, " ::", &context);
	while (token)
	{
		strcpy_s(componentType, token);
		token = strtok_s(NULL, " ::", &context);
	}

	// ���b�Z�[�W�f�[�^
	MessageData messageData;

	// ===== �R���|�[�l���g�̃^�C�v���珈���𕪊� ===== //
	// Transform�R���|�[�l���g�H
	if (strcmp(componentType, "Transform") == 0)
	{
		// Transform�ɒu��
		Transform* destTransform = (Transform*)destComponent;
		Transform* sourceTransform = (Transform*)sourceComponent;
		// �l���
		*destTransform = Transform(sourceTransform);
	}
	// Text�R���|�[�l���g�H
	else if (strcmp(componentType, "Text") == 0)
	{
		// Text�ɒu��
		Text* destText = (Text*)destComponent;
		Text* sourceText = (Text*)sourceComponent;
		// �l���
		*destText = Text(sourceText);
	}
}

void Ctlan::PrivateSystem::SystemManager::SystemComponentManager::SendMessageBasedOnType(Component* lateComponent, Component* nowComponent)
{
	// �R���|�[�l���g�̃^�C�v�擾
	char baseComponentType[50] = {};
	char componentType[30] = "Component";
	strcpy_s(baseComponentType, typeid(*lateComponent).name());
	char* context{};
	char* token = strtok_s(baseComponentType, " ::", &context);
	while (token)
	{
		strcpy_s(componentType, token);
		token = strtok_s(NULL, " ::", &context);
	}

	// ���b�Z�[�W�f�[�^
	MessageData messageData;

	// ===== �R���|�[�l���g�̃^�C�v���珈���𕪊� ===== //
	// Transform�R���|�[�l���g�H
	if (strcmp(componentType, "Transform") == 0)
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
			messageData.message.bodyObject.object.CopyName(nowTransform.gameObject->GetName());
			// �R���|�[�l���g�^�C�v
			strcpy_s(messageData.message.bodyObject.componentType,
				sizeof(messageData.message.bodyObject.componentType),
				componentType);
			// �R���|�[�l���g���
			messageData.message.bodyObject.transform = nowTransform;
			
			// ���b�Z�[�W�𑗂鏈�������s
			SystemNetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
	// Text�R���|�[�l���g�H
	else if (strcmp(componentType, "Text") == 0)
	{
		// Text�R���|�[�l���g�ɒu��
		Text nowText = *(Text*)nowComponent;
		Text lateText = *(Text*)lateComponent;

		// �l���X�V����Ă���H
		if (nowText.text && lateText.text && nowText.dummyText && lateText.dummyText &&
			strcmp(nowText.text, lateText.text) != 0 ||
			nowText.fontSize != lateText.fontSize ||
			nowText.leftTopPoint != lateText.leftTopPoint)
		{
			// ----- ���M����l���� ----- //
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::UpdateComponent;
			// �I�u�W�F�N�g
			messageData.message.bodyObject.object.CopyName(nowText.gameObject->GetName());
			// �R���|�[�l���g�^�C�v
			strcpy_s(messageData.message.bodyObject.componentType,
				sizeof(messageData.message.bodyObject.componentType),
				componentType);
			// �R���|�[�l���g���
			messageData.message.bodyObject.text = Text(nowText);

			// ���b�Z�[�W�𑗂鏈�������s
			SystemNetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
}
