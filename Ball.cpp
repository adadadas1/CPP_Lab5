#include "Ball.hpp"
#include <cmath>

void Ball::setVelocity(const Velocity& velocity) {
    m_velocity = velocity;
}

Velocity Ball::getVelocity() const {
    return m_velocity;
}

/**
 * Ball абстрагирован от способа отображения — рисование делегируется Painter.
 * Painter предоставляется извне (инверсия зависимостей).
 */
void Ball::draw(Painter& painter) const {
    painter.draw(m_center, m_radius, m_color);
}

void Ball::setCenter(const Point& center) {
    m_center = center;
}

Point Ball::getCenter() const {
    return m_center;
}

double Ball::getRadius() const {
    return m_radius;
}

// Масса пропорциональна объёму шара: (4/3) * PI * r^3
double Ball::getMass() const {
    return M_PI * m_radius * m_radius * m_radius * 4.0 / 3.0;
}

bool Ball::isCollidable() const {
    return m_isCollidable;
}

void Ball::setIsCollidable(bool value) {
    m_isCollidable = value;
}

void Ball::setRadius(double radius) {
    m_radius = radius;
}

void Ball::setColor(const Color& color) {
    m_color = color;
}
