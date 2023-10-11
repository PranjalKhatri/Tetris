#ifndef _TETRIS_HPP_
#define _TETRIS_HPP_
#include "tetramino.hpp"
#include <windows.h>
#include "utils.hpp"

class Tetris
{
private:
    const int SCREENWIDTH = 12;
    const int SCREENHEIGHT = 18;
    unsigned char* playing_field;
    unsigned char* last_playing_field;
    bool m_isrunning;
    Random random;
    bool can_godown;
    Tetramino* last_spawn = nullptr;
    int last_posX, last_posY;
public:

private:
    bool DoesPieceFit(Tetramino t, int PosX, int PosY);
public:
    Tetris();
    void GameLoop();
    void Display_Field();
    void spawn(int posX, int posY);
    void Move(int x, int y);
    bool IsRunning(void) { return m_isrunning; }
    ~Tetris();
};

bool Tetris::DoesPieceFit(Tetramino t, int PosX, int PosY)
{
    vector<vector<int>> arr = t.GetPiece();
    for (int i = 0; i < t.GetWidth(); i++)
    {
        for (int j = 0; j < t.GetHeight(); j++)
        {
            //check if index is occupied in the piece and on the board (previously)
            //i+posy denotes column , 
            if (arr[j][i] == 1 && last_playing_field[((j + PosX) * SCREENWIDTH) - i + PosY] != ' ') {
                return false;
            }
        }
    }
    return true;
}

Tetris::Tetris()
{
    can_godown = true;
    m_isrunning = true;
    last_spawn = nullptr;
    playing_field = new unsigned char[SCREENWIDTH * SCREENHEIGHT];//initializee the field
    last_playing_field = new unsigned char[SCREENWIDTH * SCREENHEIGHT];//initializee the field
    for (int x = 0; x < SCREENWIDTH; x++)
    {
        for (int y = 0; y < SCREENHEIGHT; y++)
        {
            playing_field[y * SCREENWIDTH + x] = (x == 0 || x == SCREENWIDTH - 1 || y == 0 || y == SCREENHEIGHT - 1) ? '#' : ' ';
            last_playing_field[y * SCREENWIDTH + x] = (x == 0 || x == SCREENWIDTH - 1 || y == 0 || y == SCREENHEIGHT - 1) ? '#' : ' ';
        }
    }
}

void Tetris::GameLoop()
{

    //Timings

    //Input

    //Logic
    if (last_spawn != nullptr) {
        Move(0, 1);
    }
    //output
    system("cls");
    Display_Field();
    Sleep(100);
}

void Tetris::Display_Field()
{
    // playing_field[9*SCREENWIDTH+1] = '#';
    // playing_field[9*SCREENWIDTH+2] = '#';
    for (int i = 0; i < SCREENWIDTH; i++)
    {
        for (int j = 0; j < SCREENHEIGHT; j++)
        {
            // cout<<(j*SCREENWIDTH +i)<<" ";
            cout << playing_field[j * SCREENWIDTH + i];
        }
        cout << endl;
    }

}
//x left, y below
void Tetris::Move(int x, int y) {
    if (DoesPieceFit((*last_spawn), (last_posX - x), (last_posY + y))) {
        vector<vector<int>> arr = last_spawn->GetPiece();
        // cout<<"pop"<<last_spawn->GetPiece()[0][0]<<" pop";
        for (int i = 0; i < last_spawn->GetWidth(); i++)
        {
            for (int j = 0; j < last_spawn->GetHeight(); j++)
            {
                if ((arr[j][i] == 1) && (playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] == 'P')) {
                    // cout << "arr[" << j << "][" << i << "]" << arr[j][i] << " ";
                    // cout << "emptied " << ((j + last_posX) * SCREENWIDTH) - i + last_posY << " \n";
                    playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = ' ';

                    // cout << "filled " << ((j + last_posX - x) * SCREENWIDTH) - i + last_posY + y << " \n";

                    playing_field[((j + last_posX - x) * SCREENWIDTH) - i + last_posY + y] = 'P';

                    last_playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = 'P';
                }
            }
        }
        cout << "emptied field\n";
        // Display_Field();
        // last_playing_field = playing_field;
        // for (int i = 0; i < last_spawn->GetWidth(); i++)
        // {/
            // for (int j = 0; j < last_spawn->GetHeight(); j++)
            // {
                // if (arr[j][i] == 1) {

                // }
            // }
        // }
        // cout<<"YT";
        last_posX -= x;
        last_posY += y;
    }
    else {
        delete last_spawn;
        last_spawn = nullptr;
    }
}

void Tetris::spawn(int posX, int posY)
{
    char ar[5] = { '0','1','2','3','\0' };
    Tetramino spawned = Tetramino(2, 2, ar);
    int spwidth = spawned.GetWidth();
    int spheight = spawned.GetHeight();
    vector<vector<int>> sparr = spawned.GetPiece();
    if (DoesPieceFit(spawned, posX, posY)) {
        for (int i = 0; i < spwidth; i++)
        {
            for (int j = 0; j < spheight; j++)
            {
                //check if index is occupied in the piece and on the board
                //i+posy denotes column , 
                if (sparr[j][i] == 1) {
                    cout << " filled" << ((j + posX) * SCREENWIDTH) - i + posY << "\n";
                    playing_field[((j + posX) * SCREENWIDTH) - i + posY] = 'P';
                }
            }
        }
        last_spawn = new Tetramino(spheight, spwidth, ar);
        last_posX = posX;
        last_posY = posY;
        // Display_Field();
    }//cant spawn game over
    else {
        m_isrunning = false;
    }
    //change last state to current but after movement
    // last_playing_field = playing_field;
}

Tetris::~Tetris()
{
    delete last_spawn;
    delete[] playing_field;
}

#endif