#include"pch.h"
#include"ModelObject.h"
#include"GameContext.h"
#include<Effects.h>

ModelObject::ModelObject()
{
	this->m_deviceResources = GameContext().Get<DX::DeviceResources>();
}

ModelObject::~ModelObject()
{

}

//初期化
void ModelObject::Initialize()
{
	//コモンステートの作成
	this->m_state = std::make_unique<DirectX::CommonStates>(this->m_deviceResources->GetD3DDevice());
	//エフェクトファクトリーの生成
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(this->m_deviceResources->GetD3DDevice());
	//パスの設定
	factory->SetDirectory(this->m_pathName);
	//モデルデータの読み込み
	this->m_model = DirectX::Model::CreateFromCMO(this->m_deviceResources->GetD3DDevice(), this->m_fillName, *factory);
	//使い終わったエフェクトファクトリーの破棄
	delete factory;
}

//描画
void ModelObject::Render(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//描画
	this->m_model->Draw(this->m_deviceResources->GetD3DDeviceContext(), *this->m_state, world, view, proj);
}

