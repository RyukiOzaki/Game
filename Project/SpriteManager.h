//‰æ‘œ‚ğŠÇ—‚µ‚Ä‚¢‚éƒNƒ‰ƒX
#pragma once
#include<list>
#include<memory>
#include<Effects.h>
#include<PrimitiveBatch.h>
#include<GeometricPrimitive.h>
#include"Sprite.h"

class SpriteManager
{
private:
	using PSprite = std::unique_ptr<Sprite>;
	using SpriteList = std::list<PSprite>;
	SpriteList								  m_spriteList;
	std::unique_ptr<DirectX::BasicEffect>	  m_basicEffect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;

public:
	SpriteManager();
	~SpriteManager();

public:
	Sprite* Find(std::string tagName);
	DirectX::BasicEffect* GetBasicEffect();
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* GetPrimitiveBatch();
	ID3D11InputLayout* GetInputLayout();
	void Initialize();
	void Update();
	void DestroySprite();
	void DeleteAll();
	void Add(PSprite&& sprite);

};

inline DirectX::BasicEffect* SpriteManager::GetBasicEffect()
{
	return this->m_basicEffect.get();
}

inline DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* SpriteManager::GetPrimitiveBatch()
{
	return this->m_primitiveBatch.get();
}

inline ID3D11InputLayout* SpriteManager::GetInputLayout()
{
	return this->m_inputLayout.Get();
}