#include"pch.h"
#include"Floor.h"
#include"GameContext.h"

//定数の初期化
const DirectX::SimpleMath::Vector3 Floor::SIZE = DirectX::SimpleMath::Vector3(15.0f, 1.0f, 15.0f);
const DirectX::SimpleMath::Vector3 Floor::COLLIDER_SIZE = DirectX::SimpleMath::Vector3(15.0f / 2, 0.75f, 15.0f / 2);

Floor::Floor()
{
	this->m_tagName = "Floor";
}

Floor::~Floor()
{
	delete this->m_boxCollider;
}

//初期化
void Floor::Initialize()
{
	//posの設定
	this->m_pos = DirectX::SimpleMath::Vector3(0.f, -1.0f, 0.f);
	//コンテキストの作成
	this->m_deviceResources = GameContext::Get<DX::DeviceResources>();
	//ジオメトリックプリミティブの作成
	this->m_geometricPrimitive = DirectX::GeometricPrimitive::CreateBox(this->m_deviceResources->GetD3DDeviceContext(), this->SIZE);
	//コライダーの生成
	this->m_boxCollider = new BoxCollider();
}

//更新
void Floor::Update(float elapsedTime)
{
	elapsedTime;
	//Colliderの設定
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
	this->m_collider = this->m_boxCollider;
}

//描画
void Floor::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->MatrixToVector();
	this->m_geometricPrimitive->Draw(this->m_world, view, proj, DirectX::Colors::GreenYellow);
}



