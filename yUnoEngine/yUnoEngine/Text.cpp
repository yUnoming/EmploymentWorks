#include "Text.h"

void PublicSystem::Text::AddText(const char* addText)
{
    // テキスト長を取得
    int textLength = strlen(this->text);
    // 値をコピー
    memcpy(dummyText, GetComponent<Text>()->text, textLength);

    // 追加する文字列長だけループ
    int addTextNum = 0;
    for (int i = textLength; i < textLength + strlen(addText); i++)
    {
        dummyText[i] = addText[addTextNum];
        addTextNum++;
    }

    // 追加するテキストを代入
    this->text = dummyText;
}
