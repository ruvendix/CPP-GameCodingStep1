// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <array>

namespace unit_test
{
	namespace basic
	{
		class Command abstract
		{
		public:
			Command() = default;
			virtual ~Command() = default;

			virtual void execute() abstract;
		};

		class Invoker
		{
		public:
			Invoker() = default;
			
			virtual ~Invoker()
			{
				ReleaseCommand();
			}

			void ReleaseCommand()
			{
				if (command != nullptr)
				{
					delete command;
				}
			}

			void executeCommand()
			{
				command->execute();
			}

			void setCommand(Command* command)
			{
				ReleaseCommand();
				this->command = command;
			}

		private:
			Command* command = nullptr;
		};

		class Receiver
		{
		public:
			Receiver() = default;
			virtual ~Receiver() = default;

			void operation(int a)
			{
				printf("Receiver::operation()\n");
			}
		};

		class Command1 : public Command
		{
		public:
			Command1(Receiver* receiver, int a)
			{
				this->a = a;
				this->receiver = receiver;
			}

			virtual ~Command1()
			{
				if (receiver != nullptr)
				{
					delete receiver;
				}
			}

			virtual void execute() override
			{
				printf("Command1::execute()\n");
				receiver->operation(a);
			}

		private:
			int a = 0;
			Receiver* receiver = nullptr;
		};

		class Command2 : public Command
		{
		public:
			Command2() = default;
			virtual ~Command2() = default;

			virtual void execute() override
			{
				printf("Command2::execute()\n");
			}
		};
	}

	namespace use_pattern
	{
		class Command abstract
		{
		public:
			Command() = default;
			virtual ~Command() = default;

			virtual void OnExcute() abstract;
			virtual void OnUndo() abstract;
			virtual void OnRedo() abstract;
		};

		class Invoker
		{
			static const int MAX_COMMAND = 10;

		public:
			Invoker()
			{
				std::fill(m_arrCommand.begin(), m_arrCommand.end(), nullptr);
			}

			virtual ~Invoker()
			{
				for (int i = 0; i < MAX_COMMAND; ++i)
				{
					if (m_arrCommand[i] != nullptr)
					{
						delete m_arrCommand[i];
					}
				}
			}

			void ExecuteCommand(Command* pCommand)
			{
				if (m_nextIdx >= MAX_COMMAND)
				{
					printf("더 이상 명령을 실행할 수 없음!\n");
					return;
				}

				pCommand->OnExcute();

				if (m_bHistroyChange == true)
				{
					// 현재 인덱스부터 끝까지 싹 정리
					for (int i = (m_nextIdx + 1); i < MAX_COMMAND; ++i)
					{
						if (m_arrCommand[i] != nullptr)
						{
							delete m_arrCommand[i];
							m_arrCommand[i] = nullptr;
						}
					}
				}

				++m_nextIdx;
				m_arrCommand[m_nextIdx] = pCommand; // Command 객체 저장				
			}

			void Undo()
			{				
				if (m_nextIdx < 0)
				{
					printf("취소할 명령이 없음!\n");
					return;
				}

				// 최근 명령을 취소하고 인덱스 감소
				m_arrCommand[m_nextIdx]->OnUndo();
				--m_nextIdx;

				m_bHistroyChange = false;
			}

			void Redo()
			{
				if (m_nextIdx > static_cast<int>(m_arrCommand.size()))
				{
					printf("재실행할 명령이 없음!\n");
					return;
				}

				// 인덱스를 증가시키고 최근 명령 재실행
				++m_nextIdx;
				m_arrCommand[m_nextIdx]->OnRedo();

				m_bHistroyChange = true;
			}

		private:
			int m_nextIdx = -1;
			bool m_bHistroyChange = false; // Undo 또는 Redo 중인지 확인
			std::array<Command*, MAX_COMMAND> m_arrCommand;
		};

		class AttackCommand : public Command
		{
		public:
			using Command::Command;
			virtual ~AttackCommand() = default;

			virtual void OnExcute() override
			{
				printf("공격!\n");
			}

			virtual void OnUndo() override
			{
				printf("공격 취소!\n");
			}

			virtual void OnRedo() override
			{
				printf("공격 재실행!\n");
			}
		};

		class DefendCommand : public Command
		{
		public:
			using Command::Command;
			virtual ~DefendCommand() = default;

			virtual void OnExcute() override
			{
				printf("방어!\n");
			}

			virtual void OnUndo() override
			{
				printf("방어 취소!\n");
			}

			virtual void OnRedo() override
			{
				printf("방어 재실행!\n");
			}
		};
	}
}

namespace unit_test
{
	namespace basic
	{
		void Test()
		{
			printf("<기본 Command 테스트!>\n\n");

			Invoker invoker;
			invoker.setCommand(new Command1(new Receiver(), 10));
			invoker.executeCommand();
			printf("\n");

			invoker.setCommand(new Command2());
			invoker.executeCommand();
			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<패턴 적용 테스트!>\n\n");

			Invoker invoker;
			invoker.ExecuteCommand(new AttackCommand());
			invoker.ExecuteCommand(new DefendCommand());
			printf("\n");

			printf("모든 명령을 취소합니다!\n");
			invoker.Undo();
			invoker.Undo();
			invoker.Undo();
			printf("\n");

			printf("공격 명령만 재실행합니다!\n");
			invoker.Redo();
			printf("\n");

			printf("새로 공격 명령을 실행해서 이전 명령 스택을 날립니다!\n");
			invoker.ExecuteCommand(new AttackCommand());
			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
	//unit_test::basic::Test();
	
	//unit_test::use_pattern::Test();
	return 0;
}