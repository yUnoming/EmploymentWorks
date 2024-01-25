// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SystemMouseInputManager.h"

#include <Windows.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::MouseStatus Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_nowMouseState[3];
Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::MouseStatus Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_lateMouseState[3];
Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::MouseWheelStatus Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_mouseWheelState;
Ctlan::PublicSystem::Vector2 Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_lateCursorPosition;
Ctlan::PublicSystem::Vector2 Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_nowCursorPosition;


void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::Update()
{
	// 前回のカーソル座標を保存
	m_lateCursorPosition = m_nowCursorPosition;
	// 現在のカーソル座標を取得
	tagPOINT cursorPos;
	GetCursorPos(&cursorPos);
	m_nowCursorPosition = PublicSystem::Vector2(cursorPos);
}

void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::KeepNowMouseState()
{
	// 現在のマウスの状態をセット
	memcpy(m_lateMouseState, m_nowMouseState, sizeof(m_nowMouseState));
	
	// マウスホイールの回転判定を終了
	m_mouseWheelState = NotRotation;
}

void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseDown(Ctlan::PublicSystem::MouseButtonName button)
{
	// マウスが押されている状態に変更
	m_nowMouseState[button] = Down;
}

void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseUp(Ctlan::PublicSystem::MouseButtonName button)
{
	// マウスが離されている状態に変更
	m_nowMouseState[button] = Up;
}

void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseWheelState(int mouseWheelParam)
{
	// 現在のマウスホイールの入力値をセット
	m_mouseWheelState = (MouseWheelStatus)mouseWheelParam;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseDownTrigger(Ctlan::PublicSystem::MouseButtonName button)
{
	// マウスが押された瞬間ならtrue
	return m_nowMouseState[button] == Down &&
		(m_lateMouseState[button] == Up || m_lateMouseState[button] == NoStatus);
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseDown(Ctlan::PublicSystem::MouseButtonName button)
{
	// マウスが押されていたらtrue
	return m_nowMouseState[button] == Down;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseUpTrigger(Ctlan::PublicSystem::MouseButtonName button)
{
	// マウスが離された瞬間ならtrue
	return m_nowMouseState[button] == Up &&
		(m_lateMouseState[button] == Down || m_lateMouseState[button] == NoStatus);
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseUp(Ctlan::PublicSystem::MouseButtonName button)
{
	// マウスが離されていたらtrue
	return m_nowMouseState[button] == Up || m_nowMouseState[button] == NoStatus;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotation()
{
	// マウスホイールが回転されていたらtrue
	return m_mouseWheelState == ForwardRotation || m_mouseWheelState == BackwardRotation;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotationForward()
{
	// マウスホイールが前方回転されていたらtrue
	return m_mouseWheelState == ForwardRotation;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotationBackward()
{
	// マウスホイールが後方回転されていたらtrue
	return m_mouseWheelState == BackwardRotation;
}