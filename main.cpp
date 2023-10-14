#include <iostream>
#include "tetramino.hpp"
#include "tetris.hpp"
#include <pthread.h>

using namespace std;
int main()
{
    system("color 07");
    pthread_t ptid;
    Tetris t;
    pthread_create(&ptid,NULL,&(Tetris::GetInput),(void*)&t);
    t.GameLoop();
    pthread_join(ptid,NULL);
    cout<<"Press any key to Continue...";
    cin.ignore();
    getch();
    // Sleep(100);
    
    return 0;
}