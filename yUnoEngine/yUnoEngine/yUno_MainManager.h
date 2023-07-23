#pragma once

class yUno_MainManager
{
	private:
		// ----- variables ----- //


		// ----- methods ----- //
		void Change_Mode();

	public:
		// ----- methods ----- //
		static void Init();
		static void UnInit();
		static void Update();
		static void Draw();
};
