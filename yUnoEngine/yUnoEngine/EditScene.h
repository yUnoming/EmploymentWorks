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
		public:
			// ----- functions / 関数 ----- //
			void Init()
			{
				// ===== エディット用カメラの生成 ===== //
				AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
				
				// ===== マニピュレーター用オブジェクトの生成 ===== //
				// ----- 移動系 ----- //
				AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");	// X方向への移動
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveY");	// Y方向への移動
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveZ");	// Z方向への移動
			}
	};
};

