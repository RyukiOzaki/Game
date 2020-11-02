//
// Game.h
//

#pragma once

#include"DeviceResources.h"
#include"StepTimer.h"
#include"GameStateManager.h"
#include"SpriteManager.h"
#include"GameObjectManager.h"
#include"CollisionManager.h"
#include"ScoreManager.h"
#include"Adx2Le.h"
#include"SoundLoader.h"
#include<Keyboard.h>
#include<CommonStates.h>


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:
    Game() noexcept(false);
	~Game();
    // Initialization and management
    void Initialize(HWND window, int width, int height);
    // Basic game loop
    void Tick();
    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;
    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);
    // Properties
    void GetDefaultSize( int& width, int& height ) const;

public:
	static const int WINDOW_W = 800;
	static const int WINDOW_H = 600;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

private:
    // Device resources.
    std::unique_ptr<DX::DeviceResources>						m_deviceResources;
    // Rendering loop timer.
    DX::StepTimer												m_timer;
	// キーボード
	std::unique_ptr<DirectX::Keyboard>							m_keyboard;
	// 射影行列
	DirectX::SimpleMath::Matrix									m_projection;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>						m_commonState;
	//ゲームステイトマネージャー
	std::unique_ptr<GameStateManager>							m_gameStateManager;
	//スプライトマネージャー
	std::unique_ptr<SpriteManager>								m_spriteManager;
	//ゲームオブジェクトマネージャー
	std::unique_ptr<GameObjectManager>							m_gameObjectManager;
	//コリジョンマネージャー
	std::unique_ptr<CollisionManager>							m_collisionManager;
	//スコアマネージャー
	std::unique_ptr<ScoreManager>								m_scoreManager;
	//Adx2Le
	std::unique_ptr<Adx2Le>										m_adx2le;
	//サウンドローダー
	std::unique_ptr<SoundLoader>								m_soundLoder;
};