// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include <cstdio>

// ������ �ذ�� ��Ȳ�� ���� ������
// �Ʒ��� �ִ� �����ΰ��� �ּ� ó�����ּ���.
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
// ���α׷��� ���۵Ǵ� ���̿���.
int main()
{
#ifdef NO_LSP
    Rectangle rectangle;
    rectangle.setWidth(10);

    int width = rectangle.getWidth();
    rectangle.setHeight(8);

    printf("���簢���� ���� �м�\n");
    printf("width: %d\tgetWidth(): %d\n", width, rectangle.getWidth());
    printf("\n");

    Square square;
    square.setWidth(10);

    width = square.getWidth();
    square.setHeight(8);

    printf("���簢���� ���� �м�\n");
    printf("width: %d\tgetWidth(): %d\n", width, square.getWidth());
    printf("\n");
#else
    Shape shape; // Shape ��� Rectangle �Ǵ� Square�� ���� �ƹ� ���� ����!

    // ������ Rectangle�� Square�� �θ�����
    // ������ Shape�� Square�� �θ��̹Ƿ� �����ϰ� ������ �ʿ䰡 ����!

    Rectangle rectangle;
    rectangle.setWidth(10);

    int width = rectangle.getWidth();
    rectangle.setHeight(8);

    printf("���簢���� ���� �м�\n");
    printf("width: %d\tgetWidth(): %d\n", width, rectangle.getWidth());
    printf("\n");

    Square square;
    square.setLength(10);

    int length = square.getLength();

    printf("���簢���� ���� �м�\n");
    printf("length: %d\tgetLength(): %d\n", length, square.getLength());
    printf("\n");
#endif

    return 0;
}