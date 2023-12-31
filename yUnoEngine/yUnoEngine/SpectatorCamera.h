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


/// <summary>
///	エンジン内で使うカメラオブジェクト	</summary>
class SpectatorCamera : public GameObject
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

};

