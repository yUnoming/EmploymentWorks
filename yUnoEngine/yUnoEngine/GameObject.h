#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <list>
#include <SimpleMath.h>
#include "Component.h"
#include "Vector3.h"


namespace PublicSystem
{
	class GameObject
	{
	private:
		// ----- variables ----- //
		// コンポーネントのリスト
		std::list<Component*> m_ComponentList;

	protected:
		// ----- variables ----- //
		// オブジェクトのアクティブ状態を表す
		// true: 通常動作 false: 機能停止・非表示
		bool m_Active = true;

		Vector3 m_Position = Vector3(0.0f, 0.0f, 0.0f);	// 位置
		Vector3 m_Rotation = Vector3(0.0f, 0.0f, 0.0f);	// 回転
		Vector3 m_Scale = Vector3(1.0f, 1.0f, 1.0f);	// 大きさ

	public:
		// ----- methods ----- //
		GameObject() {};
		virtual ~GameObject() {};

		// オブジェクト単体に関わる処理
		virtual void Init() {};		// 初期化
		virtual void UnInit() {};	// 終了
		virtual void Update() {};	// 更新
		virtual void Draw() {};		// 描画

		// オブジェクト全体に関わる処理
		void InitBase();
		void UnInitBase();
		void UpdateBase();
		void DrawBase(DirectX::SimpleMath::Matrix _parentMatrix);

		// コンポーネント取得
		template<class T>
		T* GetComponent();
		// コンポーネント追加
		template<class T>
		T* AddComponent();
		// コンポーネント削除
		template<class T>
		T* DeleteComponent();
	};
}