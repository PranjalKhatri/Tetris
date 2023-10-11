#include <iostream>
#include "tetramino.hpp"
#include "tetris.hpp"
using namespace std;
int main()
{
    Tetris t;
    t.spawn(9, 2);
    for (int i = 0;i <= 10;i++) {
        t.GameLoop();
    }

    return 0;
}