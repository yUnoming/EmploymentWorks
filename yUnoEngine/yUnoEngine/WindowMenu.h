#pragma once
/**
* @file		WindowMenu.h
* @brief	WindowMenuクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.28
*/

#include "Application.h"

class WindowMenu
{
	public:
		// ----- enum / 列挙型 ----- //
		/// <summary>
		///	各メニューに割り振るID	</summary>
		enum MenuID
		{
			// ファイルタブ
			ID_File,
			ID_NewScene,

			// 作成タブ
			ID_Create = 10,
			ID_CreateCube,

			// サーバータブ
			ID_Server = 20,
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

		/// <summary>
		///	メニュー内容に従って、処理を実行	</summary>
		static void Run(WORD menuID);
};

