// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SystemGameObjectManager.h"


// ������������������������������ //
// �@�@	�@static�ϐ��̒�`�@�@ �@ //
// ������������������������������ //
std::list<Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::ObjectNameData> Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::m_objectNameList;


void Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::Uninit()
{
	// ���X�g�̃N���A
	m_objectNameList.clear();
}

const char* Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::CheckObjectName(const char* name)
{
	char newObjName[50]{};							// �߂�l�Ƃ��Ĉ����ϐ�
	ObjectNameData objNameData = ObjectNameData();	// �I�u�W�F�N�g�����

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
		ObjectNameData newObjNameData = ObjectNameData();
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
		sprintf_s(newObjName, "%s%d", objNameData.baseName, ++objNameData.number);

		result = std::find_if(m_objectNameList.begin(),
			m_objectNameList.end(),
			[&newObjName](ObjectNameData nameData) {return strcmp(nameData.myName, newObjName) == 0; });
	}

	// ----- �I�u�W�F�N�g���������X�g�Ɋi�[ ----- //
	// �C���X�^���X����
	ObjectNameData newObjNameData = ObjectNameData();
	strcpy_s(newObjNameData.baseName, objNameData.baseName);	// �ԍ���t�^����O�̖��O
	strcpy_s(newObjNameData.myName, newObjName);				// ���݂̖��O
	newObjNameData.number = objNameData.number;					// �I�u�W�F�N�g�ԍ�
	// ���X�g�Ɋi�[
	m_objectNameList.push_back(newObjNameData);
	return newObjNameData.myName;
}

Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::ObjectNameData
Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::GetObjectNameData(const char* name)
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
	return ObjectNameData();
}

void Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::SetObjectNameData(ObjectNameData objNameData)
{
	// ���X�g�Ɋi�[
	m_objectNameList.push_back(objNameData);
}

void Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::DeleteObjectNameData(const char* name)
{
	// ���X�g�ɗv�f�������Ă��Ȃ��H
	if (m_objectNameList.empty())	return;	//�������I��

	// �����̒l�Ɠ����I�u�W�F�N�g���̏����폜
	m_objectNameList.erase(
		std::find_if(
		m_objectNameList.begin(),
		m_objectNameList.end(),
		[&name](ObjectNameData nameData) {return strcmp(nameData.myName, name) == 0; }));
}
