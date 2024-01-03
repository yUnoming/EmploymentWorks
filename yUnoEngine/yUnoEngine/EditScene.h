#pragma once
/**
* @file		EditScene.h
* @brief	EditSceneクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.12.25
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SceneBase.h"

#include "SpectatorCamera.h"
#include "Manipulator_MoveX.h"


namespace yUnoEngine
{
	/// <summary>
	///	エディットシーン	</summary>
	class EditScene : public SceneBase
	{
		private:
			/// <summary>
			///	エディット時に使用するカメラ	</summary>
			SpectatorCamera* m_spectatorCamera;
			/// <summary>
			///	X方向への移動マニピュレーター	</summary>
			Manipulator::Manipulator_MoveX* m_manipulator_MoveX;

		public:
			// ----- functions / 関数 ----- //
			void Init()
			{
				// ===== エディット用カメラの生成 ===== //
				m_spectatorCamera = AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
				
				// ===== マニピュレーター用オブジェクトの生成 ===== //
				// ----- 移動系 ----- //
				m_manipulator_MoveX = AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveY");
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveZ");
			}

			void Update()
			{
				// オブジェクトをクリックした？
				if (m_spectatorCamera->GetClickedObject() != nullptr)
				{
					// ===== マニピュレーターの表示処理 ===== //
					m_manipulator_MoveX->isActive = true;
					m_manipulator_MoveX->transform->parent = m_spectatorCamera->GetClickedObject();
				}
				else
				{
					// ===== マニピュレーターの非表示処理 ===== //
					m_manipulator_MoveX->isActive = false;
					m_manipulator_MoveX->transform->parent = nullptr;
				}

				SceneBase::Update();
			}
	};
};

