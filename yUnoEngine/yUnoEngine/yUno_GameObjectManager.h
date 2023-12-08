#pragma once
/**
* @file		yUno_GameObjectManager.h
* @brief	yUno_GameObjectManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.12.08
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <list>
#include <vector>
#include "GameObject.h"

namespace yUno_SystemManager
{
	/// <summary>
/// ゲームオブジェクトに関する機能をまとめたクラス	</summary>
	class yUno_GameObjectManager
	{
	private:
		// ----- structs / 構造体 ----- //
		/// <summary>
		/// オブジェクト名情報	</summary>
		struct ObjectNameData
		{
			/// <summary>
			///	自身のオブジェクト名	</summary>
			char myName[30];
			/// <summary>
			///	元のオブジェクト名	</summary>
			char baseName[30];
			/// <summary>
			///	オブジェクト名に付与する番号（名称被り防止）	</summary>
			int objectNameNumber;
		};
		/// <summary>
		/// オブジェクト番号情報	</summary>
		struct ObjectNumberData
		{
			/// <summary>
			///	オブジェクト名	</summary>
			const char* name;
			/// <summary>
			///	空き番号	</summary>
			std::vector<int> emptyNumber;
			/// <summary>
			///	番号の最大値	</summary>
			int maxNumber;
		};

		// ----- variables / 変数 ----- //
		/// <summary>
		///	オブジェクト名リスト	</summary>
		static std::list<ObjectNameData>m_objectNameList;
		/// <summary>
		///	オブジェクト番号リスト	</summary>
		static std::list<ObjectNumberData>m_objectNumberList;

	public:
		// ----- functions / 関数 ----- //
		static void UnInit();

		/// <summary>
		///	オブジェクト名が既に存在するかどうか確認	</summary>
		/// <param name="name">
		/// 確認するオブジェクト名	</param>
		/// <returns>
		///	実際に付けるオブジェクト名	</returns>
		static const char* CheckObjectName(const char* name);
		/// <summary>
		///	オブジェクト名に付与する番号を取得	</summary>
		/// <param name="name">
		///	取得するオブジェクト名	</param>
		/// <returns>
		/// 付与する番号	</returns>
		static int GetObjectNumber(const char* name);
		/// <summary>
		///	オブジェクト名に付与する番号を設定	</summary>
		/// <param name="name">
		/// 設定するオブジェクト名	</param>
		static void SetObjectNumber(const char* name);
	};
}

