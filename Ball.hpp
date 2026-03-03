#pragma once
#include "Color.h"
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
public:
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;

    // Флаг: нужно ли обрабатывать столкновение этого шара с другими
    bool isCollidable() const;
    void setIsCollidable(bool value);

    // Задаём радиус и цвет (устанавливаются при загрузке из файла)
    void setRadius(double radius);
    void setColor(const Color& color);

private:
    Point    m_center;
    Velocity m_velocity;
    double   m_radius       = 1.0;
    Color    m_color;
    bool     m_isCollidable = true;
};
