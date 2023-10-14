#include <iostream>
#include "..\include\tetramino.hpp"
#include "..\include\tetris.hpp"
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
    Sleep(200);
    system("color 07");
    cin.ignore();
    
    // Sleep(100);
    
    return 0;
}