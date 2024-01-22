#pragma once
/**
* @file		Manipulator.h
* @brief	Manipulatorクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.12.31
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"
#include "modelRenderer.h"
#include "Material.h"
#include "Transform.h"

#include "MouseInput.h"
#include "SpectatorCamera.h"

#include "SystemSceneManager.h"


/// <summary>
///	エンジン群	</summary>
namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	マニピュレーター群	</summary>
		namespace Manipulator
		{
			/// <summary>
			///	マニピュレーターの親オブジェクト	</summary>
			class Manipulator : public Ctlan::PrivateSystem::GameObject
			{
				protected:
					/// <summary>
					///	エディットカメラ	</summary>
					EngineObject::SpectatorCamera* spectatorCamera;
					/// <summary>
					///	現在のカーソル位置	</summary>
					Vector2 nowCursorPos;
					/// <summary>
					///	前回のカーソル位置	</summary>
					Vector2 lateCursorPos;
					/// <summary>
					///	クリックされたかどうか	</summary>
					bool isClicked = false;

				public:
					/// <summary>
					///	コンストラクタ	</summary>
					Manipulator() : GameObject()
					{
						// モデル追加
						AddComponent<Ctlan::PrivateSystem::ModelRenderer>()->Load("Assets\\Models\\MoveManipulator.obj");
						// エディットカメラ取得
						spectatorCamera = Ctlan::PrivateSystem::SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject<EngineObject::SpectatorCamera>("SpectatorCamera");
						// サイズ調整
						transform->scale *= 0.7f;
						// 非表示にしておく
						isActive = false;
					};
					/// <summary>
					///	引数付きコンストラクタ	</summary>
					/// <param name="nowScene">
					///	オブジェクトが生成されたシーン	</param>
					Manipulator(SceneBase* nowScene) : GameObject(nowScene)
					{
						// モデル追加
						AddComponent<Ctlan::PrivateSystem::ModelRenderer>()->Load("Assets\\Models\\MoveManipulator.obj");
						// エディットカメラ取得
						spectatorCamera = Ctlan::PrivateSystem::SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject<EngineObject::SpectatorCamera>("SpectatorCamera");
						// サイズ調整
						transform->scale *= 0.7f;
						// 非表示にしておく
						isActive = false;
					};


					void Update() override
					{
						// 自身がクリックされている？
						if (spectatorCamera->GetClickedManipulator() == this)
						{
							// 現在のカーソル位置を取得
							nowCursorPos = Ctlan::PublicSystem::MouseInput::GetCursorPosition();
							// クリックされている？
							if (isClicked)
							{
								ClickAction();	// クリックされた際の処理を実行
							}

							isClicked = true;				// クリックされている状態に切り替え
							lateCursorPos = nowCursorPos;	// 現在のカーソル位置を保存
						}
						// 前回までクリックされていた？
						else if (isClicked)
						{
							isClicked = false;	// クリックされていない状態に切り替え
						}
					};
					/// <summary>
					///	クリックされた際のアクション	</summary>
					virtual void ClickAction() {};
			};
		}
	}
}

