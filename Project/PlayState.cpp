#include"pch.h"
#include"PlayState.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"
#include"GameContext.h"
#include"Player.h"
#include"Floor.h"
#include"Enemy.h"
#include"FruitsGenerator.h"
#include"Game.h"
#include"Adx2Le.h"
#include"SoundLoader.h"

//�萔�̏�����
const int PlayState::MAX_GAME_COUNT                        = 1800;
const DirectX::SimpleMath::Vector3 PlayState::TIME_POS     = DirectX::SimpleMath::Vector3(Game::WINDOW_W / 2, 50.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::TIMER_POS    = DirectX::SimpleMath::Vector3(325.0f, 0.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::P_ANIMAL_POS = DirectX::SimpleMath::Vector3(0.0f, 60.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::E_ANIMAL_POS = DirectX::SimpleMath::Vector3(0.0f, 140.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::P_APPLE_POS  = DirectX::SimpleMath::Vector3(63.0f, 60.0f, 0.0f);
const DirectX::SimpleMath::Vector3 PlayState::E_APPLE_POS  = DirectX::SimpleMath::Vector3(63.0f, 140.0f, 0.0f);
const float PlayState::TIMER_SIZE                          = 0.2f;
const float PlayState::ANIMAL_SIZE                         = 0.08f;
const float PlayState::APPLE_SIZE						   = 0.08f;
const int PlayState::SOUND_NUM							   = 2;

PlayState::PlayState()
	: m_gameCount(MAX_GAME_COUNT)
{
}

PlayState::~PlayState()
{
	this->ResetUI();
}

//������
void PlayState::Initialize()
{
	//�L�[�{�[�h�X�e�[�g�g���b�J�[���쐬
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//���ԕ\���N���X�̐���
	this->m_timeDrawer = std::make_unique<NumDrawer>(this->TIME_POS);
	//���̐���
	std::unique_ptr<Floor> floor = std::make_unique<Floor>();
	GameContext::Get<GameObjectManager>()->Add(std::move(floor));
	//�v���C���[�̐���
	std::unique_ptr<Player> player = std::make_unique<Player>();
	//�J�����̍쐬
	this->m_followCamera = std::make_unique<FollowCamera>(player->GetPos());
	//�v���C���[�̓o�^
	GameContext::Get<GameObjectManager>()->Add(std::move(player));
	//�t���[�c�W�F�l���[�^�[�̐���
	std::unique_ptr<FruitsGenerator> fruitsGenerator = std::make_unique<FruitsGenerator>();
	GameContext::Get<GameObjectManager>()->Add(std::move(fruitsGenerator));
	//�G�̐���
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	GameContext::Get<GameObjectManager>()->Add(std::move(enemy));
	//�X�R�A�\���N���X�̐���
	this->m_scoreDrawer = std::make_unique<ScoreDrawer>();
	//UI�̐���
	this->InitializeUI();
	//���̐���
	GameContext::Get<SoundLoader>()->LoadBattle();
	GameContext::Get<Adx2Le>()->Play(0);
}

//�X�V
void PlayState::Update(float elapsedTime)
{
	elapsedTime;
	//�L�[�{�[�h���擾
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//�L�[�{�[�h�X�e�[�g�g���b�J�[�̍X�V
	this->m_tracker->Update(key);
	//�Q�[�����Ԃ̍X�V
	this->m_gameCount--;
	//�������Ԃŏ��s����
	if (this->m_gameCount <= 0)
	{
		this->m_gameCount = this->MAX_GAME_COUNT;
		this->WinJudgment();
	}
	//�X�V���ꂽ���Ԃ�o�^
	this->m_timeDrawer->SetNowNum(static_cast<int>(this->m_gameCount / 60));
	this->m_timeDrawer->Update();

	//�f�o�b�O�p 
	if (key.IsKeyDown(DirectX::Keyboard::V))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Victory");
		//���̒�~
		GameContext::Get<Adx2Le>()->Stop();
	}
	if (key.IsKeyDown(DirectX::Keyboard::D))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Defeat");
		//���̒�~
		GameContext::Get<Adx2Le>()->Stop();
	}
	if (key.IsKeyDown(DirectX::Keyboard::T))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("TieGame");
		//���̒�~
		GameContext::Get<Adx2Le>()->Stop();
	}

	//�I�u�W�F�N�g�̍X�V
	GameContext::Get<GameObjectManager>()->Update(elapsedTime);

	//�X�R�A�̍X�V
	this->m_scoreDrawer->Update();

	//�v���C���[���擾
	std::vector<GameObject*> target = GameContext::Get<GameObjectManager>()->Find("Player");
	for (std::vector<GameObject*>::iterator iter = target.begin(); iter != target.end(); iter++)
	{
		//�J�����̍X�V
		this->m_followCamera->Update((*iter)->GetPos() + FollowCamera::EYE_POS, (*iter)->GetPos());
	}
}

//�`��
void PlayState::Render(const DirectX::SimpleMath::Matrix& proj)
{
	//�Q�[���I�u�W�F�N�g�̕`��
	GameContext::Get<GameObjectManager>()->Render(this->m_followCamera->GetView(), proj);
	//UI�̕\��
	this->UIRender();
	//�X�R�A�̕\��
	this->m_scoreDrawer->Render();
	//���Ԃ̕\��
	this->m_timeDrawer->Render();
}

//�I������
void PlayState::Finalize()
{
	this->m_tracker.reset();
	GameContext::Get<GameObjectManager>()->DeleteAll();
}

//���s����
void PlayState::WinJudgment()
{
	if (GameContext::Get<ScoreManager>()->GetPlayerScore() > GameContext::Get<ScoreManager>()->GetEnemyScore())
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Victory");
	}
	else if (GameContext::Get<ScoreManager>()->GetPlayerScore() < GameContext::Get<ScoreManager>()->GetEnemyScore())
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Defeat");
	}
	else
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("TieGame");
	}
	//���̒�~
	GameContext::Get<Adx2Le>()->Stop();
}

//UI�̕\��
void PlayState::UIRender()
{	
	RECT srcRect = { 0,0,Batch::SPRITE_WIDTH, Batch::SPRITE_HEIGHT };
	//UI�̕\��
	this->m_timerDrawer->Render(&srcRect, this->TIMER_SIZE);
	this->m_pAnimalDrawer->Render(&srcRect, this->ANIMAL_SIZE);
	this->m_eAnimalDrawer->Render(&srcRect, this->ANIMAL_SIZE);
	this->m_pAppleDrawer->Render(&srcRect, this->APPLE_SIZE);
	this->m_eAppleDrawer->Render(&srcRect, this->APPLE_SIZE);
}

//UI�̃��Z�b�g
void PlayState::ResetUI()
{
	this->m_timerDrawer.reset();
	this->m_pAnimalDrawer.reset();
	this->m_eAnimalDrawer.reset();
	this->m_pAppleDrawer.reset();
	this->m_eAppleDrawer.reset();
}

//UI�̏�����
void PlayState::InitializeUI()
{
	//�^�C�}�[�\���̐���
	this->m_timerDrawer = std::make_unique<Batch>("Timer");
	this->m_timerDrawer->SetPos(this->TIMER_POS);
	//�����\���̐���
	this->m_pAnimalDrawer = std::make_unique<Batch>("Animal1");
	this->m_pAnimalDrawer->SetPos(this->P_ANIMAL_POS);
	this->m_eAnimalDrawer = std::make_unique<Batch>("Animal2");
	this->m_eAnimalDrawer->SetPos(this->E_ANIMAL_POS);
	//�ь�\���̍쐬
	this->m_pAppleDrawer = std::make_unique<Batch>("Apple");
	this->m_pAppleDrawer->SetPos(this->P_APPLE_POS);
	this->m_eAppleDrawer = std::make_unique<Batch>("Apple");
	this->m_eAppleDrawer->SetPos(this->E_APPLE_POS);
}

