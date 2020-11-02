#include"pch.h"
#include"Sprite.h"
#include"DeviceResources.h"
#include"GameContext.h"

Sprite::Sprite(const wchar_t* spriteName, std::string tagName)
	: m_deathFlag(false)
	, m_tagName(tagName)
{
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), spriteName,
		nullptr, this->m_sprite.GetAddressOf());
}


