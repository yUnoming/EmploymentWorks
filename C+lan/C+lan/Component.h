#pragma once
/**
* @file		Component.h
* @brief	Componentクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		  前方参照  	 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
namespace Ctlan
{
	namespace PrivateSystem
	{
		class GameObject;
	}
}


namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		/// コンポーネントクラス	</summary>
		class Component
		{
			public:
				// ----- variables / 変数 ----- //
				/// <summary>
				/// このコンポーネントが追加されているオブジェクト	</summary>
				GameObject* gameObject = nullptr;

				// ----- functions / 関数 ----- //
				/// <summary>
				/// コンストラクタ		</summary>
				Component() {};
				/// <summary>
				/// デストラクタ		</summary>
				virtual ~Component() {};

				/// <summary>
				/// 初期化		</summary>
				virtual void Init() {};
				/// <summary>
				/// 終了		</summary>
				virtual void Uninit() {};
				/// <summary>
				/// 更新		</summary>
				virtual void Update() {};
				/// <summary>
				/// 描画		</summary>
				virtual void Draw() {};
				/// <summary>
				/// 衝突判定時	</summary>
				virtual void HitCollision(GameObject* other) {};
		};
	}
}