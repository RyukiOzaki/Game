//�Q�[���R���e�L�X�g�N���X
#pragma once
#include"ServiceLocator.h"

class GameContext final
{
	public:
		//�o�^
		template<typename Context, typename ConcreteContext>
		static void Register(ConcreteContext* context)
		{
			ServiceLocator<Context>::Register(context);
		}

		//���j�[�N�|�C���^�̓o�^
		template<typename Context, typename ConcreteContext>
		static void Register(std::unique_ptr<ConcreteContext>& context)
		{
			ServiceLocator<Context>::Register(context);
		}

		//���j�[�N�|�C���^�̏��L�����ړ�
		template<typename Context, typename ConcreteContext>
		static void Register(std::unique_ptr<ConcreteContext>&& context)
		{
			ServiceLocator<Context>::Register(std::move(context));
		}
		
		//�o�^����Ă�����̂̃|�C���^��Ԃ�
		template<typename Context>
		static Context* Get()
		{
			return ServiceLocator<Context>::Get();
		}

		//�w�肵�����̂�����
		template<typename Context>
		static void Reset()
		{
			ServiceLocator<Context>::Reset();
		}
};
