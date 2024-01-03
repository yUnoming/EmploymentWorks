#pragma once
/**
* @file		EachFunction.h
* @brief	EachFunctionクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Component.h"
#include "GameObject.h"

/// <summary>
/// コンポーネントで使いたいものをまとめたクラス	</summary>
class EachFunction : public Component
{
	public:
		// ----- variables / 変数 ----- //
		//! 自身の親であるオブジェクト
		GameObject* parent = nullptr;

		//! トランスフォーム
		class Transform* transform = nullptr;

		// ----- functions / 関数 ----- //
		using Component::Component;
		/// <summary>
		/// コンストラクタ		</summary>
		EachFunction() {};
		
		//**  コンポーネント操作  **//
		/// <summary>
		/// コンポーネントを取得 </summary>
		/// <param name="GetComponent&lt;&gt;();">
		/// &lt;&gt;内に取得したいコンポーネントを記述		</param>
		/// <returns>
		/// 取得したコンポーネント </returns>
		template<class T>
		T* GetComponent()
		{
			return gameObject->GetComponent<T>();
		}
		/// <summary>
		/// コンポーネントを追加
		/// </summary>
		/// <param name="AddComponent&lt;&gt;();">
		/// &lt;&gt;内に追加したいコンポーネントを記述		</param>
		/// <returns>
		/// 追加したコンポーネント		</returns>
		template<class T>
		T* AddComponent()
		{
			return gameObject->AddComponent<T>();
		}
		/// <summary>
		/// コンポーネントを削除
		/// </summary>
		/// <param name="DeleteComponent&lt;&gt;();">
		/// &lt;&gt;内に削除したいコンポーネントを記述		</param>
		template<class T>
		void DeleteComponent()
		{
			gameObject->DeleteComponent<T>();
		}
};