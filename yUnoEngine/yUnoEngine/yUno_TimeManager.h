#pragma once

namespace yUno_SystemManager
{
	class yUno_TimeManager
	{
		public:
			static void Init();
			static void Update();

		private:
			static double m_Last_Time;	// 前回ループ時の時間
	};
}

