#pragma once
class Component
{
	public:

		// ----- functions / 関数 ----- //
		Component() {};				// コンストラクタ
		virtual ~Component() {};	// デストラクタ

		virtual void Init() {};			// 初期化
		virtual void UnInit() {};		// 終了
		virtual void Update() {};		// 更新
		virtual void Draw() {};			// 描画
		virtual void HitCollision() {};	// 当たり判定が当たった場合
};

