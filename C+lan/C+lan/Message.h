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
namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		///	メッセージの種類	</summary>
		enum MessageType
		{
			// ----- 通信制御 ----- //
			/// <summary>
			///	通信開始	</summary>
			CommunicationStart,
			/// <summary>
			///	通信成功	</summary>
			CommunicationSuccess,
			/// <summary>
			///	通信終了	</summary>
			CommunicationEnd,

			// ----- コンポーネント ----- //
			/// <summary>
			///	コンポーネント更新	</summary>
			UpdateComponent,

			// ----- オブジェクト全般 ----- //
			/// <summary>
			///	オブジェクトクリック	</summary>
			ClickObject,
			/// <summary>
			/// オブジェクト削除	</summary>
			ObjectDelete,

			// ----- テンプレートオブジェクト ----- //
			/// <summary>
			///	キューブ作成	</summary>
			CreateCube,
			/// <summary>
			///	テキスト作成	</summary>
			CreateText
		};

		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
		// 　		 構造体宣言	   	　　  //
		// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
		/// <summary>
		/// メッセージヘッダー
		///：メッセージの基礎的な情報が入っている	</summary>
		struct Header
		{
			Header() {};
			~Header() {};

			/// <summary>
			/// 送受信するメッセージの種類	</summary>
			int type = 0;
			/// <summary>
			///	送信元ユーザーのランク	</summary>
			int userRank = 0;
			/// <summary>
			///	送信元ユーザー番号	</summary>
			int userNo = 0;
		};

		/// <summary>
		/// オブジェクト関係のメッセージボディー
		/// ：メッセージの具体的な情報が入っている	</summary>
		struct BodyObject
		{
			BodyObject() { transform = 0; text = 0; };
			~BodyObject() {};

			/// <summary>
			///	オブジェクト情報	</summary>
			GameObject object;
			/// <summary>
			///	コンポーネントの種類	</summary>
			char componentType[50]{};
			/// <summary>
			///	各コンポーネント情報	</summary>
			union
			{
				Ctlan::PublicSystem::Transform transform;
				Ctlan::PublicSystem::Text text;
			};
		};

		/// <summary>
		/// シーン関係のメッセージボディー
		/// ：メッセージの具体的な情報が入っている	</summary>
		struct BodyScene
		{
			BodyScene() {};
			~BodyScene() {};

			/// <summary>
			///	シーン名	</summary>
			char sceneName[30]{};
			/// <summary>
			///	シーンデータ	</summary>
			char sceneData[1024]{};
		};

		/// <summary>
		///	メッセージ内容	</summary>
		struct Message
		{
			Message(){};
			~Message(){};

			/// <summary>
			///	メッセージヘッダー	</summary>
			Header header;
			/// <summary>
			///	メッセージボディー	</summary>
			union
			{
				BodyObject   bodyObject;
				BodyScene	 bodyScene;
			};
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
				char data[sizeof(Message)]{};
			};
		};
	}
}