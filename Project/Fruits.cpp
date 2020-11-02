#include"pch.h"
#include"Fruits.h"
#include"GameContext.h"
#include"DeviceResources.h"
#include"GameObjectManager.h"
#include"CollisionManager.h"
#include"Floor.h"
#include<random>

//�萔�̏�����
const float Fruits::START_POS_Y  = 10.0f;
const float Fruits::GRAVITY		 = -0.1f;
const float Fruits::FALL_DIS	 = -3.0f;
const float	Fruits::MAX_RAND_POS = 9.0f;
const float	Fruits::MIN_RAND_POS = -9.0f;
const DirectX::SimpleMath::Vector3 Fruits::COLLIDER_SIZE = DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f);

Fruits::Fruits()
{
	this->m_tagName = "Fruits";
}

Fruits::~Fruits()
{
	delete this->m_boxCollider;
}

//������
void Fruits::Initialize()
{
	//�R���e�L�X�g�̍쐬
	auto context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	//�W�I���g���b�N�v���~�e�B�u�̍쐬
	this->m_geometricPrimitive = DirectX::GeometricPrimitive::CreateGeoSphere(context, 0.3);
	//�����_���Ɉʒu�����
	std::random_device seed_generator;
	std::mt19937 engine(seed_generator());
	std::uniform_real_distribution<float> randPosZ(this->MIN_RAND_POS, this->MAX_RAND_POS);
	std::uniform_real_distribution<float> randPosX(this->MIN_RAND_POS, this->MAX_RAND_POS);
	this->m_pos = DirectX::SimpleMath::Vector3(randPosX(engine), this->START_POS_Y, randPosZ(engine));
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->MatrixToVector();
	//�R���C�_�[�̐���
	this->m_boxCollider = new BoxCollider();
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
}

//�X�V
void Fruits::Update(float elapsedTime)
{
	elapsedTime;
	//�d�͂̐ݒ�
	this->m_vel.y = this->GRAVITY;
	//�R���C�_�[�̍X�V
	this->m_boxCollider->SetCenter(this->m_pos);
	this->m_boxCollider->SetRadius(this->COLLIDER_SIZE);
	this->m_collider = this->m_boxCollider;
	//�����蔻��
	this->OnCollision();
	//�Œ�ʒu�܂ōs���������
	if (this->m_pos.y < this->FALL_DIS)
	{
		this->Invalidate();
	}
	//�|�W�V�����̍X�V
	this->m_pos += this->m_vel;
}

//�`��
void Fruits::Render(const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->MatrixToVector();
	this->m_geometricPrimitive->Draw(this->m_world, view, proj, DirectX::Colors::Red);
}

//�����蔻��
void Fruits::OnCollision()
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
				//this->m_pos.y = 0.05f;
				this->m_vel.y = 0.0f;
			}
		}
	}
}
