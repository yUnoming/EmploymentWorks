#include "Text.h"

void PublicSystem::Text::AddText(const char* addText)
{
    // �e�L�X�g�����擾
    int textLength = strlen(this->text);
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

void PublicSystem::Text::ChangeText(const char* changeText)
{
    // �e�L�X�g�����擾
    int textLength = strlen(changeText);
    // �l���R�s�[
    memcpy(dummyText, changeText, textLength);
    // �ǉ�����e�L�X�g����
    this->text = dummyText;
}

void PublicSystem::Text::DeleteText()
{
    // �e�L�X�g�����擾
    int textLength = strlen(this->text);
    
    // �e�L�X�g�������Ă���H
    if(textLength >= 1)
        // �����̕������폜
        strncpy_s(dummyText, dummyText, textLength - 1);
    
    // �폜��̃e�L�X�g����
    this->text = dummyText;
}

Text& PublicSystem::Text::operator=(const Text& other)
{
    // �������g�ł͂Ȃ��H
    if (this != &other)
    {
        // �l���
        text = other.text;
        fontSize = other.fontSize;
        leftTopPoint = other.leftTopPoint;
    }
    return *this;
}
