// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SystemGameObjectManager.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　	　static変数の定義　　 　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
std::list<Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::ObjectNameData> Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::m_objectNameList;


void Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::Uninit()
{
	// リストのクリア
	m_objectNameList.clear();
}

const char* Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::CheckObjectName(const char* name)
{
	char newObjName[50]{};							// 戻り値として扱う変数
	ObjectNameData objNameData = ObjectNameData();	// オブジェクト名情報

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
		ObjectNameData newObjNameData = ObjectNameData();
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
		sprintf_s(newObjName, "%s%d", objNameData.baseName, ++objNameData.number);

		result = std::find_if(m_objectNameList.begin(),
			m_objectNameList.end(),
			[&newObjName](ObjectNameData nameData) {return strcmp(nameData.myName, newObjName) == 0; });
	}

	// ----- オブジェクト名情報をリストに格納 ----- //
	// インスタンス生成
	ObjectNameData newObjNameData = ObjectNameData();
	strcpy_s(newObjNameData.baseName, objNameData.baseName);	// 番号を付与する前の名前
	strcpy_s(newObjNameData.myName, newObjName);				// 現在の名前
	newObjNameData.number = objNameData.number;					// オブジェクト番号
	// リストに格納
	m_objectNameList.push_back(newObjNameData);
	return newObjNameData.myName;
}

Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::ObjectNameData
Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::GetObjectNameData(const char* name)
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
	return ObjectNameData();
}

void Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::SetObjectNameData(ObjectNameData objNameData)
{
	// リストに格納
	m_objectNameList.push_back(objNameData);
}

void Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::DeleteObjectNameData(const char* name)
{
	// リストに要素が入っていない？
	if (m_objectNameList.empty())	return;	//処理を終了

	// 引数の値と同じオブジェクト名の情報を削除
	m_objectNameList.erase(
		std::find_if(
		m_objectNameList.begin(),
		m_objectNameList.end(),
		[&name](ObjectNameData nameData) {return strcmp(nameData.myName, name) == 0; }));
}
