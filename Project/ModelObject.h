//モデル表示クラス
#pragma once
#include"DeviceResources.h"
#include<Model.h>
#include<CommonStates.h>
#include<simplemath.h>

class ModelObject 
{
private:
	std::unique_ptr<DirectX::Model>			m_model;
	std::unique_ptr<DirectX::CommonStates>  m_state;
	DX::DeviceResources*					m_deviceResources;
	const wchar_t*							m_pathName;
	const wchar_t*							m_fillName;

public:
	ModelObject();
	~ModelObject();

public:
	void Initialize();
	void Render(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	void SetPathName(const wchar_t* pathame);
	void SetFillName(const wchar_t* fillName);
};

inline void ModelObject::SetPathName(const wchar_t* pathName)
{
	this->m_pathName = pathName;
}

inline void ModelObject::SetFillName(const wchar_t* fillName)
{
	this->m_fillName = fillName;
}