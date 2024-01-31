// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "FileReader.h"
#include "SystemTextRendererManager.h"
#include <Shlwapi.h>
#include <iostream>
#include <tchar.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		参考元ソース	 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// ReadTtfFile内フォントの生成、作成
// https://hakase0274.hatenablog.com/entry/2018/11/17/170918


void FileReader::ReadTtfFile(const wchar_t* filePath, const char* fontName)
{
	// バッファサイズの取得
	int bufferSize = MultiByteToWideChar(CP_UTF8, 0, fontName, -1, nullptr, 0);
	// バッファの確保
	WCHAR* wideFontName = new WCHAR[bufferSize];
	// マルチバイト文字列からワイド文字列に変換
	MultiByteToWideChar(CP_UTF8, 0, fontName, -1, wideFontName, bufferSize);

	// システムにフォントリソースを追加する
	// 追加されたフォントの数を取得しておく
	int fontNum = AddFontResourceExW(
		filePath,				// 追加したいフォントの参照パス
		FR_PRIVATE,				// 追加するフォントの特性
		0						// 0指定でOK
	);

	// フォントが追加されなかった？
	if (fontNum == 0)
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
		*wideFontName					// フォントのタイプフェイス名
	};

	// フォントの作成
	HFONT hFont = CreateFontIndirect(&lf);

	// フォントが作成出来なかった？
	if (hFont == NULL)
	{
		std::cout << "Error!!! ErrorCode：" << GetLastError() << std::endl;
	}

	// 作成したフォントを追加する
	SystemManager::SystemTextRendererManager::SetFont(hFont);
	// 削除
	delete[] wideFontName;
}
