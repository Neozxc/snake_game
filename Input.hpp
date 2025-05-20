#ifndef INPUT_HPP
#define INPUT_HPP

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

inline void setNonBlockingInput(bool enable)
{
    static struct termios oldt;
    static bool isSet = false;

    if (enable && !isSet)
    {
        struct termios newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
        isSet = true;
    }
    else if (!enable && isSet)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, 0);
        isSet = false;
    }
}

inline char readInputChar()
{
    char c = 0;
    ::read(STDIN_FILENO, &c, 1);
    return c;
}

#endif
