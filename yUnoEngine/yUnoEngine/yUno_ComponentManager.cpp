#include "yUno_NetWorkManager.h"
#include "yUno_ComponentManager.h"
#include "Transform.h"


void yUno_SystemManager::yUno_ComponentManager::SetVariableValue(Component* destComponent, Component* sourceComponent)
{
	// コンポーネントのタイプ取得
	const char* componentType = typeid(*destComponent).name();
	// メッセージデータ
	MessageData messageData;

	// ===== コンポーネントのタイプから処理を分岐 ===== //
	// Transformコンポーネント？
	if (strcmp(componentType, "class PublicSystem::Transform") == 0)
	{
		// Transformに置換
		Transform* destTransform = (Transform*)destComponent;
		Transform* sourceTransform = (Transform*)sourceComponent;
		// 値代入
		*destTransform = Transform(sourceTransform);
	}
	// Textコンポーネント？
	else if (strcmp(componentType, "class PublicSystem::Text") == 0)
	{
		// Textに置換
		Text* destText = (Text*)destComponent;
		Text* sourceText = (Text*)sourceComponent;
		// 値代入
		*destText = Text(sourceText);
	}
}

void yUno_SystemManager::yUno_ComponentManager::SendMessageBasedOnType(Component* lateComponent, Component* nowComponent)
{
	// コンポーネントのタイプ取得
	const char* componentType = typeid(*lateComponent).name();
	// メッセージデータ
	MessageData messageData;

	// ===== コンポーネントのタイプから処理を分岐 ===== //
	// Transformコンポーネント？
	if (strcmp(componentType, "class PublicSystem::Transform") == 0)
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
			messageData.message.body.object.CopyName(nowTransform.gameObject->GetName());
			// コンポーネントタイプ
			strcpy_s(messageData.message.body.componentType,
				sizeof(messageData.message.body.componentType),
				componentType);
			// コンポーネント情報
			messageData.message.body.transform = nowTransform;
			
			// メッセージを送る処理を実行
			yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
	// Textコンポーネント？
	else if (strcmp(componentType, "class PublicSystem::Text") == 0)
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
			messageData.message.body.object.CopyName(nowText.gameObject->GetName());
			// コンポーネントタイプ
			strcpy_s(messageData.message.body.componentType,
				sizeof(messageData.message.body.componentType),
				componentType);
			// コンポーネント情報
			messageData.message.body.text = nowText;

			// メッセージを送る処理を実行
			yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
}
