#include <iostream>
#include "tetramino.hpp"
#include "tetris.hpp"
using namespace std;
int main()
{
    Tetris t;
    t.spawn(1,1,Tetris::tet_bar);
    
    t.GameLoop();
    return 0;
}