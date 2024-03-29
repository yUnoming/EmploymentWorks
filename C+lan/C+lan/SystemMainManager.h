#pragma once
/**
* @file		SystemMainManager.h
* @brief	SystemMainManagerNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.01
*/
//  //
// @@t@CΜCN[h@@ //
//  //
#include "SystemSceneManager.h"

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			/// CΕVXeπρ·½ίΜNX	</summary>
			class SystemMainManager
			{
				private:
					// ----- variables / Ο ----- //
					/// <summary>
					/// »έΜvCσΤ	</summary>
					static bool m_demoPlay;

				public:
					// ----- functions / Φ ----- //
					/// <summary>
					/// ϊ»	</summary>
					/// <param name="app">
					/// AvP[Vξρ	</param>
					static void Init(Application* app);
					/// <summary>
					/// IΉ	</summary>
					static void Uninit();
					/// <summary>
					///	XV	</summary>
					static void Update();
					/// <summary>
					/// `ζ	</summary>
					static void Draw();
			};
		}
	}
}
