#pragma once
/**
* @file		WindowMenu.h
* @brief	WindowMenuクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.28
*/

class WindowMenu
{
	public:
		// ----- enum / 列挙型 ----- //
		/// <summary>
		///	各メニューに割り振るID	</summary>
		enum MenuID
		{
			ID_Server = 1,
			ID_OpenServer,
			ID_CloseServer,
			ID_LoginServer,
			ID_LogoutServer,
			ID_SendMessage,
		};

		// ----- functions / 関数 ----- //
		/// <summary>
		///	メニューを作成する	</summary>
		static void Create();
};

