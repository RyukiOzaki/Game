#include"pch.h"
#include"SpriteManager.h"
#include"GameContext.h"
#include"DeviceResources.h"
#include<functional>

SpriteManager::SpriteManager()
	: m_spriteList()
{
}

SpriteManager::~SpriteManager()
{
	this->DeleteAll();
}

//������
void SpriteManager::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext().Get<DX::DeviceResources>();
	// �G�t�F�N�g�̍쐬
	this->m_basicEffect = std::make_unique<DirectX::BasicEffect>(deviceResources->GetD3DDevice());
	this->m_basicEffect->SetTextureEnabled(true);
	this->m_basicEffect->SetVertexColorEnabled(true);
	// ���̓��C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	this->m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	deviceResources->GetD3DDevice()->CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements,
		DirectX::VertexPositionColorTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());
	//�v���~�e�B�u�o�b�`�̍쐬
	this->m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(deviceResources->GetD3DDeviceContext());
}

//�w�肵���^�O���ƍ��v�����X�v���C�g��Ԃ�
Sprite* SpriteManager::Find(std::string tagName)
{
	Sprite* result = nullptr;
	for (PSprite& sprite : this->m_spriteList)
	{
		if (sprite->GetTagName() == tagName)
		{
			result = sprite.get();
		}
	}
	return result;
}

//�X�V
void SpriteManager::Update()
{
	this->DestroySprite();
}

//���S�t���O�������Ă�����̂��폜����
void SpriteManager::DestroySprite()
{
	//�����ɍ������̂����ׂč폜����
	this->m_spriteList.remove_if(std::mem_fn(&Sprite::GetDeathFlag));
}

//�S�Ă̗v�f���폜����
void SpriteManager::DeleteAll()
{
	for (PSprite& sprite : this->m_spriteList)
	{
		if (sprite != nullptr)
		{
			sprite->Death();
		}
	}
	this->DestroySprite();
}

//�X�v���C�g�����X�g�ɒǉ�����
void SpriteManager::Add(PSprite&& sprite)
{
	this->m_spriteList.push_back(std::move(sprite));
}
