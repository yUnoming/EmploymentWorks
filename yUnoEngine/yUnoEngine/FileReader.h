#pragma once
/**
* @file		FileReader.h
* @brief	FileReaderクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.10.29
*/

/// <summary>
/// 各ファイルを読み込むためのクラス	</summary>
class FileReader
{
	public:
		// ----- functions / 関数 ----- //
		/// <summary>
		/// ttfファイルを読み込む	</summary>
		/// <param name = "filePath">
		/// 読み込みたいファイルの参照パス名	</param>
		/// <param name = "fontName">
		/// フォントの名称	</param>
		static void ReadTtfFile(const wchar_t* filePath, const char* fontName);
};

