//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/SceneManager.h"
#include "Framework/Tween/TweenManager.h"
#include "Framework/Renderer.h"
#include "Game/SkyBox/SkyBox.h"
#include "Game/Sea/Sea.h"
#include "Game/Parameters/Parameters.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Game/GameConfig/GameConfig.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <Framework/Microsoft/DebugDraw.h>
#include "Framework/DebugRenderer.h"


extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    // 共有リソースのインスタンスを取得する
    m_commonResources = CommonResources::GetInstance();

    m_collisionVisitor = CollisionVisitor::GetInstance();

    // デバイスリソースを作成する
    m_deviceResources = std::make_unique<DX::DeviceResources>(
        DXGI_FORMAT_B8G8R8A8_UNORM,     // バックバッファのフォーマットを指定する
        DXGI_FORMAT_D24_UNORM_S8_UINT   // ステンシルバッファを使用する
    );
    // デバイスの通知先を設定する
    m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// Direct3Dリソースを初期化する
void Game::Initialize(HWND window, int width, int height)
{

    // 時間測定用のエイリアス
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    using Duration = std::chrono::duration<float>;

    // --- 計算開始 ---
    TimePoint startTime = Clock::now();
   
    // デバイスリソース初期化================================================

        // ウィンドウハンドルを設定する
    m_hWnd = window;
    // デバイスリソースを生成する
    m_deviceResources->CreateDeviceResources();
    // デバイスに依存したリソースを生成する
    CreateDeviceDependentResources();
    // ウィンドウサイズに依存したリソースを生成する
    m_deviceResources->CreateWindowSizeDependentResources();
    // ウィンドウサイズに依存したリソースを生成する
    CreateWindowSizeDependentResources();

    // デバイスとコンテキストを設定
    m_device = m_deviceResources->GetD3DDevice();
    m_context = m_deviceResources->GetD3DDeviceContext();

    // デバイスリソースを共有リソースに設定
    m_commonResources->SetDeviceResources(m_deviceResources.get());

    // タイマー設定を変更する   
    // m_timer.SetFixedTimeStep(true);
    // タイマーにターゲット経過秒(60FPS)を設定する
    // m_timer.SetTargetElapsedSeconds(1.0 / 60);

    // スクリーンサイズを設定
    m_commonResources->SetScreenSize(width, height);
    // 顧問ステートを設定
    m_commonResources->SetCommonStates(m_commonStates.get());
    // タイマーを設定
    m_commonResources->SetStepTimer(&m_timer);
 
    // リソースをロードする
    Resources::GetInstance()->LoadResource();
    // ゲームデータ
    m_gameConfig = GameConfig::GetInstance();
  
    // 海の作成
    m_sea = std::make_unique<Sea>();
    m_sea->Initialize();
    m_commonResources->SetSea(m_sea.get());

    // スカイボックスの作成
    m_skyBox = std::make_unique<SkyBox>();
    m_skyBox->Initialize();
    m_commonResources->SetSkyBox(m_skyBox.get());

 
    // パラメーターのインスタンスを取得する
    m_parameters = Parameters::GetInstance();
    m_parameters->LoadFromJson("Resources/Json/JSON/Parameters.json");

    // 環境光の初期化
    AmbientLight::GetInstance()->Initialize();
 

    // 管理者達の生成========================================================

    // 描画処理の作成
    m_renderer = std::make_unique<Renderer>();
    m_commonResources->SetRenderer(m_renderer.get());

    // シーンマネージャーの作成、インスタンスを取得する
    m_sceneManager = SceneManager::GetInstance();
    // インプットマネージャーの生成、インスタンスを取得する
    m_inputManager = InputManager::GetInstance();
    m_inputManager->GetMouse()->SetWindow(window);
    // オーディオマネージャーの生成、インスタンスを取得する
    m_audioManager = AudioManager::GetInstance();
    m_audioManager->Initialize();
    // Tweenマネージャーの作成、インスタンスを取得する
    m_tweenManager = TweenManager::GetInstance();
    

    // ImGuiの初期化========================================================

        //  バージョンの確認
    IMGUI_CHECKVERSION();
    //  コンテキストの作成
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // キーボードによるナビゲーションの有効化
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // コントローラーによるナビゲーションの有効化
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // マルチビューポート有効化
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // ドッキング有効化
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 20.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

    //  Win32用の初期化
    ImGui_ImplWin32_Init(window);
    //  DirectX11用の初期化
    ID3D11Device* device = m_deviceResources->GetD3DDevice();
    ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();
    ImGui_ImplDX11_Init(device, context);

    // シーンの初期化処理
    m_sceneManager->Initialize();

    // --- 計算終了 ---
    TimePoint endTime = Clock::now();
    Duration elapsed = endTime - startTime;
    // 計算時間を取得
    m_time = elapsed.count();

    // デバッグの時のみ作成
#ifdef _DEBUG

    // ベーシックエフェクトを作成
    m_basicEffect = std::make_unique<DirectX::BasicEffect>(
        m_deviceResources->GetD3DDevice()
    );
    // 頂点カラーを有効にする
    m_basicEffect->SetVertexColorEnabled(true);
    // テクスチャを無効にする
    m_basicEffect->SetTextureEnabled(false);
    void const* shaderByteCode;
    size_t byteCodeLength;
    // 頂点シェーダーを取得する
    m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
    // 入力レイアウトを生成する
    m_device->CreateInputLayout(
        DirectX::VertexPositionColor::InputElements,
        DirectX::VertexPositionColor::InputElementCount,
        shaderByteCode, byteCodeLength,
        m_inputLayout.ReleaseAndGetAddressOf()
    );
    //	スプライトバッチの作成
    m_spriteBatch = std::make_unique<SpriteBatch>(
       m_context
    );
    //	スプライトフォントの作成
    m_spriteFont = std::make_unique<SpriteFont>(
        m_device,
        L"Resources/Fonts/SegoeUI_18.spritefont"
    );
    // プリミティブバッチの作成
    m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(
        m_deviceResources->GetD3DDeviceContext()
    );

    m_debugRenderer = DebugRenderer::GetInstance();
#endif
}

#pragma region Frame Update
// ゲームループを実行する
void Game::Tick()
{
    m_timer.Tick([&]()
        {
            Update(m_timer);
        });
    // 描画する
    Render();
}

// ワールドを更新する
void Game::Update(DX::StepTimer const& timer)
{
    (void)timer;

    m_sceneManager->CheckChageScene();

    m_inputManager->Update();

    m_audioManager->Update(timer);

    m_tweenManager->Update();

    // 環境光の初期化
    AmbientLight::GetInstance()->Update((float)timer.GetElapsedSeconds());

    // シーンの更新処理
    m_sceneManager->Update();

    if (m_sceneManager->GetIsGameExit())
        ExitGame();
}
#pragma endregion

#pragma region Frame Render
// シーンを描画する
void Game::Render()
{
    // 描画可能でない場合は復帰する
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    // バックバッファをクリアする
    Clear();

    // PIX開始イベント
    m_deviceResources->PIXBeginEvent(L"Render");

    // スカイボックスを更新する
    m_skyBox->Update(
        m_commonResources->GetViewMatrix(),
        m_commonResources->GetProjectionMatrix()
    );

    //  新フレームの開始
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigViewportsNoTaskBarIcon = false; // OSのタスクバーにアイコンを表示しない
    io.ConfigViewportsNoDecoration = false; // OSウィンドウの枠を消す

    // スカイボックスを描画
    m_skyBox->Render(m_context, m_commonStates.get());
    // 海の描画
    m_sea->Render(m_renderer->GetShadowMap());
    // シーンの描画処理
    m_sceneManager->Render();

    // デバッグ描画
#ifdef _DEBUG
    wchar_t stringBuffer[128];

    // 画面サイズ
    int screenWidth, screenHeight;
    // 画面サイズを取得する
    GetDefaultSize(screenWidth, screenHeight);

    // 射影行列を生成する 
    DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        DirectX::XMConvertToRadians(45.0f),
        screenWidth / (float)screenHeight,
        0.1f,
        100.0f
    );

    // ビュー行列を設定する
    m_basicEffect->SetView(m_commonResources->GetViewMatrix());
    // プロジェクション行列を設定する
    m_basicEffect->SetProjection(projection);
    // ワールド行列を設定する
    m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
    // コンテキストを設定する
    // 深度ステンシルの設定（深度テストを有効化）
    m_context->OMSetDepthStencilState(nullptr, 0); // デフォルトの深度ステートを使用
    m_basicEffect->Apply(m_context);
    // 入力レイアウトを設定する
    m_context->IASetInputLayout(m_inputLayout.Get());

    // グリッドを描画
    m_primitiveBatch->Begin();
    DX::DrawGrid(m_primitiveBatch.get(),
        { 5.0f, 0.0f, 0.0f },              // 横軸
        { 0.0f,0.0f,5.0f },                // 縦軸
        DirectX::SimpleMath::Vector3::Zero, // 原点
        10,                                 // 横分割数
        10                                  // 縦分割数
    );

    // 当たり判定の境界を描画
    m_collisionVisitor->DebugDraw(m_primitiveBatch.get());

    m_debugRenderer->Render(m_primitiveBatch.get());

    m_primitiveBatch->End();


    m_spriteBatch->Begin();
    // FPS
    swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"FPS : %d", m_timer.GetFramesPerSecond());
    m_spriteFont->DrawString(m_spriteBatch.get(), stringBuffer, SimpleMath::Vector2(10, 20), Colors::White, 0.0f, SimpleMath::Vector2::Zero, 0.8f);
    // スクリーンサイズ
    swprintf(stringBuffer, sizeof(stringBuffer) / sizeof(wchar_t), L"ScreenW : %d ScreenH : %d", screenWidth, screenHeight);
    m_spriteFont->DrawString(m_spriteBatch.get(), stringBuffer, SimpleMath::Vector2(10, 40), Colors::White, 0.0f, SimpleMath::Vector2::Zero, 0.8f);
    m_spriteBatch->End();
#endif

   
    //  ImGuiの描画処理
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        // TODO for OpenGL: restore current GL context.
    }

    // PIX終了イベント
    m_deviceResources->PIXEndEvent();
    // 新規フレームを描画する
    m_deviceResources->Present();
}

// バックバッファをクリアする
void Game::Clear()
{
    // ビューをクリアする
    auto context = m_deviceResources->GetD3DDeviceContext();
    // レンダーターゲットを取得する
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    // 深度ステンシルビューを取得する
    auto depthStencil = m_deviceResources->GetDepthStencilView();
    // レンダーターゲットビューをクリアする
    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    // 深度ステンシルビューをクリアする
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    // レンダーターゲットを設定する
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // スクリーンビューポートを取得する
    auto const viewport = m_deviceResources->GetScreenViewport();
    // ビューポートを設定する
    context->RSSetViewports(1, &viewport);
    // PIX終了イベント
    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// メッセージハンドラ
void Game::OnActivated()
{
    // ゲームがアクティブウィンドウになったときの処理を記述する
}

void Game::OnDeactivated()
{
    // ゲームが背景ウィンドウになった時の処理を記述する
}

void Game::OnSuspending()
{
    // ゲームの実行中に電源が停止した時の処理を記述する
}

void Game::OnResuming()
{
    // 経過時間をリセットする
    m_timer.ResetElapsedTime();
}

// ウィンドウが移動したときの処理を記述する
void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

// ウィンドウサイズが変更された時の処理を記述する
void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;
    // ウィンドウサイズに依存したリソースを生成する
    CreateWindowSizeDependentResources();

    // ゲームウィンドウのサイズが変更された時の処理を記述する
    m_commonResources->SetScreenSize(width, height);
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // 規定のウィンドウサイズ
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// デバイスに依存したリソースを生成する
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    //	コモンステートの作成
    m_commonStates = std::make_unique<DirectX::CommonStates>(device);
    // デバイスに依存したオブジェクトを初期化する
    int width, height;
    // ウィンドウの既定サイズを取得する
    GetDefaultSize(width, height);
    // 「ウィンドウハンドル」「幅」「高さ」を設定する
    m_deviceResources->SetWindow(m_hWnd, width, height);
}

// ウィンドウサイズが変更されたイベントによりメモリリソースを確保する
void Game::CreateWindowSizeDependentResources()
{
    // ウィンドウサイズに依存したオブジェクトを初期化するコードを記述する
     // 出力サイズを取得する
    auto m_size = m_deviceResources->GetOutputSize();
    // アスペクト率を計算する
    float aspectRatio = float(m_size.right) / float(m_size.bottom);
    // 視野角を設定する
    float fovAngleY = 45.0f * DirectX::XM_PI / 180.0f;
    // アプリが縦向きまたはスナップビューのときに変更する
    if (aspectRatio < 1.0f) { fovAngleY *= 2.0f; }
    // 射影行列を生成する
    DirectX::SimpleMath::Matrix projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        fovAngleY,
        aspectRatio,
        0.1f,
        10000.0f
    );
    // 射影行列を設定する
    m_commonResources->SetProjectionMatrix(projection);
}

// デバイスロストが発生した時の処理を記述する
void Game::OnDeviceLost()
{
    // Direct3Dリソースをクリーンアップする処理を記述する
}

// デバイスが復帰した時の処理を記述する
void Game::OnDeviceRestored()
{
    // デバイスに依存したリソースを生成する
    CreateDeviceDependentResources();
    // ウィンドウサイズに依存したリソースを生成する
    CreateWindowSizeDependentResources();
}
// フルスクリーン対応
void Game::SetFullscreenState(BOOL value)
{
    m_full_screen = value;
    m_deviceResources->GetSwapChain()->SetFullscreenState(m_full_screen, nullptr);
    if (value) m_deviceResources->CreateWindowSizeDependentResources();
}

#pragma endregion
