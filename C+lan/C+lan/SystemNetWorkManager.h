#pragma once
/**
* @file		SystemNetWorkManager.h
* @brief	SystemNetWorkManagerNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.16
*/

//  //
// @@t@CΜCN[h@@ //
//  //
#include "Server.h"


namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			///	lbg[NΜπΗ·ιNX	</summary>
			class SystemNetWorkManager
			{
				private:
					// ----- variables / Ο ----- //
					/// <summary>
					/// T[o[	</summary>
					static Server* m_Server;

				public:
					// ----- functions / Φ ----- //
					/// <summary>
					///	ϊ»	</summary>
					static void Init();
					/// <summary>
					///	XV	</summary>
					static void Update();
					/// <summary>
					/// IΉ	</summary>
					static void Uninit();

					/// <summary>
					///	T[o[ξρπζΎ	</summary>
					/// <returns>
					/// T[o[ξρπΤ·	</returns>
					static Server* GetServer() { return m_Server; };
			};
		}
	}
}

