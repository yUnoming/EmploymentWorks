// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_GameObjectManager.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　	　static変数の定義　　 　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
std::list<yUno_SystemManager::yUno_GameObjectManager::ObjectNameData> yUno_SystemManager::yUno_GameObjectManager::m_objectNameList;


void yUno_SystemManager::yUno_GameObjectManager::UnInit()
{
	// リストのクリア
	m_objectNameList.clear();
}

const char* yUno_SystemManager::yUno_GameObjectManager::CheckObjectName(const char* name)
{
	char returnName[50];		// 戻り値として扱う変数
	ObjectNameData objNameData;	// オブジェクト名情報

	// 引数の名称と同じオブジェクトがあれば取得
	auto result = std::find_if(
		m_objectNameList.begin(),
		m_objectNameList.end(),
		[&name](ObjectNameData nameData) {return strcmp(nameData.myName, name) == 0; });

	// 名称は被っていない？
	if (result == m_objectNameList.end())
	{
		// ----- オブジェクト名情報をリストに格納 ----- //
		// インスタンス生成
		ObjectNameData newObjNameData;
		strcpy_s(newObjNameData.baseName, name);	// 番号を付与する前の名前
		strcpy_s(newObjNameData.myName, name);		// 現在の名前
		newObjNameData.number = 0;					// オブジェクト番号
		// リストに格納
		m_objectNameList.push_back(newObjNameData);
		return name;
	}
	// 名称被りが無くなるまでループ
	while (result != m_objectNameList.end())
	{
		objNameData = *result;
		// オブジェクト名に番号を連結
		sprintf_s(returnName, "%s%d", objNameData.baseName, ++objNameData.number);

		result = std::find_if(m_objectNameList.begin(),
			m_objectNameList.end(),
			[&returnName](ObjectNameData nameData) {return strcmp(nameData.myName, returnName) == 0; });
	}

	// ----- オブジェクト名情報をリストに格納 ----- //
	// インスタンス生成
	ObjectNameData newObjNameData;
	strcpy_s(newObjNameData.baseName, objNameData.baseName);	// 番号を付与する前の名前
	strcpy_s(newObjNameData.myName, returnName);				// 現在の名前
	newObjNameData.number = objNameData.number;					// オブジェクト番号
	// リストに格納
	m_objectNameList.push_back(newObjNameData);
	return returnName;
}

yUno_SystemManager::yUno_GameObjectManager::ObjectNameData
yUno_SystemManager::yUno_GameObjectManager::GetObjectNameData(const char* name)
{
	// 格納されているデータ分ループ
	for (auto& objNameData : m_objectNameList)
	{
		// 名称が同じ？
		if (strcmp(objNameData.myName, name) == 0)
		{
			return objNameData;
		}
	}
}

void yUno_SystemManager::yUno_GameObjectManager::SetObjectNameData(ObjectNameData objNameData)
{
	// リストに格納
	m_objectNameList.push_back(objNameData);
}
