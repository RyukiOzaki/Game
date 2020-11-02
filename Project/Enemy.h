//敵クラス
#pragma once
#include"GameObject.h"
#include"ModelObject.h"
#include"BoxCollider.h"
#include"Score.h"
#include"EIState.h"

class EIState;

class Enemy : public GameObject
{
private:
	std::unique_ptr<ModelObject>				m_modelObject;
	float										m_angle;
	BoxCollider*								m_boxCollider;
	std::unique_ptr<Score>						m_score;
	DirectX::SimpleMath::Vector3                m_startPos;
	EIState*									m_currentState;
private:
	static const DirectX::SimpleMath::Vector3   COLLIDER_SIZE;
	static const DirectX::SimpleMath::Vector3   START_POS;
	static const float							SIZE;

public:
	static const float GRAVITY;

public:
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();
	
	//fruitsと当たった時の処理
	bool CollisionWithFruits();

	//floorと当たった時の処理
	bool CollisionWithFloor();

	//状態を変える
	void ChangeState(EIState* currentState);

public:
	//アクセサ
	void SetAngle(float angle);
	float GetAngle();
	DirectX::SimpleMath::Vector3 GetStartPos();

public:
	void Initialize()override;
	void Update(float elapsedTime)override;
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)override;
};

//状態を変える
inline void Enemy::ChangeState(EIState* currentState)
{
	this->m_currentState = currentState;
}

inline void Enemy::SetAngle(float angle)
{
	this->m_angle = angle;
}
inline float Enemy::GetAngle()
{
	return this->m_angle;
}
inline DirectX::SimpleMath::Vector3 Enemy::GetStartPos()
{
	return this->m_startPos;
}