#pragma once

enum class Color{
    NONE = 0,
    RED,
    GREEN,
    BLUE
};

/**
 * @brief The ColorObject class
 * Описывает объект содержащий цвет
 */
class ColorObject
{
public:
    ColorObject(Color color = Color::NONE)
        : m_color(color)
    {

    }

    void setColor(Color color)
    {
        m_color = color;

    }
    Color getColor()
    {
        return m_color;
    }

    friend bool operator == (const ColorObject& co1, const ColorObject& co2)
    {
        return co1.m_color == co2.m_color;
    }
    friend bool operator != (const ColorObject& co1, const ColorObject& co2)
    {
        return !(co1 == co2);
    }

private:
    Color m_color = Color::NONE;
};


