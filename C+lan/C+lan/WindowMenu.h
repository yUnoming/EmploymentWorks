#pragma once
/**
* @file		WindowMenu.h
* @brief	WindowMenuNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.28
*/
//  //
// @@t@CΜCN[h@@ //
//  //
#include "Application.h"


namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace ApplicationSystem
		{
			/// <summary>
			///	EBhEγΙ ιj[π΅€NX	</summary>
			class WindowMenu
			{
				public:
					// ----- enum / ρ^ ----- //
					/// <summary>
					///	ej[ΙθUιID	</summary>
					enum MenuID
					{
						// t@C^u
						ID_File,
						ID_NewScene,
						ID_OpenScene,

						// μ¬^u
						ID_Create = 10,
						ID_CreateCube,
						ID_CreateText,

						// T[o[^u
						ID_Server = 20,
						ID_OpenServer,
						ID_CloseServer,
						ID_LoginServer,
						ID_LogoutServer,
					};

					// ----- functions / Φ ----- //
					/// <summary>
					///	j[πμ¬·ι	</summary>
					static void Create();

					/// <summary>
					///	j[ΰeΙ]ΑΔAπΐs	</summary>
					static void Run(WORD menuID);
				};
		}
	}
}