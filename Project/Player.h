//プレイヤークラス
#pragma once
#include"GameObject.h"
#include"ModelObject.h"
#include"PIState.h"
#include"BoxCollider.h"
#include"Score.h"
#include<Keyboard.h>


class PIState;

class Player : public GameObject
{
private:
	std::unique_ptr<ModelObject>									m_modelObject;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>        m_tracker;
	PIState*														m_currentState;
	float															m_moveSpeed;
	float															m_rotateSpeed;
	BoxCollider*													m_boxCollider;
	std::unique_ptr<Score>											m_score;
	DirectX::SimpleMath::Vector3									m_startPos;

private:
	static const float												GRAVITY;
	static const DirectX::SimpleMath::Vector3						COLLIDER_SIZE;
	static const float												SIZE;
	static const DirectX::SimpleMath::Vector3						START_POS;

public:
	static const float												FLOOR_Y;

public:
	enum Direction
	{
		NORTH = 0,
		WEST = 90,
		SOUTH = 180,
		EAST = 270,
	};

public:
	Player();
	~Player();

private:
	void SetAngle();

public:
	//状態を変える
	void ChangeState(PIState* currentState);
	// キーボードステートトラッカーを取得する
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyboardStateTracker();
	//あたったときの処理
	void OnCollision();
	//スタート地点を返す
	DirectX::SimpleMath::Vector3 GetStartPos();

public:
	void Initialize()override;
	void Update(float elapsedTime)override;
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)override;
};

inline void Player::ChangeState(PIState* currentState)
{
	this->m_currentState = currentState;
}

inline std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& Player::GetKeyboardStateTracker()
{
	return this->m_tracker;
}

inline DirectX::SimpleMath::Vector3 Player::GetStartPos()
{
	return this->m_startPos;
}