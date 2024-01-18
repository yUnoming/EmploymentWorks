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
class GameObject;


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
		virtual void UnInit() {};
		/// <summary>
		/// 更新		</summary>
		virtual void Update() {};
		/// <summary>
		/// 描画		</summary>
		virtual void Draw() {};
		/// <summary>
		/// 衝突判定時	</summary>
		virtual void HitCollision(GameObject* other) {};

		/// <summary>
		///	Component型との代入オペレーター	</summary>
		/// <param name="other">
		///	Component型のオブジェクト	</param>
		/// <returns>
		///	代入後のComponent情報	</returns>
		Component& operator=(const Component& other);
};

