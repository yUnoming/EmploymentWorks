// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "FileReader.h"
#include "yUno_TextRendererManager.h"
#include <Shlwapi.h>
#include <iostream>
#include <tchar.h>


void FileReader::Read_ttfFile(const wchar_t* _filePath, const char* _fontName)
{
	// システムにフォントリソースを追加する
	// 追加されたフォントの数を取得しておく
	int Font_Num = AddFontResourceEx(
		_filePath,				// 追加したいフォントの参照パス
		FR_PRIVATE,				// 追加するフォントの特性
		0						// 0指定でOK
	);

	// フォントが追加されなかった？
	if (Font_Num == 0)
	{
		std::cout << "Error!!! ErrorCode：" << GetLastError() << std::endl;
	}


	// フォントの生成
	LOGFONT lf = {
		1000,							// フォントの高さ
		0,								// フォントの幅
		0,								// 脱走ベクトルとデバイスのX軸の間の角度
		0,								// 文字の基本線とデバイスのX軸の間の角度
		1,								// フォントの太さ
		FALSE,							// TRUEなら斜体フォントになる
		FALSE,							// TRUEなら下線付きフォントになる
		FALSE,							// TRUEなら取り消し線フォントになる
		DEFAULT_CHARSET,				// 文字セット
		OUT_DEFAULT_PRECIS,				// 出力制度
		CLIP_DEFAULT_PRECIS,			// クリッピングの精度
		PROOF_QUALITY,					// 出力品質
		DEFAULT_PITCH | FF_DONTCARE,	// フォントのピッチとファミリ
		*_fontName						// フォントのタイプフェイス名
	};

	// フォントの作成
	HFONT hFont = CreateFontIndirect(&lf);

	// フォントが作成出来なかった？
	if (hFont == NULL)
	{
		std::cout << "Error!!! ErrorCode：" << GetLastError() << std::endl;
	}

	// 作成したフォントを追加する
	yUno_SystemManager::yUno_TextRendererManager::Set_Font(hFont);
}
