#pragma once
/**
* @file		SystemGameObjectManager.h
* @brief	SystemGameObjectManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.12.08
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <list>
#include <vector>

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
				/// <summary>
				/// ゲームオブジェクトに関する機能をまとめたクラス	</summary>
				class SystemGameObjectManager
				{
				public:
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
						/// 識別用のオブジェクト番号	</summary>
						int number;
					};

					// ----- functions / 関数 ----- //
					static void Uninit();

					/// <summary>
					///	オブジェクト名が既に存在するかどうか確認	</summary>
					/// <param name="name">
					/// 確認するオブジェクト名	</param>
					/// <returns>
					///	実際に付けるオブジェクト名	</returns>
					static const char* CheckObjectName(const char* name);
					/// <summary>
					///	オブジェクト名情報を取得	</summary>
					/// <param name="name">
					///	取得するオブジェクト名	</param>
					/// <returns>
					/// オブジェクト名情報	</returns>
					static ObjectNameData GetObjectNameData(const char* name);
					/// <summary>
					///	オブジェクト名情報を設定	</summary>
					/// <param name="objNameData">
					/// 設定するオブジェクト名情報	</param>
					static void SetObjectNameData(ObjectNameData objNameData);
					/// <summary>
					/// オブジェクト名情報を削除	/// </summary>
					/// <param name="name">
					///	削除するオブジェクト名	</param>
					static void DeleteObjectNameData(const char* name);

				private:
					// ----- variables / 変数 ----- //
					/// <summary>
					///	オブジェクト名リスト	</summary>
					static std::list<ObjectNameData>m_objectNameList;
			};
		}
	}
}

