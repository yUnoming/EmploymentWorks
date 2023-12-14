#pragma once
/**
* @file		InputPartsName.h
* @brief	�e���͗p�Ɋ���U��ꂽ�ԍ��̗񋓌^���L�q����Ă���t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.05
*/

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
		A = 30,
		/// <summary>
		/// B�L�[	</summary>
		B = 48,
		/// <summary>
		/// C�L�[	</summary>
		C = 46,
		/// <summary>
		/// D�L�[	</summary>
		D = 32,
		/// <summary>
		/// E�L�[	</summary>
		E = 18,
		/// <summary>
		/// F�L�[	</summary>
		F = 33,
		/// <summary>
		/// G�L�[	</summary>
		G = 34,
		/// <summary>
		/// H�L�[	</summary>
		H = 35,
		/// <summary>
		/// I�L�[	</summary>
		I = 23,
		/// <summary>
		/// J�L�[	</summary>
		J = 36,
		/// <summary>
		/// K�L�[	</summary>
		K = 37,
		/// <summary>
		/// L�L�[	</summary>
		L = 38,
		/// <summary>
		/// M�L�[	</summary>
		M = 50,
		/// <summary>
		/// N�L�[	</summary>
		N = 49,
		/// <summary>
		/// O�L�[	</summary>
		O = 24,
		/// <summary>
		/// P�L�[	</summary>
		P = 25,
		/// <summary>
		/// Q�L�[	</summary>
		Q = 16,
		/// <summary>
		/// R�L�[	</summary>
		R = 19,
		/// <summary>
		/// S�L�[	</summary>
		S = 31,
		/// <summary>
		/// T�L�[	</summary>
		T = 20,
		/// <summary>
		/// U�L�[	</summary>
		U = 22,
		/// <summary>
		/// V�L�[	</summary>
		V = 47,
		/// <summary>
		/// W�L�[	</summary>
		W = 17,
		/// <summary>
		/// X�L�[	</summary>
		X = 45,
		/// <summary>
		/// Y�L�[	</summary>
		Y = 21,
		/// <summary>
		/// Z�L�[	</summary>
		Z = 44,
		// ����������������������������������//
		//  NumericKey / �e���L�[�E�����L�[  //
		// ����������������������������������//
		/// <summary>
		/// 1�L�[	</summary>
		Number1 = 2,
		/// <summary>
		/// 2�L�[	</summary>
		Number2 = 3,
		/// <summary>
		/// 3�L�[	</summary>
		Number3 = 4,
		/// <summary>
		/// 4�L�[	</summary>
		Number4 = 5,
		/// <summary>
		/// 5�L�[	</summary>
		Number5 = 6,
		/// <summary>
		/// 6�L�[	</summary>
		Number6 = 7,
		/// <summary>
		/// 7�L�[	</summary>
		Number7 = 8,
		/// <summary>
		/// 8�L�[	</summary>
		Number8 = 9,
		/// <summary>
		/// 9�L�[	</summary>
		Number9 = 10,
		/// <summary>
		/// 0�L�[	</summary>
		Number0 = 11,
		// ���������������������������������� //
		//  FunctionKey / �t�@���N�V�����L�[  //
		// ���������������������������������� //
		/// <summary>
		/// F1�L�[	</summary>
		F1 = 59,
		/// <summary>
		/// F2�L�[	</summary>
		F2 = 60,
		/// <summary>
		/// F3�L�[	</summary>
		F3 = 61,
		/// <summary>
		/// F4�L�[	</summary>
		F4 = 62,
		/// <summary>
		/// F5�L�[	</summary>
		F5 = 63,
		/// <summary>
		/// F6�L�[	</summary>
		F6 = 64,
		/// <summary>
		/// F7�L�[	</summary>
		F7 = 65,
		/// <summary>
		/// F8�L�[	</summary>
		F8 = 66,
		/// <summary>
		/// F9�L�[	</summary>
		F9 = 67,
		/// <summary>
		/// F11�L�[	</summary>
		F11 = 87,
		/// <summary>
		/// F12�L�[	</summary>
		F12 = 88,
		// ����������������������������������//
		//		OtherKey / ���̑��̃L�[	     //
		// ����������������������������������//
		/// <summary>
		///	�G�X�P�[�v�L�[�^Esc	</summary>
		Escape = 1,
		/// <summary>
		/// �o�b�N�X�y�[�X�L�[�^BackSpace	</summary>
		BackSpace = 14,
		/// <summary>
		/// �^�u�L�[�^Tab	</summary>
		Tab = 15,
		/// <summary>
		///	�G���^�[�L�[�^Enter	</summary>
		Enter = 28,
		/// <summary>
		///	�u�����v�ɂ���V�t�g�L�[�^Shift	</summary>
		LeftShift = 42,
		/// <summary>
		///	�u�E���v�ɂ���V�t�g�L�[�^Shift	</summary>
		RightShift = 310,
		/// <summary>
		///	�u�����v�ɂ���R���g���[���L�[�^Ctrl	</summary>
		LeftControl = 29,
		/// <summary>
		///	�u�E���v�ɂ���R���g���[���L�[�^Ctrl	</summary>
		RightControl = 285,
		/// <summary>
		/// ���p/�S�p�����L�[	</summary>
		Hankaku = 41,
		/// <summary>
		///	���p/�S�p�����L�[	</summary>
		Zenkaku = 41,
		/// <summary>
		/// �X�y�[�X�L�[	</summary>
		Space = 57,
		/// <summary>
		///	�ϊ��L�[	</summary>
		Henkann = 121,
		/// <summary>
		/// ���ϊ��L�[	</summary>
		MuHenkann = 123,
		/// <summary>
		///	CapsLock�L�[	</summary>
		CapsLock = 58,
		/// <summary>
		///	Home�L�[	</summary>
		Home = 327,
		/// <summary>
		///	PageUp�L�[	</summary>
		PageUp = 329,
		/// <summary>
		///	PageDown�L�[	</summary>
		PageDown = 337,
		/// <summary>
		/// End�L�[	</summary>
		End = 335,
		/// <summary>
		///	����L�[�^��	</summary>
		UpArrow = 328,
		/// <summary>
		///	�����L�[�^��	</summary>
		LeftArrow = 331,
		/// <summary>
		/// �����L�[�^��</summary>
		DownArrow = 336,
		/// <summary>
		///	�E���L�[�^��	</summary>
		RightArrow = 333,
		/// <summary>
		/// Delete�L�[	</summary>
		Delete = 339,
		/// <summary>
		///	Windows�L�[	</summary>
		Windows = 347,
		/// <summary>
		/// �J�^�J�i�Ђ炪�ȃ��[�}���L�[</summary>
		Katakana = 16496,
		/// <summary>
		/// �J�^�J�i�Ђ炪�ȃ��[�}���L�[</summary>
		Hiragana = 16496,
		/// <summary>
		/// �J�^�J�i�Ђ炪�ȃ��[�}���L�[</summary>
		Romaji = 16496,
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