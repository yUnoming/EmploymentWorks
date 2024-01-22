// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SystemNetWorkManager.h"
#include "SystemMainManager.h"
#include "SystemTimeManager.h"
#include "SystemKeyInputManager.h"
#include "SystemMouseInputManager.h"
#include "SystemCollisionManager.h"

#include "renderer.h"
#include "FileReader.h"

#include "EditScene.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
bool Ctlan::PrivateSystem::SystemManager::SystemMainManager::m_demoPlay;


void Ctlan::PrivateSystem::SystemManager::SystemMainManager::Init(Application* app)
{
    // ===== システムの初期化処理 ===== //
    // 時間
    SystemTimeManager::Init();
    // ネットワーク
    SystemNetWorkManager::Init();
    // レンダラー
    Renderer::Init(app);

    // ----- 標準フォント設定 ----- //
    FileReader::ReadTtfFile(L"Assets\\Fonts\\calibri.ttf", "Calibri");

    // ===== メインの初期化処理 ===== //
    // シーンを立ち上げる
    SystemSceneManager::InitScene();
}

void Ctlan::PrivateSystem::SystemManager::SystemMainManager::Uninit()
{
    // ===== メインの初期化処理 ===== //
    // ネットワーク終了
    SystemNetWorkManager::Uninit();

    // シーンの終了
    SystemSceneManager::UninitScene();
}

void Ctlan::PrivateSystem::SystemManager::SystemMainManager::Update()
{
    // ===== システムの更新処理 ===== //
    // 時間
    SystemTimeManager::Update();

    // キー入力
    SystemKeyInputManager::Update();

    // ===== メインの更新処理 ===== //
    // ----- デモプレイの切り替え----- //
    // 仮）Enterキーが押された？
    //if (KeyInput::GetKeyDown_Trigger(KeyName::Enter))
    //    m_DemoPlay ^= true;  // デモプレイの状態を切り替える

    // シーンの更新
    SystemSceneManager::UpdateScene();
    // 当たり判定の計算
    SystemCollisionManager::CalculationCollision();

    // 現在のキー入力状態を保存する
    SystemKeyInputManager::KeepNowKeyInfo();
    // 現在のマウス入力状態を保存する
    SystemMouseInputManager::KeepNowMouseState();
}

void Ctlan::PrivateSystem::SystemManager::SystemMainManager::Draw()
{
    // ===== メインの描画処理 ===== //
    // 描画の前処理
    Renderer::Begin();

    // シーンの描画
    SystemSceneManager::DrawScene();

    // 描画の後処理
    Renderer::End();
}

