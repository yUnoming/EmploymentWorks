#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Component.h"
#include "GameObject.h"

class EachFunction : public Component
{
	public:
		// ----- variables / 変数 ----- //
		// 自分自身を表すオブジェクト
		GameObject* Myself = nullptr;

		// 自身の親であるオブジェクト
		GameObject* Parent = nullptr;

		// 基本のオブジェクト情報
		class Transform* transform = nullptr;

		// ----- functions / 関数 ----- //
		using Component::Component;
		EachFunction() {};
		//**  コンポーネント操作  **//

		template<class T>
		T* GetComponent()
		{
			return Myself->GetComponent<T>();
		}

		template<class T>
		T* AddComponent()
		{
			return Myself->AddComponent<T>();
		}

		template<class T>
		void DeleteComponent()
		{
			Myself->DeleteComponent<T>();
		}
};