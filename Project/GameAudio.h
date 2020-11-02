#pragma once
#include<Audio.h>
#include<memory>

class GameAudio
{
private:
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

public:
	GameAudio();
	~GameAudio();

public:
	void Initialize();
	void Update();
	DirectX::AudioEngine* GetAudioEngine();
};

inline DirectX::AudioEngine* GameAudio::GetAudioEngine()
{
	return this->m_audioEngine.get();
}