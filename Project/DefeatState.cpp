#include"pch.h"
#include"DefeatState.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"
#include"ScoreManager.h"
#include"GameContext.h"
#include"Adx2Le.h"
#include"SoundLoader.h"

//�萔�̏�����
const DirectX::SimpleMath::Vector3 DefeatState::APPLE_POS   = DirectX::SimpleMath::Vector3(290.0f, 300.0f, 0.0f);
const DirectX::SimpleMath::Vector3 DefeatState::ANIMAL_POS  = DirectX::SimpleMath::Vector3(50.0f, 300.0f, 0.0f);
const DirectX::SimpleMath::Vector3 DefeatState::SCORE_POS   = DirectX::SimpleMath::Vector3(650.0f, 330.0f, 0.0f);
const DirectX::SimpleMath::Vector3 DefeatState::MESSAGE_POS = DirectX::SimpleMath::Vector3(-0.0f, -0.6f, 0.0f);
const float						   DefeatState::SCORE_SIZE  = 5.0f;
const float						   DefeatState::ANIMAL_SIZE = 0.3f;
const float						   DefeatState::APPLE_SIZE  = 0.3f;

DefeatState::DefeatState()
{
}

//�f�X�g���N�^
DefeatState::~DefeatState()
{
}

//������
void DefeatState::Initialize()
{
	//�J�����̐���
	this->m_camera = std::make_unique<FixedPointCamera>();
	//�L�[�{�[�h�X�e�[�g�g���b�J�[���쐬
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//�摜�̍쐬
	this->m_victory = std::make_unique<Batch>("Defeat");
	this->m_animal = std::make_unique<Batch>("Animal1");
	this->m_animal->SetPos(this->ANIMAL_POS);
	this->m_apple = std::make_unique<Batch>("Apple");
	this->m_apple->SetPos(this->APPLE_POS);
	//�X�R�A�̍쐬
	this->m_score = std::make_unique<NumDrawer>(this->SCORE_POS, this->SCORE_SIZE);
	//�ē��\���̍쐬
	this->m_nextMessage = std::make_unique<NextMessage>("Space", this->m_camera->GetEye(), this->m_camera->GetUp(), this->MESSAGE_POS);
	//�����BGM�Đ�
	GameContext::Get<SoundLoader>()->LoadResult();
	GameContext::Get<Adx2Le>()->Play(1);
}

//�X�V
void DefeatState::Update(float elapsedTime)
{
	elapsedTime;
	//�L�[�{�[�h���擾
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//�L�[�{�[�h�X�e�[�g�g���b�J�[�̍X�V
	this->m_tracker->Update(key);
	//�X�R�A�̍X�V
	this->m_score->SetNowNum(GameContext::Get<ScoreManager>()->GetPlayerScore());
	this->m_score->Update();
	//�ē��\���̍X�V
	this->m_nextMessage->Update();

	if (key.IsKeyDown(DirectX::Keyboard::Space))
	{
		//�v���C�X�e�[�g��
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Title");
		//�T�E���h�̒�~
		GameContext::Get<Adx2Le>()->Stop();
	}
}

//�`��
void DefeatState::Render(const DirectX::SimpleMath::Matrix& proj)
{
	this->m_victory->Render();
	RECT srcRect = { 0,0,Batch::SPRITE_WIDTH, Batch::SPRITE_HEIGHT };
	this->m_animal->Render(&srcRect, this->ANIMAL_SIZE);
	this->m_apple->Render(&srcRect, this->APPLE_SIZE);
	this->m_score->Render();
	this->m_nextMessage->Render(this->m_camera->GetView(), proj);
}

//�I������
void DefeatState::Finalize()
{
	this->m_tracker.reset();
}