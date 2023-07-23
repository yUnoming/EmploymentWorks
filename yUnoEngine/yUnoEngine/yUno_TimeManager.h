#pragma once

namespace yUno_SystemManager
{
	class yUno_TimeManager
	{
		public:
			static void Init();
			static void Update();

		private:
			static double m_Last_Time;	// ‘O‰ñƒ‹[ƒv‚ÌŠÔ
	};
}

