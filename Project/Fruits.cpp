#include"pch.h"
#include"Fruits.h"
#include"GameContext.h"
#include"DeviceResources.h"
#include"GameObjectManager.h"
#include"CollisionManager.h"
#include"Floor.h"
#include<random>

//定数の初期化
const float Fruits::START_POS_Y  = 10.0f;
const float Fruits::GRAVITY		 = -0.1f;
const float Fruits::FALL_DIS	 = -3.0f;
const float	Fruits::MAX_RAND_POS = 9.0f;
const float	Fruits::MIN_RAND_POS = -9.0f;
const DirectX::SimpleMath::Vector3 Fruits::COLLIDER_SIZE = DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f);

Fruits::Fruits()
{
	this->m_tagName = "Fruits";
}

Fruits::~Fruits()
{
	delete this->m_boxCollider;
}

//初期化
void Fruits::Initialize()
{
	//コンテキストの作成
	auto context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	//ジオメトリックプリミティブの作成
	this->m_geometricPrimitive = DirectX::GeometricPrimitive::CreateGeoSphere(context, 0.3);
	//ランダムに位置を作る
	std::random_device seed_generator;
	std::mt19937 engine(seed_generator());
	std::uniform_real_distribution<float> randPosZ(this->MIN_RAND_POS, this->MAX_RAND_POS);
	std::uniform_real_distribution<float> randPosX(this->MIN_RAND_POS, this->MAX_RAND_POS);
	this->m_pos = DirectX::SimpleMath::Vector3(randPosX(engine), this->START_POS_Y, randPosZ(engine));
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->MatrixToVector();
	//コライダーの生成
	this->m_boxCollider = new BoxCollider();
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
}

//更新
void Fruits::Update(float elapsedTime)
{
	elapsedTime;
	//重力の設定
	this->m_vel.y = this->GRAVITY;
	//コライダーの更新
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
	this->m_collider = this->m_boxCollider;
	//当たり判定
	this->OnCollision();
	//最低位置まで行ったら消滅
	if (this->m_pos.y < this->FALL_DIS)
	{
		this->Invalidate();
	}
	//ポジションの更新
	this->m_pos += this->m_vel;
}

//描画
void Fruits::Render(const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->MatrixToVector();
	this->m_geometricPrimitive->Draw(this->m_world, view, proj, DirectX::Colors::Red);
}

//当たり判定
void Fruits::OnCollision()
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
				//this->m_pos.y = 0.05f;
				this->m_vel.y = 0.0f;
			}
		}
	}
}
