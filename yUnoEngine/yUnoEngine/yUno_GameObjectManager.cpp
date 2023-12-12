// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_GameObjectManager.h"


// ������������������������������ //
// �@�@	�@static�ϐ��̒�`�@�@ �@ //
// ������������������������������ //
std::list<yUno_SystemManager::yUno_GameObjectManager::ObjectNameData> yUno_SystemManager::yUno_GameObjectManager::m_objectNameList;


void yUno_SystemManager::yUno_GameObjectManager::UnInit()
{
	// ���X�g�̃N���A
	m_objectNameList.clear();
}

const char* yUno_SystemManager::yUno_GameObjectManager::CheckObjectName(const char* name)
{
	char returnName[50];		// �߂�l�Ƃ��Ĉ����ϐ�
	ObjectNameData objNameData;	// �I�u�W�F�N�g�����

	// �����̖��̂Ɠ����I�u�W�F�N�g������Ύ擾
	auto result = std::find_if(
		m_objectNameList.begin(),
		m_objectNameList.end(),
		[&name](ObjectNameData nameData) {return strcmp(nameData.myName, name) == 0; });

	// ���͔̂���Ă��Ȃ��H
	if (result == m_objectNameList.end())
	{
		// ----- �I�u�W�F�N�g���������X�g�Ɋi�[ ----- //
		// �C���X�^���X����
		ObjectNameData newObjNameData;
		strcpy_s(newObjNameData.baseName, name);	// �ԍ���t�^����O�̖��O
		strcpy_s(newObjNameData.myName, name);		// ���݂̖��O
		newObjNameData.number = 0;					// �I�u�W�F�N�g�ԍ�
		// ���X�g�Ɋi�[
		m_objectNameList.push_back(newObjNameData);
		return name;
	}
	// ���̔�肪�����Ȃ�܂Ń��[�v
	while (result != m_objectNameList.end())
	{
		objNameData = *result;
		// �I�u�W�F�N�g���ɔԍ���A��
		sprintf_s(returnName, "%s%d", objNameData.baseName, ++objNameData.number);

		result = std::find_if(m_objectNameList.begin(),
			m_objectNameList.end(),
			[&returnName](ObjectNameData nameData) {return strcmp(nameData.myName, returnName) == 0; });
	}

	// ----- �I�u�W�F�N�g���������X�g�Ɋi�[ ----- //
	// �C���X�^���X����
	ObjectNameData newObjNameData;
	strcpy_s(newObjNameData.baseName, objNameData.baseName);	// �ԍ���t�^����O�̖��O
	strcpy_s(newObjNameData.myName, returnName);				// ���݂̖��O
	newObjNameData.number = objNameData.number;					// �I�u�W�F�N�g�ԍ�
	// ���X�g�Ɋi�[
	m_objectNameList.push_back(newObjNameData);
	return returnName;
}

yUno_SystemManager::yUno_GameObjectManager::ObjectNameData
yUno_SystemManager::yUno_GameObjectManager::GetObjectNameData(const char* name)
{
	// �i�[����Ă���f�[�^�����[�v
	for (auto& objNameData : m_objectNameList)
	{
		// ���̂������H
		if (strcmp(objNameData.myName, name) == 0)
		{
			return objNameData;
		}
	}
}

void yUno_SystemManager::yUno_GameObjectManager::SetObjectNameData(ObjectNameData objNameData)
{
	// ���X�g�Ɋi�[
	m_objectNameList.push_back(objNameData);
}
