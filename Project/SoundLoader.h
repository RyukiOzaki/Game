//音を読み込むクラス
#pragma once

class SoundLoader
{
public:
	SoundLoader() = default;
	~SoundLoader() = default;

public:
	void LoadResult();
	void LoadBattle();
	void LoadTitle();
};