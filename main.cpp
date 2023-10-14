#include <iostream>
#include "tetramino.hpp"
#include "tetris.hpp"
#include <pthread.h>

using namespace std;
int main()
{
    pthread_t ptid;
    Tetris t;
    pthread_create(&ptid,NULL,&(Tetris::GetInput),(void*)&t);
    t.spawn(1,1,Tetris::tet_bar);
    t.GameLoop();
    pthread_join(ptid,NULL);
    // Sleep(100);
    
    return 0;
}