#include"pch.h"
#include"Ground.h"
#include"GameContext.h"

//定数の初期化
const DirectX::SimpleMath::Vector3 Ground::SIZE = DirectX::SimpleMath::Vector3(25.0f, 1.0f, 14.0f);

Ground::Ground()
{
	this->m_tagName = "Ground";
}

//初期化
void Ground::Initialize()
{
	//posの設定
	this->m_pos = DirectX::SimpleMath::Vector3::Zero;
	//コンテキストの作成
	this->m_deviceResources = GameContext::Get<DX::DeviceResources>();
	//ジオメトリックプリミティブの作成
	this->m_geometricPrimitive = DirectX::GeometricPrimitive::CreateBox(this->m_deviceResources->GetD3DDeviceContext(), this->SIZE);
}

//更新
void Ground::Update(float elapsedTime)
{
	elapsedTime;
}

//描画
void Ground::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->MatrixToVector();
	this->m_geometricPrimitive->Draw(this->m_world, view, proj, DirectX::Colors::White);
}


