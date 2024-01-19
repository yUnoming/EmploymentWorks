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

#include "Camera.h"


namespace yUnoEngine
{
	/// <summary>
	///	エディットシーン	</summary>
	class EditScene : public SceneBase
	{
		private:
			// ----- structs / 構造体 ----- //
			/// <summary>
			///	シーン編集時に使うデータ	</summary>
			struct SceneEditorData
			{
				/// <summary>
				///	編集時に使用するカメラのコンポーネント情報	</summary>
				Transform transformComponent;	// トランスフォーム
				Camera cameraComponent;			// カメラ
			};
			
			// ----- variables / 変数 ----- //
			/// <summary>
			///	シーン編集に使用するデータ	</summary>
			SceneEditorData m_sceneEditorData;
			/// <summary>
			///	エディット時に使用するカメラ	</summary>
			EngineObject::SpectatorCamera* m_spectatorCamera;
			/// <summary>
			///	X方向への移動マニピュレーター	</summary>
			Manipulator::Manipulator_MoveX* m_manipulator_MoveX;
			/// <summary>
			///	Y方向への移動マニピュレーター	</summary>
			Manipulator::Manipulator_MoveY* m_manipulator_MoveY;
			/// <summary>
			///	Z方向への移動マニピュレーター	</summary>
			Manipulator::Manipulator_MoveZ* m_manipulator_MoveZ;

			// デモプレイ中かどうか
			bool isDemoPlay;

		public:
			// ----- functions / 関数 ----- //
			void Init() override;
			void Uninit() override;
			void Update() override;
			void Draw() override;

			/// <summary>
			///	デモプレイ中かどうかを取得	</summary>
			/// <returns>
			///	デモプレイ中ならtrue、それ以外はfalse	</returns>
			bool IsDemoPlay() { return isDemoPlay; };
	};
};

