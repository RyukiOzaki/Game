//‰æ‘œ‚ÌƒNƒ‰ƒX
#pragma once
#include<string>
#include<wrl.h>
#include<WICTextureLoader.h>

class Sprite
{
private:
	std::string										 m_tagName;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_sprite;
	bool											 m_deathFlag;

public:
	Sprite(const wchar_t* spriteName, std::string tagName);
	~Sprite() = default;

public:
	void SetTagName(std::string tagName);
	ID3D11ShaderResourceView* GetSprite();
	std::string GetTagName();
	bool GetDeathFlag();
	void Death();
};

inline void Sprite::SetTagName(std::string tagName)
{
	this->m_tagName = tagName;
}

inline ID3D11ShaderResourceView* Sprite::GetSprite()
{
	return this->m_sprite.Get();
}

inline std::string Sprite::GetTagName()
{
	return this->m_tagName;
}

inline bool Sprite::GetDeathFlag()
{
	return this->m_deathFlag;
}

inline void Sprite::Death()
{
	this->m_deathFlag = true;
}