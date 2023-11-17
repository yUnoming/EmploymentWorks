// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_NetWorkManager.h"
#include "renderer.h"
#include "FileReader.h"

#include "yUno_MainManager.h"
#include "yUno_TimeManager.h"
#include "yUno_KeyInputManager.h"
#include "yUno_MouseInputManager.h"

#include "SampleScene.h"

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 using宣言 	    	  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace yUno_SystemManager;
using namespace PublicSystem;


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
bool yUno_MainManager::m_DemoPlay;
yUno_SceneManager*  yUno_MainManager::m_NowScene;


void yUno_MainManager::Init(Application* app)
{
    // ===== システムの初期化処理 ===== //
    // 時間
    yUno_TimeManager::Init();
    // ネットワーク
    yUno_NetWorkManager::Init();
    // レンダラー
    Renderer::Init(app);

    // ----- shader設定 ----- //
    // 各変数
    ID3D11VertexShader* VertexShader{};
    ID3D11PixelShader* PixelShader{};
    ID3D11InputLayout* VertexLayout{};

    // 頂点シェーダー、ピクセルシェーダ作成
    Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "Assets\\Shaders\\unlitTextureVS.cso");
    Renderer::CreatePixelShader(&PixelShader, "Assets\\Shaders\\unlitTexturePS.cso");

    // 入力レイアウト設定
    Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

    // シェーダ設定
    Renderer::GetDeviceContext()->VSSetShader(VertexShader, nullptr, 0);
    Renderer::GetDeviceContext()->PSSetShader(PixelShader, nullptr, 0);


    // ----- 標準フォント設定 ----- //
    FileReader::ReadTtfFile(L"Assets\\Fonts\\calibri.ttf", "Calibri");

    // ===== メインの初期化処理 ===== //
    // シーンを立ち上げる
    m_NowScene = new yUno_SceneManager();
    m_NowScene->LoadScene<SampleScene>();
}

void yUno_MainManager::UnInit()
{
    // ===== メインの初期化処理 ===== //
    // シーンの終了
    m_NowScene->UnInitBase();
    // シーンの削除
    delete m_NowScene;
    
    // ネットワーク終了
    yUno_NetWorkManager::UnInit();
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
    m_NowScene->UpdateBase();

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
    m_NowScene->DrawBase();

    // 描画の後処理
    Renderer::End();
}

