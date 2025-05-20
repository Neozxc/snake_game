#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"
#include <random>

class Game
{
public:
    using Coord = std::pair<int, int>;

    Game(int width, int height);

    void update();
    void changeDirection(Direction dir);
    void render() const;
    bool isGameOver() const;

private:
    int width;
    int height;
    Snake snake;
    Coord food;
    bool gameOver;

    mutable std::mt19937 rng;
    std::uniform_int_distribution<int> distX;
    std::uniform_int_distribution<int> distY;

    void placeFood();
    bool isWallCollision(const Snake::Coord &head) const;
};

#endif
