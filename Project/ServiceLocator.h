//�T�[�r�X���P�[�^�[�N���X
#pragma once
#include<cassert>
#include<memory>

//�T�[�r�X���P�C�^�[
template<typename Service>
class ServiceLocator final
{
	private:
		//�C���^�[�t�F�[�X
		class IServiceHolder;

		template<typename ConcreteService>
		class ServicePtrHolder;

		template<typename ConcreteService>
		class ServiceRefHolder;
		
		template<typename ConcreteService>
		class ServiceValHolder;


	private:
		static std::unique_ptr<IServiceHolder> s_serviceHolder;


	public:
		//�|�C���^�̃N���X�̕ϐ����쐬
		template<typename ConcreteService>
		static void Register(ConcreteService* service)
		{
			s_serviceHolder = std::make_unique<ServicePtrHolder<ConcreteService>>(service);
		}
		//�����Ă��鏊�L���̃|�C���^�̃N���X�̕ϐ����쐬
		template<typename ConcreteService>
		static void Register(std::unique_ptr<ConcreteService>& service)
		{
			s_serviceHolder = std::make_unique<ServiceRefHolder<ConcreteService>>(service);
		}

		//���j�[�N�|�C���^�̃N���X�̕ϐ����쐬
		template<typename ConcreteService>
		static void Register(std::unique_ptr<ConcreteService>&& service)
		{
			s_serviceHolder = std::make_unique<ServiceValHolder<ConcreteService>>(std::move(service));
		}

		//�N���X�̃|�C���^��Ԃ�
		static Service* Get()
		{
			assert(s_serviceHolder && "The service has not been registered.");

			return s_serviceHolder->Get();
		}

		//���Z�b�g����
		static void Reset()
		{
			s_serviceHolder.reset();
		}
};


//�C���^�[�t�F�[�X
template<typename Service>
class ServiceLocator<Service>::IServiceHolder
{
	public:
		virtual ~IServiceHolder() = default;
		virtual Service* Get() const = 0;
};


//�|�C���^�[�̃t�H���_�[
template<typename Service>
template<typename ConcreteService>
class ServiceLocator<Service>::ServicePtrHolder final : public IServiceHolder
{
	private:
		ConcreteService* m_service;


	public:
		//�R���X�g���N�^
		ServicePtrHolder(ConcreteService* service)
			: m_service(service)
		{
		}

		//�|�C���^�[��Ԃ�
		Service* Get() const
		{
			return m_service;
		}
};


//���L������������ϐ��̃t�H���_�[
template<typename Service>
template<typename ConcreteService>
class ServiceLocator<Service>::ServiceRefHolder final : public IServiceHolder
{
	private:
		std::unique_ptr<ConcreteService>& m_service;


	public:
		//�R���X�g���N�^
		ServiceRefHolder(std::unique_ptr<ConcreteService>& service)
			: m_service(service)
		{
		}

		//���|�C���^�\��Ԃ�
		Service* Get() const
		{
			return m_service.get();
		}
};


//���j�[�N�|�C���^���珊�L�����ڂ����t�H���_�[
template<typename Service>
template<typename ConcreteService>
class ServiceLocator<Service>::ServiceValHolder final : public IServiceHolder
{
	private:
		std::unique_ptr<ConcreteService> m_service;


	public:
		//�R���X�g���N�^
		ServiceValHolder(std::unique_ptr<ConcreteService>&& service)
			: m_service(std::move(service))
		{
		}

		//���|�C���^�\��Ԃ�
		Service* Get() const
		{
			return m_service.get();
		}
};


template<typename Service>
std::unique_ptr<typename ServiceLocator<Service>::IServiceHolder> ServiceLocator<Service>::s_serviceHolder;
