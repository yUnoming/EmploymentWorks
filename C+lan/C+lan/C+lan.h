#pragma once
/**
* @file		C+lan.h
* @brief	C+lanのヘッダーファイルをまとめたファイル
* @author	Kojima, Kosei
* @date		2024.1.30
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　	 コンポーネント系		　　//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "BoxCollider.h"	// ボックスの当たり判定
#include "Camera.h"			// カメラ
#include "Material.h"		// マテリアル
#include "Shader.h"			// シェーダー
#include "Text.h"			// テキスト
#include "Transform.h"		// トランスフォーム
	

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　		  入力系			　　//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"	// 入力系名称
#include "KeyInput.h"		// キー入力
#include "MouseInput.h"		// マウス入力
#include "ScreenInput.h"	// 画面入力


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　		　  その他 　		　　//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "CalculationHit.h"	// 当たり判定の計算一覧
#include "Color.h"			// 色
#include "SceneManager.h"	// シーンマネージャー
#include "Time.h"			// 時間
#include "Vector2.h"		// 2次元ベクトル
#include "Vector3.h"		// 3次元ベクトル