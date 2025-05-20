#include "Game.hpp"
#include <iostream>
#include <unordered_set>
#include <algorithm>

Game::Game(int width_, int height_)
    : width(width_), height(height_),
      snake({width / 2, height / 2}),
      gameOver(false),
      rng(std::random_device{}()),
      distX(1, width - 2),
      distY(1, height - 2)
{
    placeFood();
}

void Game::update()
{
    if (gameOver)
        return;

    Snake::Coord nextHead = snake.getHead();
    switch (snake.getDirection())
    {
    case Direction::UP:
        --nextHead.second;
        break;
    case Direction::DOWN:
        ++nextHead.second;
        break;
    case Direction::LEFT:
        --nextHead.first;
        break;
    case Direction::RIGHT:
        ++nextHead.first;
        break;
    }

    bool grow = (nextHead == food);
    snake.move(grow);

    if (grow)
    {
        placeFood();
    }

    if (isWallCollision(snake.getHead()) || snake.checkSelfCollision())
    {
        gameOver = true;
    }
}

void Game::changeDirection(Direction dir)
{
    snake.setDirection(dir);
}

void Game::render() const
{
    const auto &body = snake.getBody();
    std::cout << "\033[H";

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Snake::Coord cell = {x, y};

            if (cell == body.front())
            {
                std::cout << 'O';
            }
            else if (std::find(body.begin(), body.end(), cell) != body.end())
            {
                std::cout << 'o';
            }
            else if (cell == food)
            {
                std::cout << '*';
            }
            else if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
            {
                std::cout << '#';
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    std::cout << "Score: " << (body.size() - 1) << "\n";
    if (gameOver)
    {
        std::cout << "Game Over! Press Ctrl+C to quit.\n";
    }
}

bool Game::isWallCollision(const Snake::Coord &head) const
{
    return head.first <= 0 || head.first >= width - 1 ||
           head.second <= 0 || head.second >= height - 1;
}

void Game::placeFood()
{
    const auto &body = snake.getBody();

    struct CoordHash
    {
        std::size_t operator()(const std::pair<int, int> &p) const noexcept
        {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };

    std::unordered_set<Snake::Coord, CoordHash> snakeSet(body.begin(), body.end());

    do
    {
        food = {distX(rng), distY(rng)};
    } while (snakeSet.count(food));
}

bool Game::isGameOver() const
{
    return gameOver;
}
