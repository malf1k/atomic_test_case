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
    ColorObject(Color color = Color::NONE);

    void setColor(Color color);
    Color getColor();

private:
    Color m_color = Color::NONE;
};
