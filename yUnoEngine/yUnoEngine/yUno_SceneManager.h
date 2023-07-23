#pragma once
#include <list>
#include <array>
#include "GameObject.h"

class yUno_SceneManager
{
	protected:
		// シーン内のオブジェクト
		std::array<std::list<GameObject*>, 4> m_SceneObject;

	public:
		// ----- methods ----- //
		yUno_SceneManager() {};
		virtual ~yUno_SceneManager() {};

		// シーン単体に関わる処理
		virtual void Init() {};		// 初期化
		virtual void UnInit() {};	// 終了
		virtual void Update() {};	// 更新
		virtual void Draw() {};		// 描画

		// シーン全般に関わる処理
		void InitBase();	// 初期化
		void UnInitBase();	// 終了
		void UpdateBase();	// 更新
		void DrawBase();	// 描画
};

