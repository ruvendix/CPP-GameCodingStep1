// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>

// 문제가 해결된 상황을 보고 싶으면
// 아래에 있는 디파인값을 주석 처리해주세요.
#define NO_LSP

#ifdef NO_LSP
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
#else
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
#endif

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
int main()
{
#ifdef NO_LSP
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
    printf("\n");
#else
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
    printf("\n");
#endif

    return 0;
}