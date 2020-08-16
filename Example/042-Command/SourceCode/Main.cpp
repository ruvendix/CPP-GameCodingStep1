// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
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
					printf("�� �̻� ����� ������ �� ����!\n");
					return;
				}

				pCommand->OnExcute();

				if (m_bHistroyChange == true)
				{
					// ���� �ε������� ������ �� ����
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
				m_arrCommand[m_nextIdx] = pCommand; // Command ��ü ����				
			}

			void Undo()
			{				
				if (m_nextIdx < 0)
				{
					printf("����� ����� ����!\n");
					return;
				}

				// �ֱ� ����� ����ϰ� �ε��� ����
				m_arrCommand[m_nextIdx]->OnUndo();
				--m_nextIdx;

				m_bHistroyChange = false;
			}

			void Redo()
			{
				if (m_nextIdx > static_cast<int>(m_arrCommand.size()))
				{
					printf("������� ����� ����!\n");
					return;
				}

				// �ε����� ������Ű�� �ֱ� ��� �����
				++m_nextIdx;
				m_arrCommand[m_nextIdx]->OnRedo();

				m_bHistroyChange = true;
			}

		private:
			int m_nextIdx = -1;
			bool m_bHistroyChange = false; // Undo �Ǵ� Redo ������ Ȯ��
			std::array<Command*, MAX_COMMAND> m_arrCommand;
		};

		class AttackCommand : public Command
		{
		public:
			using Command::Command;
			virtual ~AttackCommand() = default;

			virtual void OnExcute() override
			{
				printf("����!\n");
			}

			virtual void OnUndo() override
			{
				printf("���� ���!\n");
			}

			virtual void OnRedo() override
			{
				printf("���� �����!\n");
			}
		};

		class DefendCommand : public Command
		{
		public:
			using Command::Command;
			virtual ~DefendCommand() = default;

			virtual void OnExcute() override
			{
				printf("���!\n");
			}

			virtual void OnUndo() override
			{
				printf("��� ���!\n");
			}

			virtual void OnRedo() override
			{
				printf("��� �����!\n");
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
			printf("<�⺻ Command �׽�Ʈ!>\n\n");

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
			printf("<���� ���� �׽�Ʈ!>\n\n");

			Invoker invoker;
			invoker.ExecuteCommand(new AttackCommand());
			invoker.ExecuteCommand(new DefendCommand());
			printf("\n");

			printf("��� ����� ����մϴ�!\n");
			invoker.Undo();
			invoker.Undo();
			invoker.Undo();
			printf("\n");

			printf("���� ��ɸ� ������մϴ�!\n");
			invoker.Redo();
			printf("\n");

			printf("���� ���� ����� �����ؼ� ���� ��� ������ �����ϴ�!\n");
			invoker.ExecuteCommand(new AttackCommand());
			printf("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
	//unit_test::basic::Test();
	
	//unit_test::use_pattern::Test();
	return 0;
}