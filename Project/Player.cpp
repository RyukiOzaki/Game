#include"pch.h"
#include"Player.h"
#include"PRunning.h"
#include"PStanding.h"
#include"GameObjectManager.h"
#include"GameContext.h"
#include"CollisionManager.h"
#include"ScoreManager.h"
#include"PFall.h"
#include"Fruits.h"
#include"Floor.h"

//�萔�̏�����
const float Player::GRAVITY = -0.1f;
const float Player::SIZE    = 0.003f;
const float Player::FLOOR_Y = -0.5f;
const DirectX::SimpleMath::Vector3 Player::COLLIDER_SIZE = DirectX::SimpleMath::Vector3(0.20f, 0.15f, 0.20f);
const DirectX::SimpleMath::Vector3 Player::START_POS     = DirectX::SimpleMath::Vector3(0.f, 4.f, 0.f);

Player::Player()
{
	this->m_tagName = "Player";
}

Player::~Player()
{
	delete this->m_boxCollider;
}

//������
void Player::Initialize()
{
	//pos�̐ݒ�
	this->m_pos = this->START_POS;	
	//��]�p�̏�����
	this->m_rotation = DirectX::SimpleMath::Vector3::Zero;
	//��]���x�̏�����
	this->m_rotateSpeed = 2.0f;
	//���f���̍쐬
	this->m_modelObject = std::make_unique<ModelObject>();
	this->m_modelObject->SetPathName(L"Resources/Models");
	this->m_modelObject->SetFillName(L"Resources/Models/animal.cmo");
	this->m_modelObject->Initialize();
	//�L�[�{�[�h�X�e�[�g�g���b�J�[���쐬
	this->m_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//��Ԃ̏�����
	PStanding::Get()->Initialize(this);
	PRunning::Get()->Initialize(this);
	PFall::Get()->Initialize(this);
	//�ŏ��̏�Ԃ�ݒ�
	this->ChangeState(PStanding::Get());
	//�X�R�A�̍쐬
	this->m_score = std::make_unique<Score>();
	//Collider�̐ݒ�
	this->m_boxCollider = new BoxCollider();
	//�X�^�[�g�n�_���L��
	this->m_startPos = this->m_pos;
}

//�X�V
void Player::Update(float elapsedTime)
{
	//�d��
	this->m_pos.y += this->GRAVITY;
	//Collider�̐ݒ�
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
	this->m_collider = this->m_boxCollider;
	
	//������ݒ�
	this->SetAngle();

	//��������Fall��
	if (this->m_pos.y < this->FLOOR_Y)
	{
		this->ChangeState(PFall::Get());
	}

	//���݂̏�Ԃ̍X�V
	this->m_currentState->Update(elapsedTime);

	//���������Ƃ��̏���
	if (this->m_currentState != PFall::Get())
	{
		this->OnCollision();
	}

	//�X�R�A�̓o�^
	GameContext::Get<ScoreManager>()->SetPlayerScore(this->m_score->GetScore());
}

//�`��
void Player::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->m_world *= DirectX::SimpleMath::Matrix::CreateScale(this->SIZE);
	this->m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180.0f));    //���f���𔽑΂Ɍ�����
	this->m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(this->m_rotation.y));
	this->MatrixToVector();
	this->m_modelObject->Render(this->m_world, view, proj);
}

//���������Ƃ��̏���
void Player::OnCollision()
{
	//�t���[�c�z��̎擾
	std::vector<GameObject*> fruits = GameContext::Get<GameObjectManager>()->Find("Fruits");
	//�t���[�c����ȏ゠�邩�̊m�F
	if (fruits.size() != 0)
	{
		for (std::vector<GameObject*>::iterator iter = fruits.begin(); iter != fruits.end(); iter++)
		{
			//�o�Ă��邷�ׂẴt���[�c�Ɠ����蔻��
			if (GameContext::Get<CollisionManager>()->DetectCollisionBoxToBox(*this->m_boxCollider,
				*dynamic_cast<Fruits*>((*iter))->GetBoxCollider()) == true)
			{
				//���������t���[�c�����݂��Ȃ��Ȃ�������Z���Ȃ�
				if ((*iter)->IsValid())
				{
					//���_�̉��Z
					this->m_score->AddScore(1);
				}
				//���������t���[�c���폜
				(*iter)->Invalidate();
			}
		}
	}
	//���z��̎擾
	std::vector<GameObject*> floor = GameContext::Get<GameObjectManager>()->Find("Floor");
	//������ȏ゠�邩�̊m�F
	if (floor.size() != 0)
	{
		for (std::vector<GameObject*>::iterator iter = floor.begin(); iter != floor.end(); iter++)
		{
			//�o�Ă��邷�ׂĂ̏��Ɠ����蔻��
			if (GameContext::Get<CollisionManager>()->DetectCollisionBoxToBox(*this->m_boxCollider,
				*dynamic_cast<Floor*>((*iter))->GetBoxCollider()) == true)
			{
				this->m_pos.y = 0.0f;
			}
		}
	}
}

//����������
void Player::SetAngle()
{
	//�L�[�{�[�h���擾
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	//�L�[�{�[�h�X�e�[�g�g���b�J�[�̍X�V
	this->m_tracker->Update(key);
	//�L�[���͂ɉ�����angle��ύX
	if (key.IsKeyDown(DirectX::Keyboard::Right))
	{
		this->m_rotation.y = Direction::EAST;
	}
	if (key.IsKeyDown(DirectX::Keyboard::Left))
	{
		this->m_rotation.y = Direction::WEST;
	}
	if (key.IsKeyDown(DirectX::Keyboard::Up))
	{
		this->m_rotation.y = Direction::NORTH;
	}
	if (key.IsKeyDown(DirectX::Keyboard::Down))
	{
		this->m_rotation.y = Direction::SOUTH;
	}
}