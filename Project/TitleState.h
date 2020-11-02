//タイトルステートクラス
#pragma once
#include"IState.h"
#include"SpriteDrawer.h"
#include"SpriteReader.h"
#include"FixedPointCamera.h"
#include"NextMessage.h"
#include<Keyboard.h>
#include<simplemath.h>

class TitleState : public IState
{
private:
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>        m_tracker;
	std::unique_ptr<SpriteDrawer>									m_titleDrawer;
	std::unique_ptr<SpriteReader>									m_spriteReader;
	std::unique_ptr<FixedPointCamera>								m_camera;
	std::unique_ptr<NextMessage>									m_nextMessage;

private:
	static const DirectX::SimpleMath::Vector3						MESSAGE_POS;
public:
	TitleState();

public:
	~TitleState();

public:
	void Initialize() override;
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& proj) override;
	void Finalize() override;

};