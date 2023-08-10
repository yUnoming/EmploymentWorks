#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Component.h"
#include "Vector3.h"
#include <SimpleMath.h>


namespace PublicSystem
{
	class Camera : public Component
	{
		private:
			// ----- variables / 変数 ----- //
			// ビュー行列
			DirectX::SimpleMath::Matrix m_ViewMatrix{};

		public:
			// ----- functions / 関数 ----- //
			void Init()   override;	// 初期化
			void UnInit() override; // 終了
			void Update() override;	// 更新
			void Draw()   override;	// 描画
	};
}

