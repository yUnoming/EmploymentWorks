#pragma once
/**
* @file		yUno_MainManager.h
* @brief	yUno_MainManagerNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.01
*/
//  //
// @@t@CΜCN[h@@ //
//  //
#include "yUno_SceneManager.h"

namespace yUno_SystemManager
{
	class yUno_NetWorkManager;
}

/// <summary>
/// CΕVXeπρ·½ίΜNX	</summary>
class yUno_MainManager
{
	private:
		// ----- variables / Ο ----- //
		/// <summary>
		/// »έΜV[	</summary>
		static yUno_SceneManager* m_NowScene;
		/// <summary>
		/// »έΜvCσΤ	</summary>
		static bool m_DemoPlay;

		// lbg[N}l[W[
		static yUno_SystemManager::yUno_NetWorkManager* m_netWorkManager;

	public:
		// ----- methods / Φ ----- //
		/// <summary>
		/// ϊ»	</summary>
		/// <param name="app">
		/// AvP[Vξρ	</param>
		static void Init(Application* app);
		/// <summary>
		/// IΉ	</summary>
		static void UnInit();
		/// <summary>
		///	XV	</summary>
		static void Update();
		/// <summary>
		/// `ζ	</summary>
		static void Draw();
};
