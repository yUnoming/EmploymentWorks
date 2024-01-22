#pragma once
/**
* @file		SystemTimeManager.h
* @brief	SystemTimeManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.07
*/

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			///	���Ԃ��Ǘ�����N���X	</summary>
			class SystemTimeManager
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

	}
}

