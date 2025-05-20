#include "Snake.hpp"

Snake::Snake(Coord start)
    : currentDir(Direction::RIGHT), nextDir(Direction::RIGHT)
{
    body.push_front(start);
}

void Snake::setDirection(Direction dir)
{
    if ((currentDir == Direction::UP && dir == Direction::DOWN) ||
        (currentDir == Direction::DOWN && dir == Direction::UP) ||
        (currentDir == Direction::LEFT && dir == Direction::RIGHT) ||
        (currentDir == Direction::RIGHT && dir == Direction::LEFT))
    {
        return;
    }
    nextDir = dir;
}

Direction Snake::getDirection() const
{
    return currentDir;
}

Snake::Coord Snake::getHead() const
{
    return body.front();
}

const std::deque<Snake::Coord> &Snake::getBody() const
{
    return body;
}

void Snake::move(bool grow)
{
    currentDir = nextDir;

    Coord head = body.front();
    switch (currentDir)
    {
    case Direction::UP:
        --head.second;
        break;
    case Direction::DOWN:
        ++head.second;
        break;
    case Direction::LEFT:
        --head.first;
        break;
    case Direction::RIGHT:
        ++head.first;
        break;
    }

    body.push_front(head);
    if (!grow)
    {
        body.pop_back();
    }
}

bool Snake::checkSelfCollision() const
{
    const Coord &head = body.front();
    for (size_t i = 1; i < body.size(); ++i)
    {
        if (body[i] == head)
            return true;
    }
    return false;
}
