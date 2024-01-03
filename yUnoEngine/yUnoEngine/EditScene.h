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
#include "Manipulator_MoveY.h"
#include "Manipulator_MoveZ.h"


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
			/// <summary>
			///	Y方向への移動マニピュレーター	</summary>
			Manipulator::Manipulator_MoveY* m_manipulator_MoveY;
			/// <summary>
			///	Z方向への移動マニピュレーター	</summary>
			Manipulator::Manipulator_MoveZ* m_manipulator_MoveZ;

		public:
			// ----- functions / 関数 ----- //
			void Init()
			{
				// ===== エディット用カメラの生成 ===== //
				m_spectatorCamera = AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
				
				// ===== マニピュレーター用オブジェクトの生成 ===== //
				// ----- 移動 ----- //
				m_manipulator_MoveX = AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");
				m_manipulator_MoveY = AddSceneObject<Manipulator::Manipulator_MoveY>(1, "Manipulator_MoveY");
				m_manipulator_MoveZ = AddSceneObject<Manipulator::Manipulator_MoveZ>(1, "Manipulator_MoveZ");
			}

			void Update()
			{
				// オブジェクトをクリックした？
				if (m_spectatorCamera->GetClickedObject() != nullptr)
				{
					// ===== マニピュレーターの表示処理 ===== //
					// ----- 移動 ----- //
					// X軸方向
					m_manipulator_MoveX->isActive = true;
					m_manipulator_MoveX->transform->parent = m_spectatorCamera->GetClickedObject();
					// Y軸方向
					m_manipulator_MoveY->isActive = true;
					m_manipulator_MoveY->transform->parent = m_spectatorCamera->GetClickedObject();
					// Z軸方向
					m_manipulator_MoveZ->isActive = true;
					m_manipulator_MoveZ->transform->parent = m_spectatorCamera->GetClickedObject();
				}
				else
				{
					// ===== マニピュレーターの非表示処理 ===== //
					// ----- 移動 ----- //
					// X軸方向
					m_manipulator_MoveX->isActive = false;
					m_manipulator_MoveX->transform->parent = nullptr;
					// Y軸方向
					m_manipulator_MoveY->isActive = false;
					m_manipulator_MoveY->transform->parent = nullptr;
					// Z軸方向
					m_manipulator_MoveZ->isActive = false;
					m_manipulator_MoveZ->transform->parent = nullptr;
				}

				// シーンの基本的な更新処理を実行
				SceneBase::Update();
			}
	};
};

