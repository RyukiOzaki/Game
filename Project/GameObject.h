//ゲームオブジェクトクラス
//全てのゲームオブジェクトのベースクラス
#pragma once
#include<SimpleMath.h>
#include<string>
#include"DeviceResources.h"
#include"ICollider.h"

class GameObject
{
	private:
		bool m_isValid;
		
	protected:
		DirectX::SimpleMath::Vector3 m_pos;
		DirectX::SimpleMath::Vector3 m_vel;
		DirectX::SimpleMath::Vector3 m_rotation;
		DirectX::SimpleMath::Vector3 m_scale;
		DirectX::SimpleMath::Matrix  m_world;
		DX::DeviceResources*		 m_deviceResources;
		std::string					 m_tagName;
		ICollider*					 m_collider;

	public:
		GameObject();

	public:
		virtual ~GameObject();

	public:
		virtual void Initialize() = 0;
		virtual void Update(float elapsedTime) = 0;
		virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;

	public:
		void Invalidate();
		bool IsValid();
		bool IsInvalid();

		DirectX::SimpleMath::Vector3& GetPos();
		DirectX::SimpleMath::Vector3& GetVel();
		DirectX::SimpleMath::Vector3& GetRotation();
		DirectX::SimpleMath::Vector3& GetScale();
		ICollider*					  GetCollider();
		std::string&				  GetTagName();
		DirectX::SimpleMath::Matrix&  GetWorld();

		void SetPos(DirectX::SimpleMath::Vector3 pos);
		void SetPos(int x, float y, int z);
		void SetVel(DirectX::SimpleMath::Vector3 vel);
		void SetRotation(DirectX::SimpleMath::Vector3 rotation);
		void SetScale(DirectX::SimpleMath::Vector3 scale);
		void SetDeviceResources(DX::DeviceResources* deviceResources);

		void MatrixToVector();

	public:
		static void Destroy(GameObject* object);
};

inline void GameObject::SetDeviceResources(DX::DeviceResources* deviceResources)
{
	this->m_deviceResources = deviceResources;
}

inline bool GameObject::IsValid()
{
	return this->m_isValid;
}

inline bool GameObject::IsInvalid()
{
	return !this->m_isValid;
}

inline DirectX::SimpleMath::Vector3& GameObject::GetPos()
{
	return this->m_pos;
}

inline DirectX::SimpleMath::Vector3& GameObject::GetVel()
{
	return this->m_vel;
}

inline DirectX::SimpleMath::Vector3& GameObject::GetRotation()
{
	return this->m_rotation;
}

inline DirectX::SimpleMath::Vector3& GameObject::GetScale()
{
	return this->m_scale;
}

inline std::string& GameObject::GetTagName()
{
	return this->m_tagName;
}

inline ICollider* GameObject::GetCollider()
{
	return this->m_collider;
}

inline DirectX::SimpleMath::Matrix&  GameObject::GetWorld()
{
	return this->m_world;
}

inline void GameObject::SetPos(DirectX::SimpleMath::Vector3 pos)
{
	this->m_pos = pos;
}

inline void GameObject::SetPos(int x, float y, int z)
{
	this->m_pos = DirectX::SimpleMath::Vector3(static_cast<float>(x), y, static_cast<float>(z));
}

inline void GameObject::SetVel(DirectX::SimpleMath::Vector3 vel)
{
	this->m_vel = vel;
}

inline void GameObject::SetRotation(DirectX::SimpleMath::Vector3 rotation)
{
	this->m_rotation = rotation;
}

inline void GameObject::SetScale(DirectX::SimpleMath::Vector3 scale)
{
	this->m_scale = scale;
}



