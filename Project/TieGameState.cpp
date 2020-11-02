#include"pch.h"
#include"TieGameState.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"
#include"ScoreManager.h"
#include"GameContext.h"
#include"Adx2Le.h"
#include"SoundLoader.h"

//定数の初期化
const DirectX::SimpleMath::Vector3 TieGameState::APPLE_POS   = DirectX::SimpleMath::Vector3(290.0f, 300.0f, 0.0f);
const DirectX::SimpleMath::Vector3 TieGameState::ANIMAL_POS  = DirectX::SimpleMath::Vector3(50.0f, 300.0f, 0.0f);
const DirectX::SimpleMath::Vector3 TieGameState::SCORE_POS   = DirectX::SimpleMath::Vector3(650.0f, 330.0f, 0.0f);
const DirectX::SimpleMath::Vector3 TieGameState::MESSAGE_POS = DirectX::SimpleMath::Vector3(-0.0f, -0.6f, 0.0f);
const float						   TieGameState::SCORE_SIZE  = 5.0f;
const float						   TieGameState::ANIMAL_SIZE = 0.3f;
const float						   TieGameState::APPLE_SIZE  = 0.3f;
//コンストラクタ
TieGameState::TieGameState()
{
}

//デストラクタ
TieGameState::~TieGameState()
{
}

//初期化
void TieGameState::Initialize()
{
	//カメラの生成
	this->m_camera = std::make_unique<FixedPointCamera>();
	//キーボードステートトラッカーを作成
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//画像の作成
	this->m_victory = std::make_unique<Batch>("TieGame");
	this->m_animal = std::make_unique<Batch>("Animal1");
	this->m_animal->SetPos(this->ANIMAL_POS);
	this->m_apple = std::make_unique<Batch>("Apple");
	this->m_apple->SetPos(this->APPLE_POS);
	//スコアの作成
	this->m_score = std::make_unique<NumDrawer>(this->SCORE_POS, this->SCORE_SIZE);
	//案内表示の作成
	this->m_nextMessage = std::make_unique<NextMessage>("Space", this->m_camera->GetEye(), this->m_camera->GetUp(), this->MESSAGE_POS);
	//初回でBGM再生
	GameContext::Get<SoundLoader>()->LoadResult();
	GameContext::Get<Adx2Le>()->Play(2);
}

//更新
void TieGameState::Update(float elapsedTime)
{
	elapsedTime;
	//キーボードを取得
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//キーボードステートトラッカーの更新
	this->m_tracker->Update(key);
	//スコアの更新
	this->m_score->SetNowNum(GameContext::Get<ScoreManager>()->GetPlayerScore());
	this->m_score->Update();
	//案内表示の更新
	this->m_nextMessage->Update();

	if (key.IsKeyDown(DirectX::Keyboard::Space))
	{
		//プレイステートへ
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Title");
		//サウンドの停止
		GameContext::Get<Adx2Le>()->Stop();
	}
}

//描画
void TieGameState::Render(const DirectX::SimpleMath::Matrix& proj)
{
	this->m_victory->Render();
	RECT srcRect = { 0,0,Batch::SPRITE_WIDTH, Batch::SPRITE_HEIGHT };
	this->m_animal->Render(&srcRect, this->ANIMAL_SIZE);
	this->m_apple->Render(&srcRect, this->APPLE_SIZE);
	this->m_score->Render();
	this->m_nextMessage->Render(this->m_camera->GetView(), proj);
}

//終了処理
void TieGameState::Finalize()
{
	this->m_tracker.reset();
}