//リザルトステートクラス
#pragma once
#include"IState.h"
#include"FixedPointCamera.h"
#include"Ground.h"
#include"OtherFruits.h"
#include"ModelObject.h"
#include"Score.h"
#include"SpriteDrawer.h"
#include"Batch.h"
#include<Keyboard.h>


class ResultState : public IState
{
private:
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>        m_tracker;
	std::unique_ptr<FixedPointCamera>								m_camera;
	std::unique_ptr<Ground>											m_ground;
	std::unique_ptr<SpriteDrawer>									m_message;
	DirectX::SimpleMath::Vector3									m_playerPos;
	std::unique_ptr<Batch>											m_test;
	static const int FRUITS_NUM = 5;
	

public:
	ResultState();

public:
	~ResultState();

public:
	void Initialize() override;
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& proj) override;
	void Finalize() override;

};