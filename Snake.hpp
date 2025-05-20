#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>
#include <utility>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake
{
public:
    using Coord = std::pair<int, int>;

    explicit Snake(Coord start);

    void setDirection(Direction dir);
    Direction getDirection() const;

    void move(bool grow = false);
    const std::deque<Coord> &getBody() const;
    Coord getHead() const;
    bool checkSelfCollision() const;

private:
    std::deque<Coord> body;
    Direction currentDir;
    Direction nextDir;
};

#endif
