#pragma once
/**
* @file		Message.h
* @brief	ネットワーク通信で使用するメッセージをまとめたファイル
* @author	Kojima, Kosei
* @date		2023.12.11
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"
#include "Transform.h"
#include "Text.h"

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　		 列挙型宣言	   	　　  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
/// <summary>
///	メッセージの種類	</summary>
enum MessageType
{
	/// <summary>
	///	コンポーネント更新	</summary>
	UpdateComponent,
	/// <summary>
	///	オブジェクトクリック	</summary>
	ClickObject
};

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　		 構造体宣言	   	　　  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
/// <summary>
/// メッセージヘッダー
///：メッセージの基礎的な情報が入っている	</summary>
struct Header
{
	/// <summary>
	/// 送受信するメッセージの種類	</summary>
	int type;	
};

/// <summary>
/// メッセージボディー
/// メッセージの具体的な情報が入っている	</summary>
struct Body
{
	/// <summary>
	///	オブジェクト情報	</summary>
	GameObject object;
	/// <summary>
	///	コンポーネントの種類	</summary>
	char componentType[30];
	/// <summary>
	///	各コンポーネント情報	</summary>
	union
	{
		Transform transform;
		Text text;
	};
};

/// <summary>
///	メッセージ内容	</summary>
struct Message
{
	/// <summary>
	///	メッセージヘッダー	</summary>
	Header header;
	/// <summary>
	///	メッセージボディー	</summary>
	Body   body;
};

/// <summary>
///	送受信用のメッセージ情報	</summary>
struct MessageData
{
	MessageData() {};
	~MessageData() {};
	union
	{
		/// <summary>
		///	メッセージ内容	</summary>
		Message message;
		/// <summary>
		///	送受信で扱う情報	</summary>
		char data[sizeof(Message)];
	};
};
