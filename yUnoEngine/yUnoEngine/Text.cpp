#include "Text.h"

void PublicSystem::Text::AddText(const char* addText)
{
    // �e�L�X�g�����擾
    int textLength = strlen(this->text);
    // �l���R�s�[
    memcpy(dummyText, GetComponent<Text>()->text, textLength);

    // �ǉ����镶���񒷂������[�v
    int addTextNum = 0;
    for (int i = textLength; i < textLength + strlen(addText); i++)
    {
        dummyText[i] = addText[addTextNum];
        addTextNum++;
    }

    // �ǉ�����e�L�X�g����
    this->text = dummyText;
}
