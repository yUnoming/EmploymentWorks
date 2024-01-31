#pragma once
/**
* @file		SpectatorCamera.h
* @brief	SpectatorCameraクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"
#include "SceneBase.h"

namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	エンジン内で使うカメラオブジェクト	</summary>
		class SpectatorCamera : public Ctlan::PrivateSystem::GameObject
		{
		private:
			// ----- variables / 変数 ----- //
			///<summary>
			///クリックされたオブジェクト	</summary>
			GameObject* m_clickedObject = nullptr;
			/// <summary>
			///	クリックされたマニピュレーター	</summary>
			GameObject* m_clickedManipulator = nullptr;

		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			///	コンストラクタ	</summary>
			SpectatorCamera() : GameObject() {};
			/// <summary>
			///	引数付きコンストラクタ	</summary>
			/// <param name="nowScene">
			///	オブジェクトが生成されたシーン	</param>
			SpectatorCamera(SceneBase* nowScene) : GameObject(nowScene) {};

			/// <summary>
			///	初期化	</summary>
			void Init();
			/// <summary>
			///	更新	</summary>
			void Update();

			/// <summary>
			///	クリックされているオブジェクトを返す	</summary>
			/// <returns>
			///	オブジェクトがあればオブジェクト情報、なければnullptrを返す	</returns>
			GameObject* GetClickedObject() const;
			/// <summary>
			///	クリックされたマニピュレーターオブジェクトを返す	</summary>
			/// <returns>
			///	オブジェクトがあればオブジェクト情報、なければnullptrを返す	</returns>
			GameObject* GetClickedManipulator() const;
			/// <summary>
			///	クリック状態を解除	</summary>
			void ReleaseClickedObject() { m_clickedObject = nullptr;};
		};
	}
}

