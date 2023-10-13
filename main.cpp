#include <iostream>
#include "tetramino.hpp"
#include "tetris.hpp"
#include <thread>
using namespace std;
int main()
{
    Tetris t;
    t.spawn(1,1,Tetris::tet_bar);
    std::thread p();
    t.GameLoop();
    return 0;
}