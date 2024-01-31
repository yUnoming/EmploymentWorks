#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

constexpr unsigned short PORTNO = 49152;

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#pragma comment(lib, "ws2_32.lib")

#include "SystemNetWorkManager.h"

#include <stdio.h>
#include <time.h>
#include <iostream>


Server* Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::m_Server;

void Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::Init()
{
	// サーバーの生成
	m_Server = new Server();
}

void Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::Update()
{
	// ログインしていたサーバーがシャットダウンされた？
	if (m_Server->IsServerShutdown())
		m_Server->LogoutServer();	// ログアウト処理
}

void Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::Uninit()
{
	// サーバーの削除
	delete m_Server;
}
