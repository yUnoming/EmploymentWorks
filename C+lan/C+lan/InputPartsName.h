#pragma once
/**
* @file		InputPartsName.h
* @brief	�e���͗p�Ɋ���U��ꂽ�ԍ��̗񋓌^���L�q����Ă���t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.05
*/


namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	�e��L�[��	</summary>
		enum KeyName
		{
			// ����������������������������������//
			// AlphabetKey / �A���t�@�x�b�g�L�[  //
			// ����������������������������������//
			/// <summary>
			/// A�L�[	</summary>
			A = 65,
			/// <summary>
			/// B�L�[	</summary>
			B = 66,
			/// <summary>
			/// C�L�[	</summary>
			C = 67,
			/// <summary>
			/// D�L�[	</summary>
			D = 68,
			/// <summary>
			/// E�L�[	</summary>
			E = 69,
			/// <summary>
			/// F�L�[	</summary>
			F = 70,
			/// <summary>
			/// G�L�[	</summary>
			G = 71,
			/// <summary>
			/// H�L�[	</summary>
			H = 72,
			/// <summary>
			/// I�L�[	</summary>
			I = 73,
			/// <summary>
			/// J�L�[	</summary>
			J = 74,
			/// <summary>
			/// K�L�[	</summary>
			K = 75,
			/// <summary>
			/// L�L�[	</summary>
			L = 76,
			/// <summary>
			/// M�L�[	</summary>
			M = 77,
			/// <summary>
			/// N�L�[	</summary>
			N = 78,
			/// <summary>
			/// O�L�[	</summary>
			O = 79,
			/// <summary>
			/// P�L�[	</summary>
			P = 80,
			/// <summary>
			/// Q�L�[	</summary>
			Q = 81,
			/// <summary>
			/// R�L�[	</summary>
			R = 82,
			/// <summary>
			/// S�L�[	</summary>
			S = 83,
			/// <summary>
			/// T�L�[	</summary>
			T = 84,
			/// <summary>
			/// U�L�[	</summary>
			U = 85,
			/// <summary>
			/// V�L�[	</summary>
			V = 86,
			/// <summary>
			/// W�L�[	</summary>
			W = 87,
			/// <summary>
			/// X�L�[	</summary>
			X = 88,
			/// <summary>
			/// Y�L�[	</summary>
			Y = 89,
			/// <summary>
			/// Z�L�[	</summary>
			Z = 90,
			// ����������������������������������//
			//  NumericKey / �e���L�[�E�����L�[  //
			// ����������������������������������//
			/// <summary>
			/// 1�L�[	</summary>
			Number1 = 49,
			/// <summary>
			/// 2�L�[	</summary>
			Number2 = 50,
			/// <summary>
			/// 3�L�[	</summary>
			Number3 = 51,
			/// <summary>
			/// 4�L�[	</summary>
			Number4 = 52,
			/// <summary>
			/// 5�L�[	</summary>
			Number5 = 53,
			/// <summary>
			/// 6�L�[	</summary>
			Number6 = 54,
			/// <summary>
			/// 7�L�[	</summary>
			Number7 = 55,
			/// <summary>
			/// 8�L�[	</summary>
			Number8 = 56,
			/// <summary>
			/// 9�L�[	</summary>
			Number9 = 57,
			/// <summary>
			/// 0�L�[	</summary>
			Number0 = 48,
			// ���������������������� //
			//  SymbolKey / �L���L�[  //
			// ���������������������� //
			/// <summary>
			///	�Z�~�R����	</summary>
			Semicolon = 187,

			// ���������������������������������� //
			//  FunctionKey / �t�@���N�V�����L�[  //
			// ���������������������������������� //
			/// <summary>
			/// F1�L�[	</summary>
			F1 = 112,
			/// <summary>
			/// F2�L�[	</summary>
			F2 = 113,
			/// <summary>
			/// F3�L�[	</summary>
			F3 = 114,
			/// <summary>
			/// F4�L�[	</summary>
			F4 = 115,
			/// <summary>
			/// F5�L�[	</summary>
			F5 = 116,
			/// <summary>
			/// F6�L�[	</summary>
			F6 = 117,
			/// <summary>
			/// F7�L�[	</summary>
			F7 = 118,
			/// <summary>
			/// F8�L�[	</summary>
			F8 = 119,
			/// <summary>
			/// F9�L�[	</summary>
			F9 = 120,
			/// F10�L�[	</summary>
			F10 = 121,
			/// <summary>
			/// F11�L�[	</summary>
			F11 = 122,
			/// <summary>
			/// F12�L�[	</summary>
			F12 = 123,
			/// F13�L�[	</summary>
			F13 = 124,
			/// F14�L�[	</summary>
			F14 = 125,
			/// F15�L�[	</summary>
			F15 = 126,
			/// F16�L�[	</summary>
			F16 = 127,
			/// F17�L�[	</summary>
			F17 = 128,
			/// F18�L�[	</summary>
			F18 = 129,
			/// F19�L�[	</summary>
			F19 = 130,
			/// F20�L�[	</summary>
			F20 = 131,
			/// F21�L�[	</summary>
			F21 = 132,
			/// F22�L�[	</summary>
			F22 = 133,
			/// F23�L�[	</summary>
			F23 = 134,
			/// F24�L�[	</summary>
			F24 = 135,
			// ����������������������������������//
			//		OtherKey / ���̑��̃L�[	     //
			// ����������������������������������//
			/// <summary>
			///	�G�X�P�[�v�L�[�^Esc	</summary>
			Escape = 27,
			/// <summary>
			/// �o�b�N�X�y�[�X�L�[�^BackSpace	</summary>
			BackSpace = 8,
			/// <summary>
			/// �^�u�L�[�^Tab	</summary>
			Tab = 9,
			/// <summary>
			///	�G���^�[�L�[�^Enter	</summary>
			Enter = 13,
			/// <summary>
			///	�����ɂ���V�t�g�L�[�^Shift	</summary>
			LeftShift = 16,
			/// <summary>
			///	�E���ɂ���V�t�g�L�[�^Shift	</summary>
			RightShift = 16,
			/// <summary>
			///	�����ɂ���R���g���[���L�[�^Ctrl	</summary>
			LeftControl = 17,
			/// <summary>
			///	�E���ɂ���R���g���[���L�[�^Ctrl	</summary>
			RightControl = 17,
			/// <summary>
			/// ���p/�S�p�����L�[	</summary>
			Hankaku = 229,
			/// <summary>
			///	���p/�S�p�����L�[	</summary>
			Zenkaku = 229,
			/// <summary>
			/// �X�y�[�X�L�[	</summary>
			Space = 32,
			/// <summary>
			///	�ϊ��L�[	</summary>
			Henkann = 28,
			/// <summary>
			/// ���ϊ��L�[	</summary>
			MuHenkann = 229,
			/// <summary>
			///	CapsLock�L�[	</summary>
			CapsLock = 58,
			/// <summary>
			///	Home�L�[	</summary>
			Home = 36,
			/// <summary>
			///	PageUp�L�[	</summary>
			PageUp = 33,
			/// <summary>
			///	PageDown�L�[	</summary>
			PageDown = 34,
			/// <summary>
			/// End�L�[	</summary>
			End = 35,
			/// <summary>
			///	����L�[�^��	</summary>
			UpArrow = 38,
			/// <summary>
			///	�����L�[�^��	</summary>
			LeftArrow = 37,
			/// <summary>
			/// �����L�[�^��</summary>
			DownArrow = 40,
			/// <summary>
			///	�E���L�[�^��	</summary>
			RightArrow = 39,
			/// <summary>
			/// Delete�L�[	</summary>
			Delete = 46,
			/// <summary>
			///	Windows�L�[	</summary>
			Windows = 91,
			/// <summary>
			/// �J�^�J�i�Ђ炪�ȃ��[�}���L�[</summary>
			Katakana = 229,
			/// <summary>
			/// �J�^�J�i�Ђ炪�ȃ��[�}���L�[</summary>
			Hiragana = 229,
			/// <summary>
			/// �J�^�J�i�Ђ炪�ȃ��[�}���L�[</summary>
			Romaji = 229,
		};


		/// <summary>
		/// �}�E�X�̊e�{�^����	</summary>
		enum MouseButtonName
		{
			/// <summary>
			/// ���{�^��	</summary>
			LeftButton,
			/// <summary>
			/// �X�N���[���z�C�[���{�^���^�}�E�X�z�C�[���{�^��	</summary>
			ScrollWheelButton,
			/// <summary>
			///	�E�{�^��	</summary>
			RightButton
		};
	}
}