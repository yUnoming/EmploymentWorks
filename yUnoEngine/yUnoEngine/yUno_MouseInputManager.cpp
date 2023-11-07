// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_MouseInputManager.h"

#include <Windows.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
yUno_SystemManager::yUno_MouseInputManager::MouseStatus yUno_SystemManager::yUno_MouseInputManager::m_nowMouseState[3];
yUno_SystemManager::yUno_MouseInputManager::MouseStatus yUno_SystemManager::yUno_MouseInputManager::m_lateMouseState[3];
yUno_SystemManager::yUno_MouseInputManager::MouseWheelStatus yUno_SystemManager::yUno_MouseInputManager::m_mouseWheelState;


void yUno_SystemManager::yUno_MouseInputManager::KeepNowMouseState()
{
	// 現在のマウスの状態をセット
	memcpy(m_lateMouseState, m_nowMouseState, sizeof(m_nowMouseState));
	
	// マウスホイールの回転判定を終了
	m_mouseWheelState = NotRotation;
}

void yUno_SystemManager::yUno_MouseInputManager::SetMouseDown(PublicSystem::MouseButtonName button)
{
	// マウスが押されている状態に変更
	m_nowMouseState[button] = Down;
}

void yUno_SystemManager::yUno_MouseInputManager::SetMouseUp(PublicSystem::MouseButtonName button)
{
	// マウスが離されている状態に変更
	m_nowMouseState[button] = Up;
}

void yUno_SystemManager::yUno_MouseInputManager::SetMouseWheelState(int mouseWheelParam)
{
	// 現在のマウスホイールの入力値をセット
	m_mouseWheelState = (MouseWheelStatus)mouseWheelParam;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetMouseDownTrigger(PublicSystem::MouseButtonName button)
{
	// マウスが押された瞬間ならtrue
	return m_nowMouseState[button] == Down &&
		(m_lateMouseState[button] == Up || m_lateMouseState[button] == NoStatus);
}

bool yUno_SystemManager::yUno_MouseInputManager::GetMouseDown(PublicSystem::MouseButtonName button)
{
	// マウスが押されていたらtrue
	return m_nowMouseState[button] == Down;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetMouseUpTrigger(PublicSystem::MouseButtonName button)
{
	// マウスが離された瞬間ならtrue
	return m_nowMouseState[button] == Up &&
		(m_lateMouseState[button] == Down || m_lateMouseState[button] == NoStatus);
}

bool yUno_SystemManager::yUno_MouseInputManager::GetMouseUp(PublicSystem::MouseButtonName button)
{
	// マウスが離されていたらtrue
	return m_nowMouseState[button] == Up || m_nowMouseState[button] == NoStatus;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetWheelRotation()
{
	// マウスホイールが回転されていたらtrue
	return m_mouseWheelState == ForwardRotation || m_mouseWheelState == BackwardRotation;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetWheelRotationForward()
{
	// マウスホイールが前方回転されていたらtrue
	return m_mouseWheelState == ForwardRotation;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetWheelRotationBackward()
{
	// マウスホイールが後方回転されていたらtrue
	return m_mouseWheelState == BackwardRotation;
}