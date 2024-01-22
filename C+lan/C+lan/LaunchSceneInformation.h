#pragma once
/**
* @file		LaunchSceneInformation.h
* @brief	LaunchSceneInformationクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2024.01.06
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace Information
		{
			/// <summary>
			/// 起動するシーン情報</summary>
			class LaunchSceneInformation
			{
				private:
					// ----- variables / 変数 ----- //
					/// <summary>
					///	起動するシーン名	</summary>
					char m_launchSceneName[30];

				public:
					// ----- functions / 関数 ----- //
					/// <summary>
					///	コンストラクタ	</summary>
					LaunchSceneInformation();
					/// <summary>
					///	情報のロード	</summary>
					void Load();
					/// <summary>
					///	情報のセーブ	</summary>
					void Save();

					/// <summary>
					///	起動するシーン名を取得	</summary>
					/// <returns>
					///	シーンがあれば起動するシーン名、無ければnullptr	</returns>
					const char* GetLaunchSceneName();
			};
		}
	}
}

