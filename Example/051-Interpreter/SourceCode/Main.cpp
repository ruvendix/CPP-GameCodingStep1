// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <stack>
#include <string>
#include <string_view>

namespace unit_test
{
	namespace basic
	{
		class Context
		{
		public:
			Context() = default;
			~Context() = default;
		};

		class AbstractExpression abstract
		{
		public:
			AbstractExpression() = default;
			virtual ~AbstractExpression() = default;

			virtual void Interpret(const Context& context) abstract;
		};

		class TerminalExpression : public AbstractExpression
		{
		public:
			TerminalExpression() = default;
			virtual ~TerminalExpression() = default;

			virtual void Interpret(const Context& context) override
			{
				printf("TerminalExpression::Interpret()\n");
			}
		};

		class NonterminalExpression : public AbstractExpression
		{
		public:
			NonterminalExpression() = default;
			virtual ~NonterminalExpression() = default;

			virtual void Interpret(const Context& context) override
			{
				printf("NonterminalExpression::Interpret()\n");
			}
		};
	}

	namespace use_pattern
	{
#define NULL_VIRTUAL_VOID_FUNC(VIRTUAL_FUNC) VIRTUAL_FUNC override { }
#define NULL_VIRTUAL_FUNC(VIRTUAL_FUNC, RETURN_VALUE) VIRTUAL_FUNC override { return RETURN_VALUE; }

		class Token
		{
		public:
			enum class EType : int
			{
				NONE = 0,
				INT,
				PLUS,
				MINUS,
				LPAREN,
				RPAREN,
			};

			Token() = default;
			~Token() = default;

			Token(EType type, const std::string& strValue) :
				m_type(type),
				m_strValue(strValue)
			{

			}

			EType getType() const
			{
				return m_type;
			}

			const std::string& getValue() const
			{
				return m_strValue;
			}

		private:
			EType m_type = EType::NONE;
			std::string m_strValue;
		};

		class AbstractExpression abstract
		{
		public:
			AbstractExpression() = default;
			virtual ~AbstractExpression() = default;

			virtual void OnInterpret(const Token& token) abstract;
			virtual int OnEvaluate() const abstract;
		};

		class TerminalExpression : public AbstractExpression
		{
		public:
			TerminalExpression() = default;
			virtual ~TerminalExpression() = default;

			// ISP�� ���������� �������� ����!
			NULL_VIRTUAL_VOID_FUNC(virtual void OnInterpret(const Token& token))
			NULL_VIRTUAL_FUNC(virtual int OnEvaluate() const, 0)
		};

		class NonterminalExpression : public AbstractExpression
		{
		public:
			NonterminalExpression() = default;
			virtual ~NonterminalExpression() = default;
			
			// ISP�� ���������� �������� ����!
			NULL_VIRTUAL_VOID_FUNC(virtual void OnInterpret(const Token& token))
			NULL_VIRTUAL_FUNC(virtual int OnEvaluate() const, 0)
		};

		class Integer : public TerminalExpression
		{
		public:
			using TerminalExpression::TerminalExpression;
			virtual ~Integer() = default;

			virtual void OnInterpret(const Token& token) override
			{
				m_value = std::stoi(token.getValue());
			}

			virtual int OnEvaluate() const override
			{
				return m_value;
			}

		private:
			int m_value = 0;
		};

		class BinaryOperation : public NonterminalExpression
		{
		public:
			enum class EType
			{
				NONE = 0,
				ADDTION,
				SUBTRACTION,
			};

			using NonterminalExpression::NonterminalExpression;
			
			virtual ~BinaryOperation()
			{
				if (m_pLHS != nullptr)
				{
					delete m_pLHS;
				}

				if (m_pRHS != nullptr)
				{
					delete m_pRHS;
				}
			}

			virtual void OnInterpret(const Token& token) override
			{
				if (token.getValue() == "+")
				{
					m_type = EType::ADDTION;
				}
				else if (token.getValue() == "-")
				{
					m_type = EType::SUBTRACTION;
				}
			}

			virtual int OnEvaluate() const override
			{
				int result = 0;

				if (m_type == EType::ADDTION)
				{
					result = (m_pLHS->OnEvaluate() + m_pRHS->OnEvaluate());
				}
				else if (m_type == EType::SUBTRACTION)
				{
					result = (m_pLHS->OnEvaluate() - m_pRHS->OnEvaluate());
				}

				return result;
			}

			bool IsExistLHS() const
			{
				return (m_pLHS != nullptr);
			}

			bool IsExistRHS() const
			{
				return (m_pRHS != nullptr);
			}

			AbstractExpression* getLHS() const
			{
				return m_pLHS;
			}
			void setLHS(AbstractExpression* pLHS)
			{
				m_pLHS = pLHS;
			}

			AbstractExpression* getRHS() const
			{
				return m_pRHS;
			}
			void setRHS(AbstractExpression* pRHS)
			{
				m_pRHS = pRHS;
			}

			EType getType() const
			{
				return m_type;
			}
			void setType(EType type)
			{
				m_type = type;
			}

		private:
			EType m_type = EType::NONE;
			AbstractExpression* m_pLHS = nullptr;
			AbstractExpression* m_pRHS = nullptr;
		};

		class Context
		{
		public:
			Context() = default;
			~Context() = default;

			bool Interpret(const std::string_view& strContents)
			{
				// Lexer�� �̿��ؼ� Token �����
				const std::vector<Token>& vecToken = LexContents(strContents);
				ShowTokens(vecToken);

				// Parser�� �̿��ؼ� AST �����
				const AbstractExpression* pAST = ParseToken(vecToken);

				// AST�� �̿��ؼ� �ǹ� �˾Ƴ���
				int result = pAST->OnEvaluate();
				printf("AST�� �̿��ؼ� �ǹ̸� �˾Ƴ��ϴ�.\n");
				printf("%s = %d\n", strContents.data(), result);

				delete pAST;
				return true;
			}

			std::vector<Token> LexContents(const std::string_view& strContents)
			{
				std::vector<Token> vecToken;

				auto iterEnd = strContents.end();
				for (auto iter = strContents.begin(); iter != iterEnd; ++iter)
				{
					switch (*iter)
					{
					case '+':
					{
						vecToken.emplace_back(Token::EType::PLUS, "+");
						break;
					}

					case '-':
					{
						vecToken.emplace_back(Token::EType::MINUS, "-");
						break;
					}

					case '(':
					{
						vecToken.emplace_back(Token::EType::LPAREN, "(");
						break;
					}

					case ')':
					{
						vecToken.emplace_back(Token::EType::RPAREN, ")");
						break;
					}

					// ������ ����
					case ' ':
					{
						break;
					}

					default:
					{
						// ���ڰ��� �ƴ� ������ �˾Ƴ��� �մϴ�.
						auto untilNotDigit = std::find_if(iter, iterEnd,
							[](const auto& value)
							{
								return (std::isdigit(value) == false);
							});

						vecToken.emplace_back(Token::EType::INT, std::string(iter, untilNotDigit));
						
						// untilNotDigit�� ���ڰ� �ƴ� ��ġ�ϱ� �����ؾ� �ؿ�!
						iter = --untilNotDigit;
						break;
					}
					}
				}

				return std::move(vecToken);
			}

			BinaryOperation* ParseToken(const std::vector<Token>& vecToken)
			{
				// �ǹ̸� �˾Ƴ��� ���� �ٽ� �κ�!				
				BinaryOperation* pAST = new BinaryOperation();

				auto iterEnd = vecToken.end();
				for (auto iter = vecToken.begin(); iter != iterEnd; ++iter)
				{
					switch (iter->getType())
					{
					case Token::EType::INT:
					{
						Integer* pInteger = new Integer();
						pInteger->OnInterpret(*iter);

						if (pAST->IsExistLHS() == false)
						{							
							pAST->setLHS(pInteger);
						}
						else if (pAST->IsExistRHS() == false)
						{
							pAST->setRHS(pInteger);
						}
						// SubAST�� �ѱ�ϴ�.
						else
						{
							dynamic_cast<BinaryOperation*>(pAST->getRHS())->setRHS(pInteger);
						}

						break;
					}

					case Token::EType::PLUS:
					case Token::EType::MINUS:
					{
						if (pAST->getType() == BinaryOperation::EType::NONE)
						{
							pAST->OnInterpret(*iter);
						}
						else
						{
							BinaryOperation* pSubAST = new BinaryOperation();
							pSubAST->setLHS(pAST->getRHS());
							pSubAST->OnInterpret(*iter);
							pAST->setRHS(pSubAST);
						}

						break;
					}

					case Token::EType::LPAREN:
					{
						// �ݴ� ��ȣ�� �ִ��� �˾Ƴ��� �մϴ�.
						auto untilRParen = std::find_if(iter, iterEnd,
							[](const Token& token)
							{
								return (token.getType() == Token::EType::RPAREN);
							});

						// ���� ��ȣ�� �ִµ� �ݴ� ��ȣ�� ���� ����Դϴ�.
						if (untilRParen == iterEnd)
						{
							delete pAST;
							return nullptr;
						}

						std::vector<Token> vecSubToken(iter + 1, untilRParen);
						if (pAST->IsExistLHS() == false)
						{
							pAST->setLHS(ParseToken(vecSubToken));
						}
						else if (pAST->IsExistRHS() == false)
						{
							pAST->setRHS(ParseToken(vecSubToken));
						}
						// SubAST�� �ѱ�ϴ�.
						else
						{
							dynamic_cast<BinaryOperation*>(pAST->getRHS())->setRHS(ParseToken(vecSubToken));
						}

						// �ݴ� ��ȣ ��ġ�� �����ؾ� ���� ��ġ�� �� �� �־��!
						iter = untilRParen;
						break;
					}
					}
				}

				return pAST;
			}

			void ShowTokens(const std::vector<Token>& vecToken)
			{
				printf("Lexer�� ������� Token���� ����մϴ�.\n");
				printf("========================================\n");
				for (const auto& iter : vecToken)
				{
					printf("%s\n", iter.getValue().c_str());
				}
				printf("========================================\n");
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
			printf("<�⺻ Interpreter �׽�Ʈ!>\n\n");

			std::vector<AbstractExpression*> vecExpression;
			vecExpression.push_back(new TerminalExpression());
			vecExpression.push_back(new TerminalExpression());
			vecExpression.push_back(new NonterminalExpression());
			vecExpression.push_back(new TerminalExpression());

			Context context;
			for (const auto& iter : vecExpression)
			{
				iter->Interpret(context);
			}

			for (auto& iter : vecExpression)
			{
				delete iter;
			}

			printf("\n");
		}
	}

	namespace use_pattern
	{
		void Test()
		{
			printf("<���� ���� �׽�Ʈ!>\n\n");

			Context context;
			context.Interpret("(5 + 3 - 26 + 126) - (31 + 52)"); // 25

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