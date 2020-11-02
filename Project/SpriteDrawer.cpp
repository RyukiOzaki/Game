#include"pch.h"
#include"SpriteDrawer.h"
#include"SpriteManager.h"

//�萔�̏�����
const float	SpriteDrawer::FIRST_SCALE = 5.0f;

SpriteDrawer::SpriteDrawer(float scale)
	: m_pos(DirectX::SimpleMath::Vector3::Zero)
	, m_billboard(DirectX::SimpleMath::Matrix::Identity)
	, m_alpha(1.f)
	, m_scale(scale)
{
}

SpriteDrawer::~SpriteDrawer()
{

}

//������
void SpriteDrawer::Initialize(std::string tagName,DirectX::SimpleMath::Vector3 pos)
{
	this->m_pos = pos;
	this->m_sprite = GameContext::Get<SpriteManager>()->Find(tagName);
}

//�X�V
void SpriteDrawer::Update(DirectX::SimpleMath::Vector3 vel)
{
	this->m_pos.x += vel.x;
	this->m_pos.z += vel.z;
}

//�`��
void SpriteDrawer::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	// ���_���
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::XMFLOAT3( 0.5f,  0.5f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, this->m_alpha), DirectX::XMFLOAT2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::XMFLOAT3( 0.5f, -0.5f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, this->m_alpha), DirectX::XMFLOAT2(0.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, this->m_alpha), DirectX::XMFLOAT2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::XMFLOAT3(-0.5f,  0.5f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, this->m_alpha), DirectX::XMFLOAT2(1.0f, 0.0f)),
	};
	DirectX::CommonStates* state   = GameContext().Get<DirectX::CommonStates>();
	ID3D11DeviceContext* context   = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	SpriteManager* spriteManager   = GameContext().Get<SpriteManager>();

	ID3D11BlendState* blendstate = state->NonPremultiplied();
	//��������
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	//�[�x�o�b�t�@�͂Ȃ�
	context->OMSetDepthStencilState(state->DepthNone(), 0);
	//�J�����O�͉E���
	context->RSSetState(state->CullClockwise());
	//�ݒ�
	DirectX::SimpleMath::Matrix world = this->m_billboard
		* DirectX::SimpleMath::Matrix::CreateScale(this->m_scale)
		* DirectX::SimpleMath::Matrix::CreateTranslation(this->m_pos);
	spriteManager->GetBasicEffect()->SetWorld(world);
	spriteManager->GetBasicEffect()->SetView(view);
	spriteManager->GetBasicEffect()->SetProjection(proj);
	spriteManager->GetBasicEffect()->SetTexture(this->m_sprite->GetSprite());
	spriteManager->GetBasicEffect()->Apply(context);
	context->IASetInputLayout(spriteManager->GetInputLayout());
	//�`��
	spriteManager->GetPrimitiveBatch()->Begin();
	spriteManager->GetPrimitiveBatch()->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	spriteManager->GetPrimitiveBatch()->End();
}
