#include "Text.h"

Ctlan::PublicSystem::Text::Text(const Text* other)
{
    // �l���
    other->dummyText ? ChangeText(other->dummyText) : ChangeText(other->text);
    fontSize = other->fontSize;
    leftTopPoint = other->leftTopPoint;
}

void Ctlan::PublicSystem::Text::AddText(const char* addText)
{
    // �e�L�X�g�����擾
    int textLength = (int)strlen(this->text);
    // �l���R�s�[
    memcpy(dummyText, this->text, textLength);

    // �ǉ����镶���񒷂������[�v
    int addTextNum = 0;
    for (int i = textLength; i <= textLength + strlen(addText); i++)
    {
        dummyText[i] = addText[addTextNum];
        addTextNum++;
    }

    // �ǉ�����e�L�X�g����
    this->text = dummyText;
}

void Ctlan::PublicSystem::Text::ChangeText(const char* changeText)
{
    // �e�L�X�g�����擾
    size_t textLength = strlen(changeText);
    // �l�̏�����
    ZeroMemory(dummyText, sizeof(dummyText));
    // �l���R�s�[
    memcpy(dummyText, changeText, textLength);
    // �ǉ�����e�L�X�g����
    this->text = dummyText;
}

void Ctlan::PublicSystem::Text::DeleteText()
{
    // �e�L�X�g�����擾
    size_t textLength = strlen(this->text);
    
    // �e�L�X�g�������Ă���H
    if(textLength >= 1)
        // �����̕������폜
        strncpy_s(dummyText, dummyText, textLength - 1);
    
    // �폜��̃e�L�X�g����
    this->text = dummyText;
}

Text& Ctlan::PublicSystem::Text::operator=(const Text& other)
{
    // �������g�ł͂Ȃ��H
    if (this != &other)
    {
        // �l���
        other.dummyText ? ChangeText(other.dummyText) : ChangeText(other.text);
        fontSize = other.fontSize;
        leftTopPoint = other.leftTopPoint;
    }
    return *this;
}
