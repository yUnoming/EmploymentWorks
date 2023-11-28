#pragma once
/**
* @file		yUno_NetWorkManager.h
* @brief	yUno_NetWorkManagerNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.16
*/

//  //
// @@t@CΜCN[h@@ //
//  //
#include "Server.h"


//  //
// @@		 }Nθ`		@@  //
//  //

namespace yUno_SystemManager
{
	/// <summary>
	///	lbg[NΜπΗ·ιNX	</summary>
	class yUno_NetWorkManager
	{
		private:
			// ----- variables / Ο ----- //
			/// <summary>
			/// T[o[	</summary>
			static Server* m_Server;

		public:
			// ----- enums / ρ^ ----- //
			/// <summary>
			///	σM·ιbZ[WΜνή	</summary>
			enum MessageType
			{
				/// <summary>
				///	R|[lgΜlXV	</summary>
				UpdateComponentValue,
				/// <summary>
				///	IuWFNgͺNbN³κ½	</summary>
				ClickedObject
			};

			// ----- functions / Φ ----- //
			/// <summary>
			///	ϊ»	</summary>
			static void Init();
			/// <summary>
			/// IΉ	</summary>
			static void UnInit();
			
			/// <summary>
			///	T[o[ξρπζΎ	</summary>
			/// <returns>
			/// T[o[ξρπΤ·	</returns>
			static Server* GetServer() { return m_Server; };
	};
}

