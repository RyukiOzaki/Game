#include"pch.h"
#include"Enemy.h"
#include"GameObjectManager.h"
#include"GameContext.h"
#include"CollisionManager.h"
#include"ScoreManager.h"
#include"ICollider.h"
#include"EFall.h"
#include"ERunning.h"
#include"ESearch.h"
#include"EStanding.h"
#include"Fruits.h"
#include"Floor.h"

//�萔�̏�����
const float Enemy::GRAVITY = -0.07f;
const float Enemy::SIZE    = 0.003f;
const DirectX::SimpleMath::Vector3 Enemy::START_POS     = DirectX::SimpleMath::Vector3(-3.f, 4.f, 0.f);
const DirectX::SimpleMath::Vector3 Enemy::COLLIDER_SIZE = DirectX::SimpleMath::Vector3(0.20f, 0.25f, 0.20f);

Enemy::Enemy()
	: m_angle(0)
{
	this->m_tagName = "Enemy";
	this->SetPos(this->START_POS);
}

Enemy::~Enemy()
{
	delete this->m_boxCollider;
}

//������
void Enemy::Initialize()
{
	//���f���̍쐬
	this->m_modelObject = std::make_unique<ModelObject>();
	this->m_modelObject->SetPathName(L"Resources/Models");
	this->m_modelObject->SetFillName(L"Resources/Models/Animal2.cmo");
	this->m_modelObject->Initialize();

	//��Ԃ̏�����
	EStanding::Get()->Initialize(this);
	ESearch::Get()->Initialize(this);
	ERunning::Get()->Initialize(this);
	EFall::Get()->Initialize(this);

	//�ŏ��̏�Ԃ�ݒ�
	this->ChangeState(EStanding::Get());

	//�X�R�A�̍쐬
	this->m_score = std::make_unique<Score>();

	//Collider�̐ݒ�
	this->m_boxCollider = new BoxCollider();

	//�X�^�[�g�n�_���L��
	this->m_startPos = this->m_pos;
}

//�X�V
void Enemy::Update(float elapsedTime)
{
	//�d�͂�������
	this->m_pos.y += this->GRAVITY;
	//Collider�̐ݒ�
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
	this->m_collider = this->m_boxCollider;

	//�����蔻��
	this->CollisionWithFloor();
	this->CollisionWithFruits();

	//��Ԃ̍X�V
	this->m_currentState->Update(elapsedTime);

	//pos�̍X�V
	this->m_pos += this->m_vel;

	//�X�R�A�̓o�^
	GameContext::Get<ScoreManager>()->SetEnemyScore(this->m_score->GetScore());
}

//�`��
void Enemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->m_world *= DirectX::SimpleMath::Matrix::CreateScale(this->SIZE);
	this->m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180.0f));
	//����Ă��镪�̕␳
	this->m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(-DirectX::XM_PI/2.0f - this->m_angle);
	this->MatrixToVector();
	this->m_modelObject->Render(this->m_world, view, proj);
}

//���������Ƃ��̏���
bool Enemy::CollisionWithFruits()
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
				return true;
			}
		}
	}
	return false;
}

//���������Ƃ��̏���
bool Enemy::CollisionWithFloor()
{
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
				return true;
			}
		}
	}
	return false;
}


