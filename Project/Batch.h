//スプライトバッチでの画像表示クラス
#pragma once
#include"Sprite.h"
#include<SpriteBatch.h>
#include<simplemath.h>
#include<memory.h>
#include<wrl.h>
#include<WICTextureLoader.h>
#include<string>

class Batch
{
private:
	Sprite*												m_texture;
	std::unique_ptr<DirectX::SpriteBatch>				m_spriteBatch;
	DirectX::SimpleMath::Vector3						m_pos;

public:
	static const int									SPRITE_WIDTH;
	static const int									SPRITE_HEIGHT;

public:
	Batch(std::string name);
	~Batch() = default;

public:
	void Render();
	void Render(RECT const* sourceRectangle, float scale = 1.0f, float rotation = 0.0f, DirectX::FXMVECTOR color = DirectX::Colors::White, DirectX::FXMVECTOR origin = DirectX::g_XMZero);
	void Reset();
	void SetPos(DirectX::SimpleMath::Vector3 pos);
};

inline void Batch::SetPos(DirectX::SimpleMath::Vector3 pos)
{
	this->m_pos = pos;
}