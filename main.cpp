#include "Timer.hpp"
#include "Input.hpp"
#include "Game.hpp"
#include <iostream>
#include <csignal>
#include <atomic>

std::atomic<bool> running = true;

void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        running = false;
    }
}

int main()
{
    Game game(40, 20);
    setNonBlockingInput(true);

    constexpr double TICK_RATE = 15.0;
    Timer timer(TICK_RATE);
    std::signal(SIGINT, handleSignal);

    std::cout << "\033[2J\033[H";

    while (running && !game.isGameOver())
    {
        char input = readInputChar();
        switch (input)
        {
        case 'w':
            game.changeDirection(Direction::UP);
            break;
        case 's':
            game.changeDirection(Direction::DOWN);
            break;
        case 'a':
            game.changeDirection(Direction::LEFT);
            break;
        case 'd':
            game.changeDirection(Direction::RIGHT);
            break;
        }

        game.update();
        game.render();
        timer.waitNextTick();
    }

    setNonBlockingInput(false);
    std::cout << "\033[2J\033[H";
    std::cout << "Game exited cleanly.\n";

    return 0;
}
