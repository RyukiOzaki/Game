#include"pch.h"
#include"ResultState.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"
#include"SpriteManager.h"
#include"GameContext.h"

//�R���X�g���N�^
ResultState::ResultState()
	: m_playerPos(DirectX::SimpleMath::Vector3(0.0f, 0.5f, 0.0f))
{
}

//�f�X�g���N�^
ResultState::~ResultState()
{
}

//������
void ResultState::Initialize()
{
	//�L�[�{�[�h�X�e�[�g�g���b�J�[���쐬
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//�J�����̐���
	this->m_camera = std::make_unique<FixedPointCamera>();
	//���̐���
	std::unique_ptr<Ground> ground = std::make_unique<Ground>();
	GameContext::Get<GameObjectManager>()->Add(std::move(ground));
	
	this->m_message = std::make_unique<SpriteDrawer>(5.0f);
	this->m_message->Initialize("ResultMessage",DirectX::SimpleMath::Vector3(0.f,0.f,0.f));
	this->m_message->SetBillBoard(this->m_camera->GetEye(), this->m_camera->GetUp());
	
	this->m_test = std::make_unique<Batch>("Number");
	this->m_test->SetPos(DirectX::SimpleMath::Vector3(5.0f, 5.0f, 0.0f));	
}

//�X�V
void ResultState::Update(float elapsedTime)
{
	//�L�[�{�[�h���擾
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//�L�[�{�[�h�X�e�[�g�g���b�J�[�̍X�V
	this->m_tracker->Update(key);

	if (key.IsKeyDown(DirectX::Keyboard::B))
	{
		//�^�C�g���X�e�[�g��
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Title");
	}

	GameContext::Get<GameObjectManager>()->Update(elapsedTime);

	
}

//�`��
void ResultState::Render(const DirectX::SimpleMath::Matrix& proj)
{
	GameContext::Get<GameObjectManager>()->Render(this->m_camera->GetView(), proj);
	this->m_message->Render(this->m_camera->GetView(), proj);

	//this->m_timeDrawer->Render(this->m_camera->GetView(), proj);
	RECT srcRect = { 48,0,72,24 };
	this->m_test->Render(&srcRect);
}

//�I������
void ResultState::Finalize()
{
	this->m_tracker.reset();
	GameContext::Get<GameObjectManager>()->DeleteAll();
}
