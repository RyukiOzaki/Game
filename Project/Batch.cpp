#include"pch.h"
#include"Batch.h"
#include"GameContext.h"
#include"DeviceResources.h"
#include"SpriteManager.h"
#include<CommonStates.h>

//定数の初期化
const int Batch::SPRITE_WIDTH     = 800;
const int Batch::SPRITE_HEIGHT    = 600;

Batch::Batch(std::string name)
	: m_pos(DirectX::SimpleMath::Vector3::Zero)
{
	DX::DeviceResources *deviceResources = GameContext::Get<DX::DeviceResources>();
	this->m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceResources->GetD3DDeviceContext());
	this->m_texture = GameContext::Get<SpriteManager>()->Find(name);
}

//描画
void Batch::Render()
{
	this->m_spriteBatch->Begin();
	this->m_spriteBatch->Draw(this->m_texture->GetSprite(), this->m_pos);
	this->m_spriteBatch->End();
}

//描画(切り取り位置)
void Batch::Render(RECT const* sourceRectangle, float scale, float rotation, DirectX::FXMVECTOR color, DirectX::FXMVECTOR origin)
{
	this->m_spriteBatch->Begin();
	this->m_spriteBatch->Draw(this->m_texture->GetSprite(), this->m_pos, sourceRectangle, color, rotation, origin, scale);
	this->m_spriteBatch->End();
}

//終了処理
void Batch::Reset()
{
	this->m_spriteBatch.reset();
}

