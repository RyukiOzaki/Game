//ゲームコンテキストクラス
#pragma once
#include"ServiceLocator.h"

class GameContext final
{
	public:
		//登録
		template<typename Context, typename ConcreteContext>
		static void Register(ConcreteContext* context)
		{
			ServiceLocator<Context>::Register(context);
		}

		//ユニークポインタの登録
		template<typename Context, typename ConcreteContext>
		static void Register(std::unique_ptr<ConcreteContext>& context)
		{
			ServiceLocator<Context>::Register(context);
		}

		//ユニークポインタの所有権を移動
		template<typename Context, typename ConcreteContext>
		static void Register(std::unique_ptr<ConcreteContext>&& context)
		{
			ServiceLocator<Context>::Register(std::move(context));
		}
		
		//登録されているもののポインタを返す
		template<typename Context>
		static Context* Get()
		{
			return ServiceLocator<Context>::Get();
		}

		//指定したものを消す
		template<typename Context>
		static void Reset()
		{
			ServiceLocator<Context>::Reset();
		}
};
