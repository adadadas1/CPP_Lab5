#include "World.h"
#include "Painter.h"
#include <fstream>

// Длительность одного тика симуляции. Изменять не следует.
static constexpr double timePerTick = 0.001;

World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    while (stream.peek(), stream.good()) {
        Point  center;
        Point  velocityVec;
        Color  color;
        double radius;
        bool   collidable;

        stream >> center >> velocityVec;
        stream >> color;
        stream >> radius;
        stream >> std::boolalpha >> collidable;

        if (!stream.good())
            break;

        Ball ball;
        ball.setCenter(center);
        ball.setVelocity(Velocity(velocityVec));
        ball.setColor(color);
        ball.setRadius(radius);
        ball.setIsCollidable(collidable);
        balls.push_back(ball);
    }
}

void World::show(Painter& painter) const {
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
}

void World::update(double time) {
    /**
     * Симуляция дискретна: время делится на тики длиной timePerTick.
     * Остаток времени (restTime) накапливается и учитывается в следующем update,
     * чтобы не терять дробную часть при вычислении числа тиков.
     */
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, ticks);
}
