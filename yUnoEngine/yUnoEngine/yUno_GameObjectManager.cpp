// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_GameObjectManager.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　	　static変数の定義　　 　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
std::list<yUno_SystemManager::yUno_GameObjectManager::ObjectNameData> yUno_SystemManager::yUno_GameObjectManager::m_objectNameList;
std::list<yUno_SystemManager::yUno_GameObjectManager::ObjectNumberData> yUno_SystemManager::yUno_GameObjectManager::m_objectNumberList;


void yUno_SystemManager::yUno_GameObjectManager::UnInit()
{
	// リストのクリア
	m_objectNameList.clear();
	m_objectNumberList.clear();
}

const char* yUno_SystemManager::yUno_GameObjectManager::CheckObjectName(const char* name)
{
	// 戻り値として扱う変数
	char returnName[50];

	// ===== オブジェクト名が被っていないか確認 ===== //
	// オブジェクト名データ取得
	for (auto& objNameData : m_objectNameList)
	{
		if (strcmp(objNameData.myName, name) == 0)
		{
			// 付与するオブジェクト番号取得
			int number = GetObjectNumber(objNameData.baseName);
			// オブジェクト名に番号を連結
			sprintf_s(returnName, "%s%d", objNameData.baseName, number);

			// ----- オブジェクト名データをリストに格納 ----- //
			// インスタンス生成
			ObjectNameData newObjNameData;
			strcpy_s(newObjNameData.baseName, objNameData.baseName);	// 番号を付与する前の名前
			strcpy_s(newObjNameData.myName, returnName);				// 現在の名前
			newObjNameData.objectNameNumber = number;					// オブジェクト番号
			// リストに格納
			m_objectNameList.push_back(newObjNameData);

			// オブジェクト名を戻り値として返す
			return returnName;
		}
	}
	///////////////////////////////////////////////
	// ここまで来たら、オブジェクト名は被っていない
	// =====　各データをリストに格納 ===== //
	// ----- オブジェクト番号 ----- //
	SetObjectNumber(name);
	// ----- オブジェクト名 ----- //
	// インスタンス生成
	ObjectNameData newObjNameData;
	strcpy_s(newObjNameData.baseName, name);	// 番号を付与する前の名前
	strcpy_s(newObjNameData.myName, name);		// 現在の名前
	newObjNameData.objectNameNumber = 0;		// オブジェクト番号
	// リストに格納
	m_objectNameList.push_back(newObjNameData);

	// オブジェクト名を戻り値として返す
	return name;
}

int yUno_SystemManager::yUno_GameObjectManager::GetObjectNumber(const char* name)
{
	// ===== オブジェクト番号取得 ===== //
	// オブジェクト番号データ取得
	for (auto& objNumberData : m_objectNumberList)
	{
		// オブジェクト名がデータと合致した？
		if (strcmp(objNumberData.name, name) == 0)
		{
			// 空き番号がある？
			if (!objNumberData.emptyNumber.empty())
			{
				// 空き番号を戻り値として返す
				return objNumberData.emptyNumber[0];
			}
			// 空き番号がない
			else
			{
				// 今回付与する番号を返す
				return ++objNumberData.maxNumber;
			}
		}
	}
	///////////////////////////////////////////////////////////
	// ここまで来たら、オブジェクト番号データが格納されていない
	// ０を返す
	return 0;
}

void yUno_SystemManager::yUno_GameObjectManager::SetObjectNumber(const char* name)
{
	// ===== 新規データの格納 ===== //
	// インスタンス生成
	ObjectNumberData objNumberData;
	objNumberData.name = name;	// オブジェクト名
	objNumberData.maxNumber = 0;// 最大値の番号
	// リストに格納
	m_objectNumberList.push_back(objNumberData);
}
