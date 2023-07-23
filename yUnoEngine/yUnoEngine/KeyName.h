#pragma once

namespace System
{
	// 各種キー番号
	enum KeyName
	{
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		// AlphabetKey / アルファベットキー  //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		A = 30,
		B = 48,
		C = 46,
		D = 32,
		E = 18,
		F = 33,
		G = 34,
		H = 35,
		I = 23,
		J = 36,
		K = 37,
		L = 38,
		M = 50,
		N = 49,
		O = 24,
		P = 25,
		Q = 16,
		R = 19,
		S = 31,
		T = 20,
		U = 22,
		V = 47,
		W = 17,
		X = 45,
		Y = 21,
		Z = 44,
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		//  NumericKey / テンキー・数字キー  //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		Number1 = 2,
		Number2 = 3,
		Number3 = 4,
		Number4 = 5,
		Number5 = 6,
		Number6 = 7,
		Number7 = 8,
		Number8 = 9,
		Number9 = 10,
		Number0 = 11,
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
		//  FunctionKey / ファンクションキー  //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
		F1 = 59,
		F2 = 60,
		F3 = 61,
		F4 = 62,
		F5 = 63,
		F6 = 64,
		F7 = 65,
		F8 = 66,
		F9 = 67,
		F11 = 87,
		F12 = 88,
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		//		OtherKey / その他のキー	     //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		Escape = 1,			// Escape
		BackSpace = 14,		// BackSpace
		Tab = 15,			// Tab
		Enter = 28,			// Enter
		LeftShift = 42,		// 左側にあるShift
		RightShift = 310,	// 右側にあるShift
		LeftControl = 29,	// 左側にあるControl
		RightControl = 285,	// 右側にあるControl
		Hankaku = 41,		// 半角
		Zenkaku = 41,		// 全角
		Space = 57,			// Space
		Henkann = 121,		// 変換
		MuHenkann = 123,	// 無変換
		CapsLock = 58,		// CapsLock
		Home = 327,			// Home
		PageUp = 329,		// PageUp
		PageDown = 337,		// PageDown
		End = 335,			// End
		UpArrow = 328,		// 上矢印 ↑
		LeftArrow = 331,	// 左矢印 ←
		DownArrow = 336,	// 下矢印 ↓
		RightArrow = 333,	// 右矢印 →
		Delete = 339,		// Delete
		Windows = 347,		// Windows
		Katakana = 16496,	// カタカナ
		Hiragana = 16496,	// ひらがな
		Romaji = 16496,		// ローマ字
	};
}