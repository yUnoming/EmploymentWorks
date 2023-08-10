#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <list>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		  前方参照  		  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
class GameObject;


class Component
{
	public:
		// ----- variables / 変数 ----- //
		// 自身の親であるオブジェクト
		GameObject* Parent = nullptr;

		// よく使われるコンポーネントは呼び出さるようにしておく


		// ----- functions / 関数 ----- //
		// コンストラクタ
		Component() {};
		// デストラクタ
		virtual ~Component() {};

		// 初期化
		virtual void Init() {};
		// 終了
		virtual void UnInit() {};
		// 更新
		virtual void Update() {};
		// 描画
		virtual void Draw() {};
};

