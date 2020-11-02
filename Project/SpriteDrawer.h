//プリミティブバッチでの画像表示クラス
#pragma once
#include"Sprite.h"
#include"GameContext.h"
#include"SpriteManager.h"
#include"DeviceResources.h"
#include<CommonStates.h>
#include<simplemath.h>
#include<string>
#include<Effects.h>
#include<PrimitiveBatch.h>
#include<VertexTypes.h>

class SpriteDrawer
{
protected:
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Matrix  m_billboard;
	float						 m_alpha;
	float						 m_scale;
	Sprite*						 m_sprite;
	static const float			 FIRST_SCALE;

public:
	SpriteDrawer(float scale = FIRST_SCALE);
	~SpriteDrawer();

public:
	void Initialize(std::string tagName,DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero);
	void Update(DirectX::SimpleMath::Vector3 vel);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

public:
	void SetBillBoard(DirectX::SimpleMath::Vector3 cameraPos, DirectX::SimpleMath::Vector3 up);
	void SetPos(DirectX::SimpleMath::Vector3 pos);
	float GetAlpha();
};

inline void SpriteDrawer::SetBillBoard(DirectX::SimpleMath::Vector3 cameraPos, DirectX::SimpleMath::Vector3 up)
{
	this->m_billboard = DirectX::SimpleMath::Matrix::CreateBillboard(this->m_pos, cameraPos, up);
}

inline float SpriteDrawer::GetAlpha()
{
	return this->m_alpha;
}

inline void SpriteDrawer::SetPos(DirectX::SimpleMath::Vector3 pos)
{
	this->m_pos = pos;
}