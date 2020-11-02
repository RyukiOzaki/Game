#include"pch.h"
#include"Player.h"
#include"PRunning.h"
#include"PStanding.h"
#include"GameObjectManager.h"
#include"GameContext.h"
#include"CollisionManager.h"
#include"ScoreManager.h"
#include"PFall.h"
#include"Fruits.h"
#include"Floor.h"

//定数の初期化
const float Player::GRAVITY = -0.1f;
const float Player::SIZE    = 0.003f;
const float Player::FLOOR_Y = -0.5f;
const DirectX::SimpleMath::Vector3 Player::COLLIDER_SIZE = DirectX::SimpleMath::Vector3(0.20f, 0.15f, 0.20f);
const DirectX::SimpleMath::Vector3 Player::START_POS     = DirectX::SimpleMath::Vector3(0.f, 4.f, 0.f);

Player::Player()
{
	this->m_tagName = "Player";
}

Player::~Player()
{
	delete this->m_boxCollider;
}

//初期化
void Player::Initialize()
{
	//posの設定
	this->m_pos = this->START_POS;	
	//回転角の初期化
	this->m_rotation = DirectX::SimpleMath::Vector3::Zero;
	//回転速度の初期化
	this->m_rotateSpeed = 2.0f;
	//モデルの作成
	this->m_modelObject = std::make_unique<ModelObject>();
	this->m_modelObject->SetPathName(L"Resources/Models");
	this->m_modelObject->SetFillName(L"Resources/Models/animal.cmo");
	this->m_modelObject->Initialize();
	//キーボードステートトラッカーを作成
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//状態の初期化
	PStanding::Get()->Initialize(this);
	PRunning::Get()->Initialize(this);
	PFall::Get()->Initialize(this);
	//最初の状態を設定
	this->ChangeState(PStanding::Get());
	//スコアの作成
	this->m_score = std::make_unique<Score>();
	//Colliderの設定
	this->m_boxCollider = new BoxCollider();
	//スタート地点を記憶
	this->m_startPos = this->m_pos;
}

//更新
void Player::Update(float elapsedTime)
{
	//重力
	this->m_pos.y += this->GRAVITY;
	//Colliderの設定
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
	this->m_collider = this->m_boxCollider;
	
	//方向を設定
	this->SetAngle();

	//落ちたらFallへ
	if (this->m_pos.y < this->FLOOR_Y)
	{
		this->ChangeState(PFall::Get());
	}

	//現在の状態の更新
	this->m_currentState->Update(elapsedTime);

	//あたったときの処理
	if (this->m_currentState != PFall::Get())
	{
		this->OnCollision();
	}

	//スコアの登録
	GameContext::Get<ScoreManager>()->SetPlayerScore(this->m_score->GetScore());
}

//描画
void Player::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->m_world *= DirectX::SimpleMath::Matrix::CreateScale(this->SIZE);
	this->m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180.0f));    //モデルを反対に向ける
	this->m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(this->m_rotation.y));
	this->MatrixToVector();
	this->m_modelObject->Render(this->m_world, view, proj);
}

//あたったときの処理
void Player::OnCollision()
{
	//フルーツ配列の取得
	std::vector<GameObject*> fruits = GameContext::Get<GameObjectManager>()->Find("Fruits");
	//フルーツが一つ以上あるかの確認
	if (fruits.size() != 0)
	{
		for (std::vector<GameObject*>::iterator iter = fruits.begin(); iter != fruits.end(); iter++)
		{
			//出ているすべてのフルーツと当たり判定
			if (GameContext::Get<CollisionManager>()->DetectCollisionBoxToBox(*this->m_boxCollider,
				*dynamic_cast<Fruits*>((*iter))->GetBoxCollider()) == true)
			{
				//当たったフルーツが存在しなくなったら加算しない
				if ((*iter)->IsValid())
				{
					//得点の加算
					this->m_score->AddScore(1);
				}
				//当たったフルーツを削除
				(*iter)->Invalidate();
			}
		}
	}
	//床配列の取得
	std::vector<GameObject*> floor = GameContext::Get<GameObjectManager>()->Find("Floor");
	//床が一つ以上あるかの確認
	if (floor.size() != 0)
	{
		for (std::vector<GameObject*>::iterator iter = floor.begin(); iter != floor.end(); iter++)
		{
			//出ているすべての床と当たり判定
			if (GameContext::Get<CollisionManager>()->DetectCollisionBoxToBox(*this->m_boxCollider,
				*dynamic_cast<Floor*>((*iter))->GetBoxCollider()) == true)
			{
				this->m_pos.y = 0.0f;
			}
		}
	}
}

//方向を決定
void Player::SetAngle()
{
	//キーボードを取得
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//キーボードステートトラッカーの更新
	this->m_tracker->Update(key);
	//キー入力に応じてangleを変更
	if (key.IsKeyDown(DirectX::Keyboard::Right))
	{
		this->m_rotation.y = Direction::EAST;
	}
	if (key.IsKeyDown(DirectX::Keyboard::Left))
	{
		this->m_rotation.y = Direction::WEST;
	}
	if (key.IsKeyDown(DirectX::Keyboard::Up))
	{
		this->m_rotation.y = Direction::NORTH;
	}
	if (key.IsKeyDown(DirectX::Keyboard::Down))
	{
		this->m_rotation.y = Direction::SOUTH;
	}
}