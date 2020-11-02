#include"pch.h"
#include"SpriteManager.h"
#include"GameContext.h"
#include"DeviceResources.h"
#include<functional>

SpriteManager::SpriteManager()
	: m_spriteList()
{
}

SpriteManager::~SpriteManager()
{
	this->DeleteAll();
}

//初期化
void SpriteManager::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext().Get<DX::DeviceResources>();
	// エフェクトの作成
	this->m_basicEffect = std::make_unique<DirectX::BasicEffect>(deviceResources->GetD3DDevice());
	this->m_basicEffect->SetTextureEnabled(true);
	this->m_basicEffect->SetVertexColorEnabled(true);
	// 入力レイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	this->m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	deviceResources->GetD3DDevice()->CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements,
		DirectX::VertexPositionColorTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());
	//プリミティブバッチの作成
	this->m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(deviceResources->GetD3DDeviceContext());
}

//指定したタグ名と合致したスプライトを返す
Sprite* SpriteManager::Find(std::string tagName)
{
	Sprite* result = nullptr;
	for (PSprite& sprite : this->m_spriteList)
	{
		if (sprite->GetTagName() == tagName)
		{
			result = sprite.get();
		}
	}
	return result;
}

//更新
void SpriteManager::Update()
{
	this->DestroySprite();
}

//死亡フラグが立っているものを削除する
void SpriteManager::DestroySprite()
{
	//条件に合うものをすべて削除する
	this->m_spriteList.remove_if(std::mem_fn(&Sprite::GetDeathFlag));
}

//全ての要素を削除する
void SpriteManager::DeleteAll()
{
	for (PSprite& sprite : this->m_spriteList)
	{
		if (sprite != nullptr)
		{
			sprite->Death();
		}
	}
	this->DestroySprite();
}

//スプライトをリストに追加する
void SpriteManager::Add(PSprite&& sprite)
{
	this->m_spriteList.push_back(std::move(sprite));
}
