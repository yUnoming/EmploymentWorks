// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_KeyInputManager.h"
#include "KeyInput.h"
#include "Time.h"

#include <Windows.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
yUno_SystemManager::yUno_KeyInputManager::KeyInfo yUno_SystemManager::yUno_KeyInputManager::m_nowKeyInfo[400];
yUno_SystemManager::yUno_KeyInputManager::KeyInfo yUno_SystemManager::yUno_KeyInputManager::m_lateKeyInfo[400];
yUno_SystemManager::yUno_KeyInputManager::CheckKeyInfo yUno_SystemManager::yUno_KeyInputManager::m_upStateKeyInfo;
yUno_SystemManager::yUno_KeyInputManager::CheckKeyInfo yUno_SystemManager::yUno_KeyInputManager::m_downStateKeyInfo;


void yUno_SystemManager::yUno_KeyInputManager::Update()
{
	// ===== 各キー状態の経過時間を測定 ===== //
	//**  押されているキー  **//
	// キーが押されている？（押されていない場合は処理を行わない）
	if (!m_downStateKeyInfo.keyType->empty())
	{
		// 押されているキーの数だけループ
		for (int i = 0; i < m_downStateKeyInfo.keyIndex; i++)
		{
			// キーの押されている時間を計算
			m_nowKeyInfo[m_downStateKeyInfo.keyType->at(i)].nowStateElapsedTime += PublicSystem::Time::DeltaTime * 0.0001f;
		}
	}
	//**  離されているキー  **//
	// キーが離されている（判定を行っているキーが存在する）？（離されていない（判定を行っているキーが存在しない）場合は処理を行わない）
	if (!m_upStateKeyInfo.keyType->empty())
	{
		// 離されているキーの数だけループ
		for (int i = 0; i < m_upStateKeyInfo.keyIndex; i++)
		{
			// キーの離されている時間を計算
			m_nowKeyInfo[m_upStateKeyInfo.keyType->at(i)].nowStateElapsedTime += PublicSystem::Time::DeltaTime * 0.0001f;
		}
	}
}

void yUno_SystemManager::yUno_KeyInputManager::KeepNowKeyInfo()
{
	// 現在のキー状態を保存
	memcpy(m_lateKeyInfo, m_nowKeyInfo, sizeof(m_nowKeyInfo));
}

void yUno_SystemManager::yUno_KeyInputManager::SetKeyDown(int key)
{
	// ＝＝＝＝＝　判定のリセット処理　＝＝＝＝＝ //
	// 離された判定の途中でキーが押された？
	if (m_nowKeyInfo[key].keyState == Up)
	{
		// 離れているキーの判定から除外
		m_upStateKeyInfo.keyType->erase(std::find(m_upStateKeyInfo.keyType->begin(), m_upStateKeyInfo.keyType->end(), key));

		// 要素数を減らす
		m_upStateKeyInfo.keyIndex--;

		// 経過時間をリセット
		m_nowKeyInfo[key].nowStateElapsedTime = 0.0;
	}

	// ＝＝＝＝＝　押されたキーの処理　＝＝＝＝＝ //
	// 前回キーは離されていた？
	if (m_nowKeyInfo[key].keyState != Down)
	{
		// キーが押されていることを保存
		m_nowKeyInfo[key].keyState = Down;

		// 押されているキーの種類を保存
		m_downStateKeyInfo.keyType->emplace_back(key);

		// 要素数を増やす
		m_downStateKeyInfo.keyIndex++;
	}
}

void yUno_SystemManager::yUno_KeyInputManager::SetKeyUp(int key)
{
	// ＝＝＝＝＝　判定の変更処理　＝＝＝＝＝ //
	// 前回キーは押されていた？
	if (m_nowKeyInfo[key].keyState == Down)
	{
		// 離れているキーの判定から除外
		m_downStateKeyInfo.keyType->erase(std::find(m_downStateKeyInfo.keyType->begin(), m_downStateKeyInfo.keyType->end(), key));

		// 要素数を減らす
		m_downStateKeyInfo.keyIndex--;

		// 経過時間をリセット
		m_nowKeyInfo[key].nowStateElapsedTime = 0.0;


		// ＝＝＝＝＝　押されたキーの処理　＝＝＝＝＝ //
		// キーが離されていることを保存
		m_nowKeyInfo[key].keyState = Up;

		// 離されたキーの種類を保存
		m_upStateKeyInfo.keyType->emplace_back(key);

		// 要素数を増やす
		m_upStateKeyInfo.keyIndex++;
	}
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyDownTrigger(PublicSystem::KeyName key)
{
	// 前回キーは離されていたが、現在は押されているならtrue
	return m_lateKeyInfo[key].keyState != Down && m_nowKeyInfo[key].keyState == Down;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyDown(PublicSystem::KeyName key)
{
	// 現在キーは押されているならtrue
	return m_nowKeyInfo[key].keyState == Down;
}

double yUno_SystemManager::yUno_KeyInputManager::GetKeyDownTime(PublicSystem::KeyName key)
{
	// キーが押されている？
	if (m_nowKeyInfo[key].keyState == Down)
		// 経過時間を返す
		return m_nowKeyInfo[key].nowStateElapsedTime;
	
	return 0;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyUpTrigger(PublicSystem::KeyName key)
{
	// 前回キーは押されていたが、現在は離されているならtrue
	return m_lateKeyInfo[key].keyState == Down && m_nowKeyInfo[key].keyState != Down;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyUp(PublicSystem::KeyName key)
{
	// 現在キーは離されている？
	return m_nowKeyInfo[key].keyState == NoStatus || m_nowKeyInfo[key].keyState == Up;
}

double yUno_SystemManager::yUno_KeyInputManager::GetKeyUpTime(PublicSystem::KeyName key)
{
	// キーが離されている？
	if (m_nowKeyInfo[key].keyState == Up)
		// 経過時間を返す
		return m_nowKeyInfo[key].nowStateElapsedTime;

	return 0;
}
