#pragma once
/**
* @file		yUno_TimeManager.h
* @brief	yUno_TimeManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.07
*/
namespace yUno_SystemManager
{
	/// <summary>
	///	���Ԃ��Ǘ�����N���X	</summary>
	class yUno_TimeManager
	{
		private:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			///	�O��̎���	</summary>
			static double m_lastTime;

		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			///	������	</summary>
			static void Init();
			/// <summary>
			///	�X�V	</summary>
			static void Update();
	};
}

