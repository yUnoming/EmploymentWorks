#pragma once

// 各ファイルを読み込むためのクラス
class FileReader
{
	public:
		// ----- functions / 関数 ----- //
		/// <summary>
		/// ttfファイルを読み込む	</summary>
		/// <param name = "_filePath">
		/// ／読み込みたいファイルの参照パス名	</param>
		/// <param name = "_fontName">
		/// ／フォントの名称	</param>
		static void Read_ttfFile(const wchar_t* _filePath, const char* _fontName);

};

