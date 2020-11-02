#include"pch.h"
#include"PlayState.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"
#include"GameContext.h"
#include"Player.h"
#include"Floor.h"
#include"Enemy.h"
#include"FruitsGenerator.h"
#include"Game.h"
#include"Adx2Le.h"
#include"SoundLoader.h"

//定数の初期化
const int PlayState::MAX_GAME_COUNT                        = 1800;
const DirectX::SimpleMath::Vector3 PlayState::TIME_POS     = DirectX::SimpleMath::Vector3(Game::WINDOW_W / 2, 50.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::TIMER_POS    = DirectX::SimpleMath::Vector3(325.0f, 0.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::P_ANIMAL_POS = DirectX::SimpleMath::Vector3(0.0f, 60.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::E_ANIMAL_POS = DirectX::SimpleMath::Vector3(0.0f, 140.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::P_APPLE_POS  = DirectX::SimpleMath::Vector3(63.0f, 60.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::E_APPLE_POS  = DirectX::SimpleMath::Vector3(63.0f, 140.0f, 0.0f);
const float PlayState::TIMER_SIZE                          = 0.2f;
const float PlayState::ANIMAL_SIZE                         = 0.08f;
const float PlayState::APPLE_SIZE						   = 0.08f;
const int PlayState::SOUND_NUM							   = 2;

PlayState::PlayState()
	: m_gameCount(MAX_GAME_COUNT)
{
}

PlayState::~PlayState()
{
	this->ResetUI();
}

//初期化
void PlayState::Initialize()
{
	//キーボードステートトラッカーを作成
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//時間表示クラスの生成
	this->m_timeDrawer = std::make_unique<NumDrawer>(this->TIME_POS);
	//床の生成
	std::unique_ptr<Floor> floor = std::make_unique<Floor>();
	GameContext::Get<GameObjectManager>()->Add(std::move(floor));
	//プレイヤーの生成
	std::unique_ptr<Player> player = std::make_unique<Player>();
	//カメラの作成
	this->m_followCamera = std::make_unique<FollowCamera>(player->GetPos());
	//プレイヤーの登録
	GameContext::Get<GameObjectManager>()->Add(std::move(player));
	//フルーツジェネレーターの生成
	std::unique_ptr<FruitsGenerator> fruitsGenerator = std::make_unique<FruitsGenerator>();
	GameContext::Get<GameObjectManager>()->Add(std::move(fruitsGenerator));
	//敵の生成
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	GameContext::Get<GameObjectManager>()->Add(std::move(enemy));
	//スコア表示クラスの生成
	this->m_scoreDrawer = std::make_unique<ScoreDrawer>();
	//UIの生成
	this->InitializeUI();
	//音の生成
	GameContext::Get<SoundLoader>()->LoadBattle();
	GameContext::Get<Adx2Le>()->Play(0);
}

//更新
void PlayState::Update(float elapsedTime)
{
	elapsedTime;
	//キーボードを取得
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//キーボードステートトラッカーの更新
	this->m_tracker->Update(key);
	//ゲーム時間の更新
	this->m_gameCount--;
	//制限時間で勝敗判定
	if (this->m_gameCount <= 0)
	{
		this->m_gameCount = this->MAX_GAME_COUNT;
		this->WinJudgment();
	}
	//更新された時間を登録
	this->m_timeDrawer->SetNowNum(static_cast<int>(this->m_gameCount / 60));
	this->m_timeDrawer->Update();

	//デバッグ用 
	if (key.IsKeyDown(DirectX::Keyboard::V))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Victory");
		//音の停止
		GameContext::Get<Adx2Le>()->Stop();
	}
	if (key.IsKeyDown(DirectX::Keyboard::D))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Defeat");
		//音の停止
		GameContext::Get<Adx2Le>()->Stop();
	}
	if (key.IsKeyDown(DirectX::Keyboard::T))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("TieGame");
		//音の停止
		GameContext::Get<Adx2Le>()->Stop();
	}

	//オブジェクトの更新
	GameContext::Get<GameObjectManager>()->Update(elapsedTime);

	//スコアの更新
	this->m_scoreDrawer->Update();

	//プレイヤーを取得
	std::vector<GameObject*> target = GameContext::Get<GameObjectManager>()->Find("Player");
	for (std::vector<GameObject*>::iterator iter = target.begin(); iter != target.end(); iter++)
	{
		//カメラの更新
		this->m_followCamera->Update((*iter)->GetPos() + FollowCamera::EYE_POS, (*iter)->GetPos());
	}
}

//描画
void PlayState::Render(const DirectX::SimpleMath::Matrix& proj)
{
	//ゲームオブジェクトの描画
	GameContext::Get<GameObjectManager>()->Render(this->m_followCamera->GetView(), proj);
	//UIの表示
	this->UIRender();
	//スコアの表示
	this->m_scoreDrawer->Render();
	//時間の表示
	this->m_timeDrawer->Render();
}

//終了処理
void PlayState::Finalize()
{
	this->m_tracker.reset();
	GameContext::Get<GameObjectManager>()->DeleteAll();
}

//勝敗判定
void PlayState::WinJudgment()
{
	if (GameContext::Get<ScoreManager>()->GetPlayerScore() > GameContext::Get<ScoreManager>()->GetEnemyScore())
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Victory");
	}
	else if (GameContext::Get<ScoreManager>()->GetPlayerScore() < GameContext::Get<ScoreManager>()->GetEnemyScore())
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Defeat");
	}
	else
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("TieGame");
	}
	//音の停止
	GameContext::Get<Adx2Le>()->Stop();
}

//UIの表示
void PlayState::UIRender()
{	
	RECT srcRect = { 0,0,Batch::SPRITE_WIDTH, Batch::SPRITE_HEIGHT };
	//UIの表示
	this->m_timerDrawer->Render(&srcRect, this->TIMER_SIZE);
	this->m_pAnimalDrawer->Render(&srcRect, this->ANIMAL_SIZE);
	this->m_eAnimalDrawer->Render(&srcRect, this->ANIMAL_SIZE);
	this->m_pAppleDrawer->Render(&srcRect, this->APPLE_SIZE);
	this->m_eAppleDrawer->Render(&srcRect, this->APPLE_SIZE);
}

//UIのリセット
void PlayState::ResetUI()
{
	this->m_timerDrawer.reset();
	this->m_pAnimalDrawer.reset();
	this->m_eAnimalDrawer.reset();
	this->m_pAppleDrawer.reset();
	this->m_eAppleDrawer.reset();
}

//UIの初期化
void PlayState::InitializeUI()
{
	//タイマー表示の生成
	this->m_timerDrawer = std::make_unique<Batch>("Timer");
	this->m_timerDrawer->SetPos(this->TIMER_POS);
	//動物表示の生成
	this->m_pAnimalDrawer = std::make_unique<Batch>("Animal1");
	this->m_pAnimalDrawer->SetPos(this->P_ANIMAL_POS);
	this->m_eAnimalDrawer = std::make_unique<Batch>("Animal2");
	this->m_eAnimalDrawer->SetPos(this->E_ANIMAL_POS);
	//林檎表示の作成
	this->m_pAppleDrawer = std::make_unique<Batch>("Apple");
	this->m_pAppleDrawer->SetPos(this->P_APPLE_POS);
	this->m_eAppleDrawer = std::make_unique<Batch>("Apple");
	this->m_eAppleDrawer->SetPos(this->E_APPLE_POS);
}

