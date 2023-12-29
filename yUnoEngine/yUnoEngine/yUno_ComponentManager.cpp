#include "yUno_NetWorkManager.h"
#include "yUno_ComponentManager.h"
#include "Transform.h"


void yUno_SystemManager::yUno_ComponentManager::SetVariableValue(Component* destComponent, Component* sourceComponent)
{
	// コンポーネントのタイプ取得
	const char* componentType = typeid(*destComponent).name();

	// ===== コンポーネントのタイプから処理を分岐 ===== //
	// Transformコンポーネント？
	if (strcmp(componentType, "class PublicSystem::Transform") == 0)
	{
		// Transformコンポーネントに置換
		Transform* destTransform = (Transform*)destComponent;
		Transform* sourceTransform = (Transform*)sourceComponent;

		// 各値を代入
		destTransform->position = sourceTransform->position;
		destTransform->rotation = destTransform->rotation;
		destTransform->scale = destTransform->scale;
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
}
