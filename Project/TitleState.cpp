#include"pch.h"
#include"TitleState.h"
#include"GameStateManager.h"
#include"GameObjectManager.h"
#include"GameContext.h"
#include"Adx2Le.h"
#include"SoundLoader.h"

//�萔�̏�����
const DirectX::SimpleMath::Vector3 TitleState::MESSAGE_POS = DirectX::SimpleMath::Vector3(0.0f, -0.3f, 0.0f);

TitleState::TitleState()
{
}

TitleState::~TitleState()
{
}

//������
void TitleState::Initialize()
{
	//�J�����̐���
	this->m_camera = std::make_unique<FixedPointCamera>();
	//�L�[�{�[�h�X�e�[�g�g���b�J�[���쐬
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//�X�v���C�g�̓ǂݍ���
	this->m_spriteReader = std::make_unique<SpriteReader>();
	this->m_spriteReader->Reading();
	//�^�C�g���X�v���C�g�̐���
	this->m_titleDrawer = std::make_unique<SpriteDrawer>(10.0f);
	this->m_titleDrawer->Initialize("Title");
	this->m_titleDrawer->SetBillBoard(this->m_camera->GetEye(), this->m_camera->GetUp());
	//�ē��\���̍쐬
	this->m_nextMessage = std::make_unique<NextMessage>("Enter", this->m_camera->GetEye(), this->m_camera->GetUp(), this->MESSAGE_POS);
	//�����BGM�Đ�
	GameContext::Get<SoundLoader>()->LoadTitle();
	GameContext::Get<Adx2Le>()->Play(0);
}

//�X�V
void TitleState::Update(float elapsedTime)
{
	elapsedTime;
	//�L�[�{�[�h���擾
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//�L�[�{�[�h�X�e�[�g�g���b�J�[�̍X�V
	this->m_tracker->Update(key);
	//���b�Z�[�W�̍X�V
	this->m_nextMessage->Update();

	

	if (key.IsKeyDown(DirectX::Keyboard::Enter))
	{
		//�v���C�X�e�[�g��
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState("Play");
		//�T�E���h�̒�~
		GameContext::Get<Adx2Le>()->Stop();
	}
}

//�`��
void TitleState::Render(const DirectX::SimpleMath::Matrix& proj)
{
	this->m_titleDrawer->Render(this->m_camera->GetView(), proj);
	this->m_nextMessage->Render(this->m_camera->GetView(), proj);
}

//�I������
void TitleState::Finalize()
{
	this->m_tracker.reset();
}
