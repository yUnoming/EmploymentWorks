#include "SystemNetWorkManager.h"
#include "SystemComponentManager.h"
#include "Transform.h"


void Ctlan::PrivateSystem::SystemManager::SystemComponentManager::SetVariableValue(Component* destComponent, Component* sourceComponent)
{
	// コンポーネントのタイプ取得
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

	// メッセージデータ
	MessageData messageData;

	// ===== コンポーネントのタイプから処理を分岐 ===== //
	// Transformコンポーネント？
	if (strcmp(componentType, "Transform") == 0)
	{
		// Transformに置換
		Transform* destTransform = (Transform*)destComponent;
		Transform* sourceTransform = (Transform*)sourceComponent;
		// 値代入
		*destTransform = Transform(sourceTransform);
	}
	// Textコンポーネント？
	else if (strcmp(componentType, "Text") == 0)
	{
		// Textに置換
		Text* destText = (Text*)destComponent;
		Text* sourceText = (Text*)sourceComponent;
		// 値代入
		*destText = Text(sourceText);
	}
}

void Ctlan::PrivateSystem::SystemManager::SystemComponentManager::SendMessageBasedOnType(Component* lateComponent, Component* nowComponent)
{
	// コンポーネントのタイプ取得
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

	// メッセージデータ
	MessageData messageData;

	// ===== コンポーネントのタイプから処理を分岐 ===== //
	// Transformコンポーネント？
	if (strcmp(componentType, "Transform") == 0)
	{
		// Transformコンポーネントに置換
		Transform nowTransform = *(Transform*)nowComponent;
		Transform lateTransform = *(Transform*)lateComponent;

		// 値が更新されている？
		if (nowTransform.position != lateTransform.position ||
			nowTransform.rotation != lateTransform.rotation ||
			nowTransform.scale != lateTransform.scale)
		{
			// ----- 送信する値を代入 ----- //
			// メッセージタイプ
			messageData.message.header.type = MessageType::UpdateComponent;
			// オブジェクト
			messageData.message.bodyObject.object.CopyName(nowTransform.gameObject->GetName());
			// コンポーネントタイプ
			strcpy_s(messageData.message.bodyObject.componentType,
				sizeof(messageData.message.bodyObject.componentType),
				componentType);
			// コンポーネント情報
			messageData.message.bodyObject.transform = nowTransform;
			
			// メッセージを送る処理を実行
			SystemNetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
	// Textコンポーネント？
	else if (strcmp(componentType, "Text") == 0)
	{
		// Textコンポーネントに置換
		Text nowText = *(Text*)nowComponent;
		Text lateText = *(Text*)lateComponent;

		// 値が更新されている？
		if (nowText.text && lateText.text && nowText.dummyText && lateText.dummyText &&
			strcmp(nowText.text, lateText.text) != 0 ||
			nowText.fontSize != lateText.fontSize ||
			nowText.leftTopPoint != lateText.leftTopPoint)
		{
			// ----- 送信する値を代入 ----- //
			// メッセージタイプ
			messageData.message.header.type = MessageType::UpdateComponent;
			// オブジェクト
			messageData.message.bodyObject.object.CopyName(nowText.gameObject->GetName());
			// コンポーネントタイプ
			strcpy_s(messageData.message.bodyObject.componentType,
				sizeof(messageData.message.bodyObject.componentType),
				componentType);
			// コンポーネント情報
			messageData.message.bodyObject.text = Text(nowText);

			// メッセージを送る処理を実行
			SystemNetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
}
