#pragma once
/**
* @file		C+lan.h
* @brief	C+lanのヘッダーファイルをまとめたファイル
* @author	Kojima, Kosei
* @date		2024.1.30
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　	 コンポーネント一覧		　　//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "BoxCollider.h"	// ボックスの当たり判定
#include "Camera.h"			// カメラ
#include "Material.h"		// マテリアル
#include "Shader.h"			// シェーダー
#include "Text.h"			// テキスト
#include "Transform.h"		// トランスフォーム

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　		  入力一覧			　　//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"	// 入力名称
#include "KeyInput.h"		// キー入力
#include "MouseInput.h"		// マウス入力
#include "ScreenInput.h"	// 画面入力


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　		 C+lanクラス 　		　　//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "CalculationHit.h"	// 当たり判定の計算一覧
#include "Color.h"			// 色
#include "SceneManager.h"	// シーンマネージャー
#include "Time.h"			// 時間
#include "Vector2.h"		// ベクトル2
#include "Vector3.h"		// ベクトル3


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　		C++標準ライブラリ 　	//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <string>