// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 테스트를 하려면 네임스페이스를 참고해주세요.
// 예) no_LSP::UnitTest();

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
        Rectangle rectangle;
        rectangle.setWidth(10);

        int width = rectangle.getWidth();
        rectangle.setHeight(8);

        printf("직사각형의 길이 분석\n");
        printf("width: %d\tgetWidth(): %d\n", width, rectangle.getWidth());
        printf("\n");

        Square square;
        square.setWidth(10);

        width = square.getWidth();
        square.setHeight(8);

        printf("정사각형의 길이 분석\n");
        printf("width: %d\tgetWidth(): %d\n", width, square.getWidth());
    }

} // namesapce no_LSP

namespace LSP
{

    class Shape
    {
    public:
        Shape() = default;
        virtual ~Shape() = default;
    };

    class Rectangle : public Shape
    {
    public:
        using Shape::Shape;
        virtual ~Rectangle() = default;

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
		Shape shape; // Shape 대신 Rectangle 또는 Square가 들어가도 아무 문제 없음!
                     
        // 전에는 Rectangle이 Square의 부모였지만
        // 이제는 Shape이 Square의 부모이므로 동일하게 구현할 필요가 없음!

		Rectangle rectangle;
		rectangle.setWidth(10);

		int width = rectangle.getWidth();
		rectangle.setHeight(8);

		printf("직사각형의 길이 분석\n");
		printf("width: %d\tgetWidth(): %d\n", width, rectangle.getWidth());
        printf("\n");

        Square square;
        square.setLength(10);

        int length = square.getLength();

        printf("정사각형의 길이 분석\n");
        printf("length: %d\tgetLength(): %d\n", length, square.getLength());
    }

} // namespace LSP end

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
    no_LSP::UnitTest();
    //LSP::UnitTest();

    printf("\n");
    return 0;
}