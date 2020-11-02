#include"pch.h"
#include"TitleState.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"
#include"GameContext.h"
#include"Adx2Le.h"
#include"SoundLoader.h"

//定数の初期化
const DirectX::SimpleMath::Vector3 TitleState::MESSAGE_POS = DirectX::SimpleMath::Vector3(0.0f, -0.3f, 0.0f);

TitleState::TitleState()
{
}

TitleState::~TitleState()
{
}

//初期化
void TitleState::Initialize()
{
	//カメラの生成
	this->m_camera = std::make_unique<FixedPointCamera>();
	//キーボードステートトラッカーを作成
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//スプライトの読み込み
	this->m_spriteReader = std::make_unique<SpriteReader>();
	this->m_spriteReader->Reading();
	//タイトルスプライトの生成
	this->m_titleDrawer = std::make_unique<SpriteDrawer>(10.0f);
	this->m_titleDrawer->Initialize("Title");
	this->m_titleDrawer->SetBillBoard(this->m_camera->GetEye(), this->m_camera->GetUp());
	//案内表示の作成
	this->m_nextMessage = std::make_unique<NextMessage>("Enter", this->m_camera->GetEye(), this->m_camera->GetUp(), this->MESSAGE_POS);
	//初回でBGM再生
	GameContext::Get<SoundLoader>()->LoadTitle();
	GameContext::Get<Adx2Le>()->Play(0);
}

//更新
void TitleState::Update(float elapsedTime)
{
	elapsedTime;
	//キーボードを取得
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//キーボードステートトラッカーの更新
	this->m_tracker->Update(key);
	//メッセージの更新
	this->m_nextMessage->Update();

	

	if (key.IsKeyDown(DirectX::Keyboard::Enter))
	{
		//プレイステートへ
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Play");
		//サウンドの停止
		GameContext::Get<Adx2Le>()->Stop();
	}
}

//描画
void TitleState::Render(const DirectX::SimpleMath::Matrix& proj)
{
	this->m_titleDrawer->Render(this->m_camera->GetView(), proj);
	this->m_nextMessage->Render(this->m_camera->GetView(), proj);
}

//終了処理
void TitleState::Finalize()
{
	this->m_tracker.reset();
}
