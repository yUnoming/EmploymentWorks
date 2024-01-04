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

#include "yUno_SceneManager.h"


/// <summary>
///	エンジン群	</summary>
namespace yUnoEngine
{
	/// <summary>
	///	マニピュレーター群	</summary>
	namespace Manipulator
	{
		class Manipulator :	public GameObject
		{
			protected:
				/// <summary>
				///	エディットカメラ	</summary>
				SpectatorCamera* spectatorCamera;
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
				Manipulator()
				{
					// モデル追加
					AddComponent<ModelRenderer>()->Load("Assets\\Models\\MoveManipulator.obj");
					// エディットカメラ取得
					spectatorCamera = yUno_SceneManager::GetEditScene()->GetSceneObject<SpectatorCamera>("SpectatorCamera");
					// 非表示にしておく
					isActive = false;
				};



				void Update() override
				{
					// 自身がクリックされている？
					if (spectatorCamera->GetClickedManipulator() == this)
					{
						// 現在のカーソル位置を取得
						nowCursorPos = PublicSystem::MouseInput::GetCursorPosition();
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

