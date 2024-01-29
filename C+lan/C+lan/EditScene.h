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
#include "PositionXGizmo.h"
#include "PositionYGizmo.h"
#include "PositionZGizmo.h"

#include "Camera.h"


namespace Ctlan
{
	namespace EngineScene
	{
		/// <summary>
		///	エディットシーン	</summary>
		class EditScene : public Ctlan::PrivateSystem::SceneBase
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
				Ctlan::EngineObject::SpectatorCamera* m_spectatorCamera;
				/// <summary>
				///	X軸移動ギズモ	</summary>
				Ctlan::EngineObject::Gizmo::PositionXGizmo* m_positionXGizmo;
				/// <summary>
				///	Y軸移動ギズモ	</summary>
				Ctlan::EngineObject::Gizmo::PositionYGizmo* m_positionYGizmo;
				/// <summary>
				///	Z軸移動ギズモ	</summary>
				Ctlan::EngineObject::Gizmo::PositionZGizmo* m_positionZGizmo;

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
	}
};

