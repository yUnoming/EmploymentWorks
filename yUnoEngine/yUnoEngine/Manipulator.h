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
#include "SceneManager.h"


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
				Manipulator() {
					AddComponent<ModelRenderer>()->Load("Assets/Models\\test2.obj");
					spectatorCamera = yUno_SceneManager::GetEditScene()->GetSceneObject<SpectatorCamera>("SpectatorCamera");
					isActive = false;
				};

				void Update() override
				{
					// 自身がクリックされている？
					if (spectatorCamera->GetClickedManipulator() == this)
					{
						nowCursorPos = PublicSystem::MouseInput::GetCursorPosition();

						if (isClicked)
						{
							ClickAction();
						}

						isClicked = true;
						lateCursorPos = nowCursorPos;
					}
					else if (isClicked)
					{
						isClicked = false;
					}
				};
				/// <summary>
				///	クリックされた際のアクション	</summary>
				virtual void ClickAction() {};
		};
	}
}

