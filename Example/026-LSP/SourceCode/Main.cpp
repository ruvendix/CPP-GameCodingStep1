// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �׽�Ʈ�� �Ϸ��� ���ӽ����̽��� �������ּ���.
// ��) no_LSP::UnitTest();

#include <cstdio>

namespace no_LSP
{

	class Rectangle
	{
	public:
		Rectangle() = default;
		virtual ~Rectangle() = default;

		int getWidth() const
		{
			return m_width;
		};

		int getHeight() const
		{
			return m_height;
		};

		virtual void setWidth(int width)
		{
			m_width = width;
		}

		virtual void setHeight(int height)
		{
			m_height = height;
		}

	private:
		int m_width = 0;
		int m_height = 0;
	};

	class Square : public Rectangle
	{
	public:
		using Rectangle::Rectangle;
		virtual ~Square() = default;

		virtual void setWidth(int width) override
		{
			Rectangle::setWidth(width);
			Rectangle::setHeight(width);
		}

		virtual void setHeight(int height) override
		{
			Rectangle::setHeight(height);
			Rectangle::setWidth(height);
		}
	};

	void UnitTest()
	{
		//////////////////////////////////////////////////////////////////
		// �θ� Ŭ���� �׽�Ʈ
		Rectangle rectangle;
		rectangle.setWidth(10);

		int width = rectangle.getWidth();
		rectangle.setHeight(8);

		printf("���簢���� ���� �м�\n");
		printf("width: %d\tgetWidth(): %d\n", width, rectangle.getWidth());
		printf("\n");
		//////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////
		// �ڽ� Ŭ���� �׽�Ʈ(���� �ڵ忡�� �θ� Ŭ������ �ڽ� Ŭ������ �ٲٱ�)
		Square square;
		square.setWidth(10);

		width = square.getWidth();
		square.setHeight(8); // ���⼭ ���� ���̵� ����Ǵ� ���� �߻�

		printf("���簢���� ���� �м�\n");
		printf("width: %d\tgetWidth(): %d\n", width, square.getWidth());
		//////////////////////////////////////////////////////////////////
	}

} // namesapce no_LSP

namespace LSP
{

	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;

		virtual int CalcArea() abstract;
	};

	class Rectangle : public Shape
	{
	public:
		using Shape::Shape;
		virtual ~Rectangle() = default;

		virtual int CalcArea() override
		{
			return (m_width * m_height);
		}

		int getWidth() const
		{
			return m_width;
		};

		int getHeight() const
		{
			return m_height;
		};

		void setWidth(int width)
		{
			m_width = width;
		}

		void setHeight(int height)
		{
			m_height = height;
		}

	private:
		int m_width = 0;
		int m_height = 0;
	};

	class Square : public Shape
	{
	public:
		using Shape::Shape;
		virtual ~Square() = default;

		virtual int CalcArea() override
		{
			return (m_length * m_length);
		}

		int getLength() const
		{
			return m_length;
		}

		void setLength(int length)
		{
			m_length = length;
		}

	private:
		int m_length = 0;
	};

	void UnitTest()
	{
		// ������ Rectangle�� Square�� �θ� Ŭ����������
		// ������ Shape�� Square�� �θ� Ŭ�����ϱ� �����ϰ� ������ �ʿ䰡 ����!
		// ��, �θ� Ŭ������ �� ��ġ�� �ڽ� Ŭ������ ���� ���� �۵��Ǿ�� ��!

		//////////////////////////////////////////////////////////////////
		// Rectangle �׽�Ʈ(�ڽ� Ŭ����)
		Rectangle rectangle;
		rectangle.setWidth(10);

		int width = rectangle.getWidth();
		rectangle.setHeight(8);

		printf("���簢���� ���̿� ���� �м�\n");
		printf("width: %d\tgetWidth(): %d\t\t����: %d\n",
			width, rectangle.getWidth(), rectangle.CalcArea()); // �θ� Ŭ������ �������̽�
		printf("\n");
		//////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////
		// Square �׽�Ʈ(�ڽ� Ŭ����)
		Square square;
		square.setLength(10);

		int length = square.getLength();

		printf("���簢���� ���̿� ���� �м�\n");
		printf("length: %d\tgetLength(): %d\t\t����: %d\n",
			length, square.getLength(), square.CalcArea()); // �θ� Ŭ������ �������̽�
		//////////////////////////////////////////////////////////////////
	}

} // namespace LSP end 

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
	//no_LSP::UnitTest();
	LSP::UnitTest();

	return 0;
}