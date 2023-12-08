// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_GameObjectManager.h"


// ������������������������������ //
// �@�@	�@static�ϐ��̒�`�@�@ �@ //
// ������������������������������ //
std::list<yUno_SystemManager::yUno_GameObjectManager::ObjectNameData> yUno_SystemManager::yUno_GameObjectManager::m_objectNameList;
std::list<yUno_SystemManager::yUno_GameObjectManager::ObjectNumberData> yUno_SystemManager::yUno_GameObjectManager::m_objectNumberList;


void yUno_SystemManager::yUno_GameObjectManager::UnInit()
{
	// ���X�g�̃N���A
	m_objectNameList.clear();
	m_objectNumberList.clear();
}

const char* yUno_SystemManager::yUno_GameObjectManager::CheckObjectName(const char* name)
{
	// �߂�l�Ƃ��Ĉ����ϐ�
	char returnName[50];

	// ===== �I�u�W�F�N�g��������Ă��Ȃ����m�F ===== //
	// �I�u�W�F�N�g���f�[�^�擾
	for (auto& objNameData : m_objectNameList)
	{
		if (strcmp(objNameData.myName, name) == 0)
		{
			// �t�^����I�u�W�F�N�g�ԍ��擾
			int number = GetObjectNumber(objNameData.baseName);
			// �I�u�W�F�N�g���ɔԍ���A��
			sprintf_s(returnName, "%s%d", objNameData.baseName, number);

			// ----- �I�u�W�F�N�g���f�[�^�����X�g�Ɋi�[ ----- //
			// �C���X�^���X����
			ObjectNameData newObjNameData;
			strcpy_s(newObjNameData.baseName, objNameData.baseName);	// �ԍ���t�^����O�̖��O
			strcpy_s(newObjNameData.myName, returnName);				// ���݂̖��O
			newObjNameData.objectNameNumber = number;					// �I�u�W�F�N�g�ԍ�
			// ���X�g�Ɋi�[
			m_objectNameList.push_back(newObjNameData);

			// �I�u�W�F�N�g����߂�l�Ƃ��ĕԂ�
			return returnName;
		}
	}
	///////////////////////////////////////////////
	// �����܂ŗ�����A�I�u�W�F�N�g���͔���Ă��Ȃ�
	// =====�@�e�f�[�^�����X�g�Ɋi�[ ===== //
	// ----- �I�u�W�F�N�g�ԍ� ----- //
	SetObjectNumber(name);
	// ----- �I�u�W�F�N�g�� ----- //
	// �C���X�^���X����
	ObjectNameData newObjNameData;
	strcpy_s(newObjNameData.baseName, name);	// �ԍ���t�^����O�̖��O
	strcpy_s(newObjNameData.myName, name);		// ���݂̖��O
	newObjNameData.objectNameNumber = 0;		// �I�u�W�F�N�g�ԍ�
	// ���X�g�Ɋi�[
	m_objectNameList.push_back(newObjNameData);

	// �I�u�W�F�N�g����߂�l�Ƃ��ĕԂ�
	return name;
}

int yUno_SystemManager::yUno_GameObjectManager::GetObjectNumber(const char* name)
{
	// ===== �I�u�W�F�N�g�ԍ��擾 ===== //
	// �I�u�W�F�N�g�ԍ��f�[�^�擾
	for (auto& objNumberData : m_objectNumberList)
	{
		// �I�u�W�F�N�g�����f�[�^�ƍ��v�����H
		if (strcmp(objNumberData.name, name) == 0)
		{
			// �󂫔ԍ�������H
			if (!objNumberData.emptyNumber.empty())
			{
				// �󂫔ԍ���߂�l�Ƃ��ĕԂ�
				return objNumberData.emptyNumber[0];
			}
			// �󂫔ԍ����Ȃ�
			else
			{
				// ����t�^����ԍ���Ԃ�
				return ++objNumberData.maxNumber;
			}
		}
	}
	///////////////////////////////////////////////////////////
	// �����܂ŗ�����A�I�u�W�F�N�g�ԍ��f�[�^���i�[����Ă��Ȃ�
	// �O��Ԃ�
	return 0;
}

void yUno_SystemManager::yUno_GameObjectManager::SetObjectNumber(const char* name)
{
	// ===== �V�K�f�[�^�̊i�[ ===== //
	// �C���X�^���X����
	ObjectNumberData objNumberData;
	objNumberData.name = name;	// �I�u�W�F�N�g��
	objNumberData.maxNumber = 0;// �ő�l�̔ԍ�
	// ���X�g�Ɋi�[
	m_objectNumberList.push_back(objNumberData);
}
