#include "World.h"
#include "Painter.h"
#include <fstream>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    // Читаем границы мира через operator>>(istream, Point)
    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    // Читаем шары из файла построчно
    while (stream.peek(), stream.good()) {
        Point  center;
        Point  velocityVec;
        Color  color;
        double radius;
        bool   collidable;

        // Центр и вектор скорости
        stream >> center >> velocityVec;
        // Цвет через operator>>(istream, Color)
        stream >> color;
        // Радиус
        stream >> radius;
        // Флаг коллайдируемости
        stream >> std::boolalpha >> collidable;

        if (!stream.good())
            break;

        // Собираем объект Ball и добавляем в контейнер
        Ball ball;
        ball.setCenter(center);
        ball.setVelocity(Velocity(velocityVec));
        ball.setColor(color);
        ball.setRadius(radius);
        ball.setIsCollidable(collidable);
        balls.push_back(ball);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, ticks);
}