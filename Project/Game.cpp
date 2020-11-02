//
// Game.cpp
//

#include"pch.h"
#include"Game.h"
#include"GameContext.h"
#include"GameStateManager.h"
#include"TitleState.h"
#include"PlayState.h"
#include"VictoryState.h"
#include"DefeatState.h"
#include"TieGameState.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
	this->m_deviceResources = std::make_unique<DX::DeviceResources>();
	this->m_deviceResources->RegisterDeviceNotify(this);
	GameContext::Register<DX::DeviceResources>(this->m_deviceResources);
}

Game::~Game() 
{
	//�X�v���C�g�̔j��
	this->m_spriteManager->DeleteAll();
	//�T�E���h�̔j��
	this->m_adx2le->Finalize();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	this->m_deviceResources->SetWindow(window, width, height);

	this->m_deviceResources->CreateDeviceResources();
	this->CreateDeviceDependentResources();

	this->m_deviceResources->CreateWindowSizeDependentResources();
	this->CreateWindowSizeDependentResources();
	
	//�L�[�̍쐬
	this->m_keyboard = std::make_unique<Keyboard>();

	//�R�����X�e�[�g�쐬
	this->m_commonState = std::make_unique<CommonStates>(this->m_deviceResources->GetD3DDevice());
	GameContext::Register<DirectX::CommonStates>(this->m_commonState);

	//�V�[���̐���
	this->m_gameStateManager = std::make_unique<GameStateManager>();
	//�V�[���̓o�^
	this->m_gameStateManager->RegisterState<TitleState>("Title");
	this->m_gameStateManager->RegisterState<PlayState>("Play");
	this->m_gameStateManager->RegisterState<VictoryState>("Victory");
	this->m_gameStateManager->RegisterState<DefeatState>("Defeat");
	this->m_gameStateManager->RegisterState<TieGameState>("TieGame");
	this->m_gameStateManager->SetStartState("Title");
	GameContext::Register<GameStateManager>(this->m_gameStateManager);

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̐���
	this->m_gameObjectManager = std::make_unique<GameObjectManager>();
	GameContext::Register<GameObjectManager>(this->m_gameObjectManager);

	//�X�v���C�g�}�l�[�W���[�̐���
	this->m_spriteManager = std::make_unique<SpriteManager>();
	this->m_spriteManager->Initialize();
	GameContext::Register<SpriteManager>(this->m_spriteManager);

	//�R���W�����}�l�[�W���[�̐���
	this->m_collisionManager = std::make_unique<CollisionManager>();
	GameContext::Register<CollisionManager>(this->m_collisionManager);

	//�X�R�A�}�l�[�W���[�̐���
	this->m_scoreManager = std::make_unique<ScoreManager>();
	GameContext::Register<ScoreManager>(this->m_scoreManager);

   //�T�E���h�̐���
	this->m_adx2le = std::make_unique<Adx2Le>();
	this->m_adx2le->Initialize(L"Sound/CatchTheFruits.acf");
	GameContext::Register<Adx2Le>(this->m_adx2le);
	//�T�E���h�̓ǂݍ���
	this->m_soundLoder = std::make_unique<SoundLoader>();
	GameContext::Register<SoundLoader>(this->m_soundLoder);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
	this->m_timer.Tick([&]()
    {
		this->Update(this->m_timer);
    });

	this->Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
    elapsedTime;

	//���݂̃V�[���̍X�V
	this->m_gameStateManager->Update(elapsedTime);
	//�X�v���C�g�}�l�[�W���[�̍X�V
	this->m_spriteManager->Update();
	//�T�E���h�̍X�V
	this->m_adx2le->Update();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (this->m_timer.GetFrameCount() == 0)
    {
        return;
    }

	this->Clear();

	this->m_deviceResources->PIXBeginEvent(L"Render");
    auto context = this->m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

	this->m_gameStateManager->Render(this->m_projection);

	this->m_deviceResources->PIXEndEvent();

    // Show the new frame.
	this->m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	this->m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = this->m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = this->m_deviceResources->GetRenderTargetView();
    auto depthStencil = this->m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = this->m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

	this->m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	this->m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = this->m_deviceResources->GetOutputSize();
	this->m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!this->m_deviceResources->WindowSizeChanged(width, height))
        return;

	this->CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = this->WINDOW_W;
    height = this->WINDOW_H;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = this->m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	//�E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = this->m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	//��p��ݒ�
	float fovAngleY = XMConvertToRadians(45.0f);

	//�ˉe�s����쐬����
	this->m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
	);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
	this->CreateDeviceDependentResources();
	this->CreateWindowSizeDependentResources();
}
#pragma endregion
