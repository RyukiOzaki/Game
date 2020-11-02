//サービスロケータークラス
#pragma once
#include<cassert>
#include<memory>

//サービスロケイター
template<typename Service>
class ServiceLocator final
{
	private:
		//インターフェース
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
		//ポインタのクラスの変数を作成
		template<typename ConcreteService>
		static void Register(ConcreteService* service)
		{
			s_serviceHolder = std::make_unique<ServicePtrHolder<ConcreteService>>(service);
		}
		//もっている所有権のポインタのクラスの変数を作成
		template<typename ConcreteService>
		static void Register(std::unique_ptr<ConcreteService>& service)
		{
			s_serviceHolder = std::make_unique<ServiceRefHolder<ConcreteService>>(service);
		}

		//ユニークポインタのクラスの変数を作成
		template<typename ConcreteService>
		static void Register(std::unique_ptr<ConcreteService>&& service)
		{
			s_serviceHolder = std::make_unique<ServiceValHolder<ConcreteService>>(std::move(service));
		}

		//クラスのポインタを返す
		static Service* Get()
		{
			assert(s_serviceHolder && "The service has not been registered.");

			return s_serviceHolder->Get();
		}

		//リセットする
		static void Reset()
		{
			s_serviceHolder.reset();
		}
};


//インターフェース
template<typename Service>
class ServiceLocator<Service>::IServiceHolder
{
	public:
		virtual ~IServiceHolder() = default;
		virtual Service* Get() const = 0;
};


//ポインターのフォルダー
template<typename Service>
template<typename ConcreteService>
class ServiceLocator<Service>::ServicePtrHolder final : public IServiceHolder
{
	private:
		ConcreteService* m_service;


	public:
		//コンストラクタ
		ServicePtrHolder(ConcreteService* service)
			: m_service(service)
		{
		}

		//ポインターを返す
		Service* Get() const
		{
			return m_service;
		}
};


//所有権をもらった変数のフォルダー
template<typename Service>
template<typename ConcreteService>
class ServiceLocator<Service>::ServiceRefHolder final : public IServiceHolder
{
	private:
		std::unique_ptr<ConcreteService>& m_service;


	public:
		//コンストラクタ
		ServiceRefHolder(std::unique_ptr<ConcreteService>& service)
			: m_service(service)
		{
		}

		//生ポインタ―を返す
		Service* Get() const
		{
			return m_service.get();
		}
};


//ユニークポインタから所有権を移したフォルダー
template<typename Service>
template<typename ConcreteService>
class ServiceLocator<Service>::ServiceValHolder final : public IServiceHolder
{
	private:
		std::unique_ptr<ConcreteService> m_service;


	public:
		//コンストラクタ
		ServiceValHolder(std::unique_ptr<ConcreteService>&& service)
			: m_service(std::move(service))
		{
		}

		//生ポインタ―を返す
		Service* Get() const
		{
			return m_service.get();
		}
};


template<typename Service>
std::unique_ptr<typename ServiceLocator<Service>::IServiceHolder> ServiceLocator<Service>::s_serviceHolder;
