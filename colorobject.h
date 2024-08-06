#pragma once

enum class Color: char{
    NONE = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

/**
 * @brief The ColorObject class
 * Описывает объект содержащий цвет
 */
class ColorObject
{
public:
    ColorObject(Color color = Color::NONE);

    void setColor(Color color);
    Color getColor();

private:
    Color m_color = Color::NONE;
};
