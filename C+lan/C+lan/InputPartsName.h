#pragma once
/**
* @file		InputPartsName.h
* @brief	各入力用に割り振られた番号の列挙型が記述されているファイル
* @author	Kojima, Kosei
* @date		2023.11.05
*/


namespace Ctlan
{
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
			A = 65,
			/// <summary>
			/// Bキー	</summary>
			B = 66,
			/// <summary>
			/// Cキー	</summary>
			C = 67,
			/// <summary>
			/// Dキー	</summary>
			D = 68,
			/// <summary>
			/// Eキー	</summary>
			E = 69,
			/// <summary>
			/// Fキー	</summary>
			F = 70,
			/// <summary>
			/// Gキー	</summary>
			G = 71,
			/// <summary>
			/// Hキー	</summary>
			H = 72,
			/// <summary>
			/// Iキー	</summary>
			I = 73,
			/// <summary>
			/// Jキー	</summary>
			J = 74,
			/// <summary>
			/// Kキー	</summary>
			K = 75,
			/// <summary>
			/// Lキー	</summary>
			L = 76,
			/// <summary>
			/// Mキー	</summary>
			M = 77,
			/// <summary>
			/// Nキー	</summary>
			N = 78,
			/// <summary>
			/// Oキー	</summary>
			O = 79,
			/// <summary>
			/// Pキー	</summary>
			P = 80,
			/// <summary>
			/// Qキー	</summary>
			Q = 81,
			/// <summary>
			/// Rキー	</summary>
			R = 82,
			/// <summary>
			/// Sキー	</summary>
			S = 83,
			/// <summary>
			/// Tキー	</summary>
			T = 84,
			/// <summary>
			/// Uキー	</summary>
			U = 85,
			/// <summary>
			/// Vキー	</summary>
			V = 86,
			/// <summary>
			/// Wキー	</summary>
			W = 87,
			/// <summary>
			/// Xキー	</summary>
			X = 88,
			/// <summary>
			/// Yキー	</summary>
			Y = 89,
			/// <summary>
			/// Zキー	</summary>
			Z = 90,
			// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
			//  NumericKey / テンキー・数字キー  //
			// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
			/// <summary>
			/// 1キー	</summary>
			Number1 = 49,
			/// <summary>
			/// 2キー	</summary>
			Number2 = 50,
			/// <summary>
			/// 3キー	</summary>
			Number3 = 51,
			/// <summary>
			/// 4キー	</summary>
			Number4 = 52,
			/// <summary>
			/// 5キー	</summary>
			Number5 = 53,
			/// <summary>
			/// 6キー	</summary>
			Number6 = 54,
			/// <summary>
			/// 7キー	</summary>
			Number7 = 55,
			/// <summary>
			/// 8キー	</summary>
			Number8 = 56,
			/// <summary>
			/// 9キー	</summary>
			Number9 = 57,
			/// <summary>
			/// 0キー	</summary>
			Number0 = 48,
			// ＝＝＝＝＝＝＝＝＝＝＝ //
			//  SymbolKey / 記号キー  //
			// ＝＝＝＝＝＝＝＝＝＝＝ //
			/// <summary>
			///	セミコロン	</summary>
			Semicolon = 187,

			// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
			//  FunctionKey / ファンクションキー  //
			// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
			/// <summary>
			/// F1キー	</summary>
			F1 = 112,
			/// <summary>
			/// F2キー	</summary>
			F2 = 113,
			/// <summary>
			/// F3キー	</summary>
			F3 = 114,
			/// <summary>
			/// F4キー	</summary>
			F4 = 115,
			/// <summary>
			/// F5キー	</summary>
			F5 = 116,
			/// <summary>
			/// F6キー	</summary>
			F6 = 117,
			/// <summary>
			/// F7キー	</summary>
			F7 = 118,
			/// <summary>
			/// F8キー	</summary>
			F8 = 119,
			/// <summary>
			/// F9キー	</summary>
			F9 = 120,
			/// F10キー	</summary>
			F10 = 121,
			/// <summary>
			/// F11キー	</summary>
			F11 = 122,
			/// <summary>
			/// F12キー	</summary>
			F12 = 123,
			/// F13キー	</summary>
			F13 = 124,
			/// F14キー	</summary>
			F14 = 125,
			/// F15キー	</summary>
			F15 = 126,
			/// F16キー	</summary>
			F16 = 127,
			/// F17キー	</summary>
			F17 = 128,
			/// F18キー	</summary>
			F18 = 129,
			/// F19キー	</summary>
			F19 = 130,
			/// F20キー	</summary>
			F20 = 131,
			/// F21キー	</summary>
			F21 = 132,
			/// F22キー	</summary>
			F22 = 133,
			/// F23キー	</summary>
			F23 = 134,
			/// F24キー	</summary>
			F24 = 135,
			// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
			//		OtherKey / その他のキー	     //
			// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝//
			/// <summary>
			///	エスケープキー／Esc	</summary>
			Escape = 27,
			/// <summary>
			/// バックスペースキー／BackSpace	</summary>
			BackSpace = 8,
			/// <summary>
			/// タブキー／Tab	</summary>
			Tab = 9,
			/// <summary>
			///	エンターキー／Enter	</summary>
			Enter = 13,
			/// <summary>
			///	左側にあるシフトキー／Shift	</summary>
			LeftShift = 16,
			/// <summary>
			///	右側にあるシフトキー／Shift	</summary>
			RightShift = 16,
			/// <summary>
			///	左側にあるコントロールキー／Ctrl	</summary>
			LeftControl = 17,
			/// <summary>
			///	右側にあるコントロールキー／Ctrl	</summary>
			RightControl = 17,
			/// <summary>
			/// 半角/全角漢字キー	</summary>
			Hankaku = 229,
			/// <summary>
			///	半角/全角漢字キー	</summary>
			Zenkaku = 229,
			/// <summary>
			/// スペースキー	</summary>
			Space = 32,
			/// <summary>
			///	変換キー	</summary>
			Henkann = 28,
			/// <summary>
			/// 無変換キー	</summary>
			MuHenkann = 229,
			/// <summary>
			///	CapsLockキー	</summary>
			CapsLock = 58,
			/// <summary>
			///	Homeキー	</summary>
			Home = 36,
			/// <summary>
			///	PageUpキー	</summary>
			PageUp = 33,
			/// <summary>
			///	PageDownキー	</summary>
			PageDown = 34,
			/// <summary>
			/// Endキー	</summary>
			End = 35,
			/// <summary>
			///	上矢印キー／↑	</summary>
			UpArrow = 38,
			/// <summary>
			///	左矢印キー／←	</summary>
			LeftArrow = 37,
			/// <summary>
			/// 下矢印キー／↓</summary>
			DownArrow = 40,
			/// <summary>
			///	右矢印キー／→	</summary>
			RightArrow = 39,
			/// <summary>
			/// Deleteキー	</summary>
			Delete = 46,
			/// <summary>
			///	Windowsキー	</summary>
			Windows = 91,
			/// <summary>
			/// カタカナひらがなローマ字キー</summary>
			Katakana = 229,
			/// <summary>
			/// カタカナひらがなローマ字キー</summary>
			Hiragana = 229,
			/// <summary>
			/// カタカナひらがなローマ字キー</summary>
			Romaji = 229,
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
}