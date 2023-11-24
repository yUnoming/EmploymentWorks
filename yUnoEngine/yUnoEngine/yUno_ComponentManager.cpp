#include "yUno_ComponentManager.h"
#include "yUno_NetWorkManager.h"
#include "Transform.h"


void yUno_SystemManager::yUno_ComponentManager::SetVariableValue(Component* destComponent, Component* sourceComponent)
{
	// コンポーネントのタイプ取得
	const char* componentType = typeid(*destComponent).name();
	// 送るメッセージを代入する配列
	char sendMessage[256];
	ZeroMemory(sendMessage, sizeof(sendMessage));

	// ===== コンポーネントのタイプから処理を分岐 ===== //
	// Transformコンポーネント？
	if (strcmp(componentType, "class PublicSystem::Transform") == 0)
	{
		// Transformコンポーネントに置換
		Transform* destTransform = (Transform*)destComponent;
		Transform* sourceTransform = (Transform*)sourceComponent;

		// 各値を代入
		destTransform->Position = sourceTransform->Position;
		destTransform->Rotation = destTransform->Rotation;
		destTransform->Scale = destTransform->Scale;
	}
}

void yUno_SystemManager::yUno_ComponentManager::SendMessageBasedOnType(Component* lateComponent, Component* nowComponent)
{
	// コンポーネントのタイプ取得（typeidで取得すると"class"という文字列が含まれるので削除する処理も実行）
	char tmpComponentType[50];
	ZeroMemory(tmpComponentType, sizeof(tmpComponentType));
	char* componentType = const_cast<char*>(typeid(*nowComponent).name());
	memcpy(tmpComponentType, componentType, strlen(componentType));
	char* context;
	char* token = strtok_s(tmpComponentType, " ", &context);
	componentType = strtok_s(NULL, " ", &context);
	
	// 送るメッセージを代入する配列
	char sendMessage[256];
	ZeroMemory(sendMessage, sizeof(sendMessage));
	
	// ===== コンポーネントのタイプから処理を分岐 ===== //
	// Transformコンポーネント？
	if (strcmp(componentType, "PublicSystem::Transform") == 0)
	{
		// Transformコンポーネントに置換
		Transform nowTransform = *(Transform*)nowComponent;
		Transform lateTransform = *(Transform*)lateComponent;

		if (strcmp(nowTransform.gameObject->GetName(), "SpectatorCamera") == 0)
		{
			return;
		}

		// ----- 更新された値を特定 ----- //
		// Position（位置）が更新された？
		if (nowTransform.Position != lateTransform.Position)
		{
			// 送りたい情報を文字列に置換
			sprintf_s(sendMessage, "%d %s %s %s %f %f %f",
				yUno_SystemManager::yUno_NetWorkManager::MessageType::UpdateComponentValue,	// 送信するメッセージのタイプ
				nowTransform.gameObject->GetName(),											// オブジェクト名
				componentType,																// コンポーネントのタイプ
				"Position",																	// 変数名
				nowTransform.Position.x, nowTransform.Position.y, nowTransform.Position.z);	// 値
			// メッセージを送る処理を実行
			yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
		// Position（回転）が更新された？
		else if (nowTransform.Rotation != lateTransform.Rotation)
		{
			sprintf_s(sendMessage, "%s %s %s %f %f %f",
				nowTransform.gameObject->GetName(),
				componentType,
				"Rotation",
				nowTransform.Rotation.x, nowTransform.Rotation.y, nowTransform.Rotation.z);
			yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
		// Scale（大きさ）が更新された？
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
