#include"pch.h"
#include"SoundLoader.h"
#include"GameContext.h"
#include"Adx2Le.h"

//���U���g�̉������[�h����
void SoundLoader::LoadResult()
{
	GameContext::Get<Adx2Le>()->LoadAcbFile(L"Resources/Sound/WorkUnit_0/ResultSound.acb");
}

//�v���C�V�[���̉������[�h����
void SoundLoader::LoadBattle()
{
	GameContext::Get<Adx2Le>()->LoadAcbFile(L"Resources/Sound/WorkUnit_0/BattleSound.acb");
}

//�^�C�g���̉������[�h����
void SoundLoader::LoadTitle()
{
	GameContext::Get<Adx2Le>()->LoadAcbFile(L"Resources/Sound/WorkUnit_0/TitleSound.acb");
}
