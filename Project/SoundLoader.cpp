#include"pch.h"
#include"SoundLoader.h"
#include"GameContext.h"
#include"Adx2Le.h"

//リザルトの音をロードする
void SoundLoader::LoadResult()
{
	GameContext::Get<Adx2Le>()->LoadAcbFile(L"Resources/Sound/WorkUnit_0/ResultSound.acb");
}

//プレイシーンの音をロードする
void SoundLoader::LoadBattle()
{
	GameContext::Get<Adx2Le>()->LoadAcbFile(L"Resources/Sound/WorkUnit_0/BattleSound.acb");
}

//タイトルの音をロードする
void SoundLoader::LoadTitle()
{
	GameContext::Get<Adx2Le>()->LoadAcbFile(L"Resources/Sound/WorkUnit_0/TitleSound.acb");
}
