#include"pch.h"
#include"ResultState.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"
#include"SpriteManager.h"
#include"GameContext.h"

//コンストラクタ
ResultState::ResultState()
	: m_playerPos(DirectX::SimpleMath::Vector3(0.0f, 0.5f, 0.0f))
{
}

//デストラクタ
ResultState::~ResultState()
{
}

//初期化
void ResultState::Initialize()
{
	//キーボードステートトラッカーを作成
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//カメラの生成
	this->m_camera = std::make_unique<FixedPointCamera>();
	//床の生成
	std::unique_ptr<Ground> ground = std::make_unique<Ground>();
	GameContext::Get<GameObjectManager>()->Add(std::move(ground));
	
	this->m_message = std::make_unique<SpriteDrawer>(5.0f);
	this->m_message->Initialize("ResultMessage",DirectX::SimpleMath::Vector3(0.f,0.f,0.f));
	this->m_message->SetBillBoard(this->m_camera->GetEye(), this->m_camera->GetUp());
	
	this->m_test = std::make_unique<Batch>("Number");
	this->m_test->SetPos(DirectX::SimpleMath::Vector3(5.0f, 5.0f, 0.0f));	
}

//更新
void ResultState::Update(float elapsedTime)
{
	//キーボードを取得
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//キーボードステートトラッカーの更新
	this->m_tracker->Update(key);

	if (key.IsKeyDown(DirectX::Keyboard::B))
	{
		//タイトルステートへ
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Title");
	}

	GameContext::Get<GameObjectManager>()->Update(elapsedTime);

	
}

//描画
void ResultState::Render(const DirectX::SimpleMath::Matrix& proj)
{
	GameContext::Get<GameObjectManager>()->Render(this->m_camera->GetView(), proj);
	this->m_message->Render(this->m_camera->GetView(), proj);

	//this->m_timeDrawer->Render(this->m_camera->GetView(), proj);
	RECT srcRect = { 48,0,72,24 };
	this->m_test->Render(&srcRect);
}

//終了処理
void ResultState::Finalize()
{
	this->m_tracker.reset();
	GameContext::Get<GameObjectManager>()->DeleteAll();
}
