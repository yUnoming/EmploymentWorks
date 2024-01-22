// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SystemTimeManager.h"
#include "Time.h"

#include <Windows.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   　ライブラリのリンク　        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#pragma comment (lib, "winmm.lib")	// timeGetTime()を使うためにリンクする


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
double Ctlan::PrivateSystem::SystemManager::SystemTimeManager::m_lastTime;


void Ctlan::PrivateSystem::SystemManager::SystemTimeManager::Init()
{
	// 初期化時に現在時刻を代入しておく
	m_lastTime = timeGetTime();
}

void Ctlan::PrivateSystem::SystemManager::SystemTimeManager::Update()
{
	timeBeginPeriod(1);				// 精度を１ミリ秒に上げる
	DWORD nowTime = timeGetTime();	// 現在時刻を取得
	timeEndPeriod(1);				// 精度を元に戻す

	// 現在時刻-前回時刻で求めた値をデルタタイムに代入
	Ctlan::PublicSystem::Time::DeltaTime = nowTime - m_lastTime;

	//＊-----デルタタイムの調整-----＊//
	if (Ctlan::PublicSystem::Time::DeltaTime <= 0)	// デルタタイムが０以下？
		Ctlan::PublicSystem::Time::DeltaTime = 1;	// 値を１に調整

	m_lastTime = nowTime;			// 現在時刻を保存
}
