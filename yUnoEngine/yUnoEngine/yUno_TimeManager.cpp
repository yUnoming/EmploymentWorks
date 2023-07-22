// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_TimeManager.h"
#include "Time.h"

#include <Windows.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   　ライブラリのリンク　        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#pragma comment (lib, "winmm.lib")	// timeGetTime()を使うためにリンクする


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
double yUno_SystemManager::yUno_TimeManager::m_Last_Time;


void yUno_SystemManager::yUno_TimeManager::Init()
{
	// 初期化時に現在時刻を代入しておく
	m_Last_Time = timeGetTime();
}

void yUno_SystemManager::yUno_TimeManager::Update()
{
	timeBeginPeriod(1);				// 精度を１ミリ秒に上げる
	DWORD Now_Time = timeGetTime();	// 現在時刻を取得
	timeEndPeriod(1);				// 精度を元に戻す

	// 現在時刻-前回時刻で求めた値をデルタタイムに代入
	System::Time::DeltaTime = Now_Time - m_Last_Time;

	//＊-----デルタタイムの調整-----＊//
	if (System::Time::DeltaTime <= 0)	// デルタタイムが０以下？
		System::Time::DeltaTime = 1;	// 値を１に調整

	m_Last_Time = Now_Time;			// 現在時刻を保存
}
