#include "Ball.hpp"
#include <cmath>

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    m_velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return m_velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(m_center, m_radius, m_color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    m_center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return m_center;
}

/**
 * @brief Возвращает радиус объекта
 */
double Ball::getRadius() const {
    return m_radius;
}

/**
 * @brief Возвращает массу объекта
 * @details масса пропорциональна объёму шара: PI * radius^3 * 4/3
 */
double Ball::getMass() const {
    return M_PI * m_radius * m_radius * m_radius * 4.0 / 3.0;
}

// Возвращает флаг коллайдируемости
bool Ball::isCollidable() const {
    return m_isCollidable;
}

// Задаёт флаг коллайдируемости
void Ball::setIsCollidable(bool value) {
    m_isCollidable = value;
}

// Задаёт радиус шара
void Ball::setRadius(double radius) {
    m_radius = radius;
}

// Задаёт цвет шара
void Ball::setColor(const Color& color) {
    m_color = color;
}
