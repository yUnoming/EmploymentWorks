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
			ID_Server,
			ID_OpenServer = 1,
			ID_CloseServer = 2,
			ID_LoginServer = 3,
			ID_LogoutServer = 4,
			ID_SendMessage = 5,
		};

		// ----- functions / 関数 ----- //
		/// <summary>
		///	メニューを作成する	</summary>
		static void Create();
};

