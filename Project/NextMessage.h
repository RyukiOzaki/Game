//ˆÄ“à•\Ž¦ƒNƒ‰ƒX
#pragma once
#include"SpriteDrawer.h"
#include<memory>
#include<string>
#include<simplemath.h>

class NextMessage
{
private:
	std::unique_ptr<SpriteDrawer> m_nextMessage;
	int m_time;
	int m_isIndicate;
	static const int BLANK_TIME;

public:
	NextMessage(std::string tagName, DirectX::SimpleMath::Vector3 cameraPos, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero, float scale = 5.0f);
	~NextMessage() = default;

public:
	void Update();
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
};