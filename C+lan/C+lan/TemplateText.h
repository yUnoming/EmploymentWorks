#pragma once
/**
* @file		TemplateText.h
* @brief	TemplateTextクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.01.18
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Text.h"
#include "Shader.h"


namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	作成タブで作成できるテキスト	</summary>
		class TemplateText : public PrivateSystem::GameObject
		{
			public:
				/// <summary>
				///	コンストラクタ	</summary>
				TemplateText() : GameObject()
				{
					GetComponent<Ctlan::PublicSystem::Shader>()->Load("Assets\\Shaders\\unlitTextureVS.cso", "Assets\\Shaders\\unlitTexturePS.cso");
					AddComponent<Material>();
					Text* textComponent = AddComponent<Text>();
					textComponent->text = "Input text";
					textComponent->fontSize = Vector2(20, 30);

					transform->position.x = 0.0f;
					transform->position.z = 3.0f;
				};
				/// <summary>
				///	引数付きコンストラクタ	</summary>
				/// <param name="nowScene">
				///	オブジェクトが生成されたシーン	</param>
				TemplateText(SceneBase* nowScene) : GameObject(nowScene)
				{
					GetComponent<Ctlan::PublicSystem::Shader>()->Load("Assets\\Shaders\\unlitTextureVS.cso", "Assets\\Shaders\\unlitTexturePS.cso");
					AddComponent<Material>();
					Text* textComponent = AddComponent<Text>();
					textComponent->text = "Input text...";
					textComponent->fontSize = Vector2(20, 30);

					transform->position.x = 0.0f;
					transform->position.z = 3.0f;
				};
		};
	}
}

