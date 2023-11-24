#include "yUno_ComponentManager.h"
#include "yUno_NetWorkManager.h"
#include "Transform.h"


void yUno_SystemManager::yUno_ComponentManager::SetVariableValue(Component* destComponent, Component* sourceComponent)
{
	// �R���|�[�l���g�̃^�C�v�擾
	const char* componentType = typeid(*destComponent).name();
	// ���郁�b�Z�[�W��������z��
	char sendMessage[256];
	ZeroMemory(sendMessage, sizeof(sendMessage));

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
	// �R���|�[�l���g�̃^�C�v�擾�itypeid�Ŏ擾�����"class"�Ƃ��������񂪊܂܂��̂ō폜���鏈�������s�j
	char tmpComponentType[50];
	ZeroMemory(tmpComponentType, sizeof(tmpComponentType));
	char* componentType = const_cast<char*>(typeid(*nowComponent).name());
	memcpy(tmpComponentType, componentType, strlen(componentType));
	char* context;
	char* token = strtok_s(tmpComponentType, " ", &context);
	componentType = strtok_s(NULL, " ", &context);
	
	// ���郁�b�Z�[�W��������z��
	char sendMessage[256];
	ZeroMemory(sendMessage, sizeof(sendMessage));
	
	// ===== �R���|�[�l���g�̃^�C�v���珈���𕪊� ===== //
	// Transform�R���|�[�l���g�H
	if (strcmp(componentType, "PublicSystem::Transform") == 0)
	{
		// Transform�R���|�[�l���g�ɒu��
		Transform nowTransform = *(Transform*)nowComponent;
		Transform lateTransform = *(Transform*)lateComponent;

		if (strcmp(nowTransform.gameObject->GetName(), "SpectatorCamera") == 0)
		{
			return;
		}

		// ----- �X�V���ꂽ�l����� ----- //
		// Position�i�ʒu�j���X�V���ꂽ�H
		if (nowTransform.Position != lateTransform.Position)
		{
			// ���肽�����𕶎���ɒu��
			sprintf_s(sendMessage, "%d %s %s %s %f %f %f",
				yUno_SystemManager::yUno_NetWorkManager::MessageType::UpdateComponentValue,	// ���M���郁�b�Z�[�W�̃^�C�v
				nowTransform.gameObject->GetName(),											// �I�u�W�F�N�g��
				componentType,																// �R���|�[�l���g�̃^�C�v
				"Position",																	// �ϐ���
				nowTransform.Position.x, nowTransform.Position.y, nowTransform.Position.z);	// �l
			// ���b�Z�[�W�𑗂鏈�������s
			yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
		// Position�i��]�j���X�V���ꂽ�H
		else if (nowTransform.Rotation != lateTransform.Rotation)
		{
			sprintf_s(sendMessage, "%s %s %s %f %f %f",
				nowTransform.gameObject->GetName(),
				componentType,
				"Rotation",
				nowTransform.Rotation.x, nowTransform.Rotation.y, nowTransform.Rotation.z);
			yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
		// Scale�i�傫���j���X�V���ꂽ�H
		else if (nowTransform.Scale != lateTransform.Scale)
		{
			sprintf_s(sendMessage, "%s %s %s %f %f %f",
				nowTransform.gameObject->GetName(),
				componentType,
				"Scale",
				nowTransform.Scale.x, nowTransform.Scale.y, nowTransform.Scale.z);
			yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
	}
}
