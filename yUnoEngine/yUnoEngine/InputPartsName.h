#pragma once
/**
* @file		InputPartsName.h
* @brief	各入力用に割り振られた番号の列挙型が記述されているファイル
* @author	Kojima, Kosei
* @date		2023.11.05
*/

namespace PublicSystem
{
	/// <summary>
	///	各種キー名	</summary>
	enum KeyName
	{
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		// AlphabetKey / アルファベットキー  //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		/// <summary>
		/// Aキー	</summary>
		A = 30,
		/// <summary>
		/// Bキー	</summary>
		B = 48,
		/// <summary>
		/// Cキー	</summary>
		C = 46,
		/// <summary>
		/// Dキー	</summary>
		D = 32,
		/// <summary>
		/// Eキー	</summary>
		E = 18,
		/// <summary>
		/// Fキー	</summary>
		F = 33,
		/// <summary>
		/// Gキー	</summary>
		G = 34,
		/// <summary>
		/// Hキー	</summary>
		H = 35,
		/// <summary>
		/// Iキー	</summary>
		I = 23,
		/// <summary>
		/// Jキー	</summary>
		J = 36,
		/// <summary>
		/// Kキー	</summary>
		K = 37,
		/// <summary>
		/// Lキー	</summary>
		L = 38,
		/// <summary>
		/// Mキー	</summary>
		M = 50,
		/// <summary>
		/// Nキー	</summary>
		N = 49,
		/// <summary>
		/// Oキー	</summary>
		O = 24,
		/// <summary>
		/// Pキー	</summary>
		P = 25,
		/// <summary>
		/// Qキー	</summary>
		Q = 16,
		/// <summary>
		/// Rキー	</summary>
		R = 19,
		/// <summary>
		/// Sキー	</summary>
		S = 31,
		/// <summary>
		/// Tキー	</summary>
		T = 20,
		/// <summary>
		/// Uキー	</summary>
		U = 22,
		/// <summary>
		/// Vキー	</summary>
		V = 47,
		/// <summary>
		/// Wキー	</summary>
		W = 17,
		/// <summary>
		/// Xキー	</summary>
		X = 45,
		/// <summary>
		/// Yキー	</summary>
		Y = 21,
		/// <summary>
		/// Zキー	</summary>
		Z = 44,
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		//  NumericKey / テンキー・数字キー  //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		/// <summary>
		/// 1キー	</summary>
		Number1 = 2,
		/// <summary>
		/// 2キー	</summary>
		Number2 = 3,
		/// <summary>
		/// 3キー	</summary>
		Number3 = 4,
		/// <summary>
		/// 4キー	</summary>
		Number4 = 5,
		/// <summary>
		/// 5キー	</summary>
		Number5 = 6,
		/// <summary>
		/// 6キー	</summary>
		Number6 = 7,
		/// <summary>
		/// 7キー	</summary>
		Number7 = 8,
		/// <summary>
		/// 8キー	</summary>
		Number8 = 9,
		/// <summary>
		/// 9キー	</summary>
		Number9 = 10,
		/// <summary>
		/// 0キー	</summary>
		Number0 = 11,
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
		//  FunctionKey / ファンクションキー  //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
		/// <summary>
		/// F1キー	</summary>
		F1 = 59,
		/// <summary>
		/// F2キー	</summary>
		F2 = 60,
		/// <summary>
		/// F3キー	</summary>
		F3 = 61,
		/// <summary>
		/// F4キー	</summary>
		F4 = 62,
		/// <summary>
		/// F5キー	</summary>
		F5 = 63,
		/// <summary>
		/// F6キー	</summary>
		F6 = 64,
		/// <summary>
		/// F7キー	</summary>
		F7 = 65,
		/// <summary>
		/// F8キー	</summary>
		F8 = 66,
		/// <summary>
		/// F9キー	</summary>
		F9 = 67,
		/// <summary>
		/// F11キー	</summary>
		F11 = 87,
		/// <summary>
		/// F12キー	</summary>
		F12 = 88,
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		//		OtherKey / その他のキー	     //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
		/// <summary>
		///	エスケープキー／Esc	</summary>
		Escape = 1,
		/// <summary>
		/// バックスペースキー／BackSpace	</summary>
		BackSpace = 14,
		/// <summary>
		/// タブキー／Tab	</summary>
		Tab = 15,
		/// <summary>
		///	エンターキー／Enter	</summary>
		Enter = 28,
		/// <summary>
		///	「左側」にあるシフトキー／Shift	</summary>
		LeftShift = 42,
		/// <summary>
		///	「右側」にあるシフトキー／Shift	</summary>
		RightShift = 310,
		/// <summary>
		///	「左側」にあるコントロールキー／Ctrl	</summary>
		LeftControl = 29,
		/// <summary>
		///	「右側」にあるコントロールキー／Ctrl	</summary>
		RightControl = 285,
		/// <summary>
		/// 半角/全角漢字キー	</summary>
		Hankaku = 41,
		/// <summary>
		///	半角/全角漢字キー	</summary>
		Zenkaku = 41,
		/// <summary>
		/// スペースキー	</summary>
		Space = 57,
		/// <summary>
		///	変換キー	</summary>
		Henkann = 121,
		/// <summary>
		/// 無変換キー	</summary>
		MuHenkann = 123,
		/// <summary>
		///	CapsLockキー	</summary>
		CapsLock = 58,
		/// <summary>
		///	Homeキー	</summary>
		Home = 327,
		/// <summary>
		///	PageUpキー	</summary>
		PageUp = 329,
		/// <summary>
		///	PageDownキー	</summary>
		PageDown = 337,
		/// <summary>
		/// Endキー	</summary>
		End = 335,
		/// <summary>
		///	上矢印キー／↑	</summary>
		UpArrow = 328,
		/// <summary>
		///	左矢印キー／←	</summary>
		LeftArrow = 331,
		/// <summary>
		/// 下矢印キー／↓</summary>
		DownArrow = 336,
		/// <summary>
		///	右矢印キー／→	</summary>
		RightArrow = 333,
		/// <summary>
		/// Deleteキー	</summary>
		Delete = 339,
		/// <summary>
		///	Windowsキー	</summary>
		Windows = 347,
		/// <summary>
		/// カタカナひらがなローマ字キー</summary>
		Katakana = 16496,
		/// <summary>
		/// カタカナひらがなローマ字キー</summary>
		Hiragana = 16496,
		/// <summary>
		/// カタカナひらがなローマ字キー</summary>
		Romaji = 16496,
	};

	
	/// <summary>
	/// マウスの各ボタン名	</summary>
	enum MouseButtonName
	{
		/// <summary>
		/// 左ボタン	</summary>
		LeftButton,
		/// <summary>
		/// スクロールホイールボタン／マウスホイールボタン	</summary>
		ScrollWheelButton,
		/// <summary>
		///	右ボタン	</summary>
		RightButton
	};
}