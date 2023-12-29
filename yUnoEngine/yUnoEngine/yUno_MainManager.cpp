// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_NetWorkManager.h"
#include "yUno_MainManager.h"
#include "yUno_TimeManager.h"
#include "yUno_KeyInputManager.h"
#include "yUno_MouseInputManager.h"
#include "yUno_CollisionManager.h"

#include "renderer.h"
#include "FileReader.h"


#include "SampleScene.h"
#include "EditScene.h"

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 using宣言 	    	  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace yUno_SystemManager;
using namespace PublicSystem;


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
bool yUno_MainManager::m_demoPlay;


void yUno_MainManager::Init(Application* app)
{
    // ===== システムの初期化処理 ===== //
    // 時間
    yUno_TimeManager::Init();
    // ネットワーク
    yUno_NetWorkManager::Init();
    // レンダラー
    Renderer::Init(app);

    // ----- 標準フォント設定 ----- //
    FileReader::ReadTtfFile(L"Assets\\Fonts\\calibri.ttf", "Calibri");

    // ===== メインの初期化処理 ===== //
    // シーンを立ち上げる
    yUno_SceneManager::InitScene();
}

void yUno_MainManager::UnInit()
{
    // ===== メインの初期化処理 ===== //
    // ネットワーク終了
    yUno_NetWorkManager::UnInit();

    // シーンの終了
    yUno_SceneManager::UnInitScene();
}

void yUno_MainManager::Update()
{
    // ===== システムの更新処理 ===== //
    // 時間
    yUno_TimeManager::Update();

    // キー入力
    yUno_KeyInputManager::Update();

    // ===== メインの更新処理 ===== //
    // ----- デモプレイの切り替え----- //
    // 仮）Enterキーが押された？
    //if (KeyInput::GetKeyDown_Trigger(KeyName::Enter))
    //    m_DemoPlay ^= true;  // デモプレイの状態を切り替える

    // シーンの更新
    yUno_SceneManager::UpdateScene();
    // 当たり判定の計算
    yUno_CollisionManager::CalculationCollision();

    // 現在のキー入力状態を保存する
    yUno_KeyInputManager::KeepNowKeyInfo();
    // 現在のマウス入力状態を保存する
    yUno_MouseInputManager::KeepNowMouseState();
}

void yUno_MainManager::Draw()
{
    // ===== メインの描画処理 ===== //
    // 描画の前処理
    Renderer::Begin();

    // シーンの描画
    yUno_SceneManager::DrawScene();

    // 描画の後処理
    Renderer::End();
}

