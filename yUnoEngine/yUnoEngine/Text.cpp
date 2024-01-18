#include "Text.h"

void PublicSystem::Text::AddText(const char* addText)
{
    // テキスト長を取得
    int textLength = strlen(this->text);
    // 値をコピー
    memcpy(dummyText, this->text, textLength);

    // 追加する文字列長だけループ
    int addTextNum = 0;
    for (int i = textLength; i <= textLength + strlen(addText); i++)
    {
        dummyText[i] = addText[addTextNum];
        addTextNum++;
    }

    // 追加するテキストを代入
    this->text = dummyText;
}

void PublicSystem::Text::ChangeText(const char* changeText)
{
    // テキスト長を取得
    int textLength = strlen(changeText);
    // 値をコピー
    memcpy(dummyText, changeText, textLength);
    // 追加するテキストを代入
    this->text = dummyText;
}

void PublicSystem::Text::DeleteText()
{
    // テキスト長を取得
    int textLength = strlen(this->text);
    
    // テキストが入っている？
    if(textLength >= 1)
        // 末尾の文字を削除
        strncpy_s(dummyText, dummyText, textLength - 1);
    
    // 削除後のテキストを代入
    this->text = dummyText;
}

Text& PublicSystem::Text::operator=(const Text& other)
{
    // 自分自身ではない？
    if (this != &other)
    {
        // 値代入
        text = other.text;
        fontSize = other.fontSize;
        leftTopPoint = other.leftTopPoint;
    }
    return *this;
}
