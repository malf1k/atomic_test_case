#include "colorobject.h"

ColorObject::ColorObject(Color color)
    : m_color(color)
{

}


void ColorObject::setColor(Color color)
{
    m_color = color;

}

Color ColorObject::getColor()
{
    return m_color;
}
