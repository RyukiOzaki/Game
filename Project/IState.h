//ゲームステートのインターフェースクラス
#pragma once
#include "StepTimer.h"
#include <simplemath.h>

class IState
{
	public:
		IState() = default;

	public:
		virtual ~IState() = default;

	public:
		virtual void Initialize() = 0;
		virtual void Update(float elapsedTime) = 0;
		virtual void Render(const DirectX::SimpleMath::Matrix& proj) = 0;
		virtual void Finalize() = 0;
};
