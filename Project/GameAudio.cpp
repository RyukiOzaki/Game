#include"pch.h"
#include"GameAudio.h"
#include<assert.h>

GameAudio::GameAudio()
{

}

GameAudio::~GameAudio()
{

}

void GameAudio::Initialize()
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(FAILED(hr) && "error");
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif // _DEBUG
	this->m_audioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
}

void GameAudio::Update()
{
	if (!this->m_audioEngine->Update())
	{
		if (this->m_audioEngine->IsCriticalError())
		{
			this->m_audioEngine->Reset();
		}
	}
}