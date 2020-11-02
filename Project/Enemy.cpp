#include"pch.h"
#include"Enemy.h"
#include"GameObjectManager.h"
#include"GameContext.h"
#include"CollisionManager.h"
#include"ScoreManager.h"
#include"ICollider.h"
#include"EFall.h"
#include"ERunning.h"
#include"ESearch.h"
#include"EStanding.h"
#include"Fruits.h"
#include"Floor.h"

//定数の初期化
const float Enemy::GRAVITY = -0.07f;
const float Enemy::SIZE    = 0.003f;
const DirectX::SimpleMath::Vector3 Enemy::START_POS     = DirectX::SimpleMath::Vector3(-3.f, 4.f, 0.f);
const DirectX::SimpleMath::Vector3 Enemy::COLLIDER_SIZE = DirectX::SimpleMath::Vector3(0.20f, 0.25f, 0.20f);

Enemy::Enemy()
	: m_angle(0)
{
	this->m_tagName = "Enemy";
	this->SetPos(this->START_POS);
}

Enemy::~Enemy()
{
	delete this->m_boxCollider;
}

//初期化
void Enemy::Initialize()
{
	//モデルの作成
	this->m_modelObject = std::make_unique<ModelObject>();
	this->m_modelObject->SetPathName(L"Resources/Models");
	this->m_modelObject->SetFillName(L"Resources/Models/Animal2.cmo");
	this->m_modelObject->Initialize();

	//状態の初期化
	EStanding::Get()->Initialize(this);
	ESearch::Get()->Initialize(this);
	ERunning::Get()->Initialize(this);
	EFall::Get()->Initialize(this);

	//最初の状態を設定
	this->ChangeState(EStanding::Get());

	//スコアの作成
	this->m_score = std::make_unique<Score>();

	//Colliderの設定
	this->m_boxCollider = new BoxCollider();

	//スタート地点を記憶
	this->m_startPos = this->m_pos;
}

//更新
void Enemy::Update(float elapsedTime)
{
	//重力を加える
	this->m_pos.y += this->GRAVITY;
	//Colliderの設定
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
	this->m_collider = this->m_boxCollider;

	//当たり判定
	this->CollisionWithFloor();
	this->CollisionWithFruits();

	//状態の更新
	this->m_currentState->Update(elapsedTime);

	//posの更新
	this->m_pos += this->m_vel;

	//スコアの登録
	GameContext::Get<ScoreManager>()->SetEnemyScore(this->m_score->GetScore());
}

//描画
void Enemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->m_world *= DirectX::SimpleMath::Matrix::CreateScale(this->SIZE);
	this->m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180.0f));
	//ずれている分の補正
	this->m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(-DirectX::XM_PI/2.0f - this->m_angle);
	this->MatrixToVector();
	this->m_modelObject->Render(this->m_world, view, proj);
}

//あたったときの処理
bool Enemy::CollisionWithFruits()
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
				return true;
			}
		}
	}
	return false;
}

//あたったときの処理
bool Enemy::CollisionWithFloor()
{
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
				return true;
			}
		}
	}
	return false;
}


