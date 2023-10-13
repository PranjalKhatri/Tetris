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
    bool m_isrunning = true;
    Random random;
    bool can_godown = true;
    Tetramino* last_spawn = nullptr;
    int last_posX = 0, last_posY = 0;
    Tetramino tets[5];
public:
    enum tet_types {
        tet_square,
        tet_l,
        tet_s,
        tet_bar,
        tet_t,
        tet_rand
    };

private:
    bool DoesPieceFit(Tetramino t, int PosX, int PosY);
    void InitTetraminos();
public:
    Tetris();
    void GameLoop();
    void Display_Field();
    void spawn(int posX, int posY, tet_types t = tet_rand);
    void Move(int x, int y);
    vector<char> CheckRow();
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
            if (arr[j][i] == 1 && (playing_field[((j + PosX) * SCREENWIDTH) - i + PosY] != ' ' && playing_field[((j + PosX) * SCREENWIDTH) - i + PosY] != '0')) {
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
    InitTetraminos();
}

void Tetris::GameLoop()
{
    int k = 1;
    while (m_isrunning) {
        //Timings

        //Input

        //Logic
        if (last_spawn != nullptr) {
            Move(0, 1);
        }
        else {
            spawn(last_posX + 4 * k, 1, Tetris::tet_bar);
            // t.spawn(9, 1, Tetris::tet_bar);
            // spawn(9, 4);
            if (last_spawn == nullptr) {
                k *= -1;
                spawn(last_posX + 4 * k, 1, Tetris::tet_bar);
                m_isrunning = true;
            }
        }
        CheckRow();
        //output
        Sleep(100);
        system("cls");
        Display_Field();

    }
    // CheckRow();
    cout << "YOU LOSE";
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
            // Sleep(1);
        }
        cout << endl;
    }

}
//x left, y below
void Tetris::Move(int x, int y) {
    vector<vector<int>> arr = last_spawn->GetPiece();
    if (DoesPieceFit((*last_spawn), (last_posX - x), (last_posY + y))) {
        // cout<<"pop"<<last_spawn->GetPiece()[0][0]<<" pop";
        for (int i = 0; i < last_spawn->GetWidth(); i++)
        {
            for (int j = 0; j < last_spawn->GetHeight(); j++)
            {
                if ((arr[j][i] == 1) && (playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] == '0')) {
                    // set pieces last position as empty
                    playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = ' ';

                    // move the current piece down 
                    playing_field[((j + last_posX - x) * SCREENWIDTH) - i + last_posY + y] = '0';
                    //update last playing field
                    last_playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = '0';
                }
            }
        }

        last_posX -= x;
        last_posY += y;
    }
    else {
        //Chage the letters
        for (int i = 0; i < last_spawn->GetWidth(); i++)
        {
            for (int j = 0; j < last_spawn->GetHeight(); j++)
            {
                if ((arr[j][i] == 1) && (playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] == '0')) {

                    playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = "ABCDEFGHIJKLMNOPQRSTUVWXXYZ"[random.GetRandomNumber(27)];

                    last_playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = 'G';
                }
            }
        }
        // delete last_spawn;
        last_spawn = nullptr;
    }
}

vector<char> Tetris::CheckRow()
{

    vector<char> rowsnums;
    for (int i = 0; i < (SCREENWIDTH); i++)
    {
        for (int j = 0; j < (SCREENHEIGHT); j++)
        {
            if (playing_field[j * SCREENWIDTH + i] == ' ') {
                break;
            }
            else {
                if (j == (SCREENHEIGHT - 1)) {
                    // cout << "   " << i << "   " << endl;
                    // Sleep(10);
                    rowsnums.push_back(i);
                }else{
                    continue;
                }
            }
        }

    }
    if (rowsnums.size() > 2) {
        rowsnums.pop_back();
        for (int i = 1; i < (rowsnums.size()); i++)
        {
            for (int j = 1; j < (SCREENHEIGHT - 1); j++)
            {
                playing_field[(j * SCREENWIDTH) + rowsnums[i]] = '=';
            }

        }
        system("cls");
        Display_Field();
        Sleep(200);
        for (int i = (SCREENWIDTH - 2); i > 1;i--)
        {
            for (int j = 0; j < SCREENHEIGHT; j++)
            {
                playing_field[j * SCREENWIDTH + i] = playing_field[j * SCREENWIDTH + i - 1];
            }

        }
    }
    return rowsnums;
   // last_playing_field = playing_field;
}

void Tetris::InitTetraminos() {
    //23 345
    //01 012
    char sq[5] = { '0','1','2','3','\0' };
    char s[5] = { '0','1','4','5','\0' };
    char l[5] = { '0','1','2','4','\0' };
    char bar[5] = { '0','1','2','3','\0' };
    char t[5] = { '1','3','4','5','\0' };
    tets[tet_square].SetVars(2, 2, sq);
    tets[tet_s].SetVars(2, 3, s);
    tets[tet_t].SetVars(2, 3, t);
    tets[tet_l].SetVars(3, 2, l);
    tets[tet_bar].SetVars(4, 1, bar);
}
void Tetris::spawn(int posX, int posY, tet_types t)
{
    int rd;
    if (t == tet_rand) {
        rd = random.GetRandomNumber(5);
    }
    else {
        rd = t;
    }
    Tetramino spawned = tets[rd];
    int spwidth = spawned.GetWidth();
    int spheight = spawned.GetHeight();
    vector<vector<int>> sparr = spawned.GetPiece();
    // playing_field[posX*SCREENWIDTH + posY] = '#';
    if (DoesPieceFit(spawned, posX, posY)) {
        for (int i = 0; i < spwidth; i++)
        {
            for (int j = 0; j < spheight; j++)
            {
                //check if index is occupied in the piece and on the board
                //i+posy denotes column , 
                if (sparr[j][i] == 1) {

                    // cout << " filled" << ((j + posX) * SCREENWIDTH) - i + posY << "\n";
                    playing_field[((j + posX) * SCREENWIDTH) - i + posY] = '0';

                }
            }
        }
        last_spawn = &tets[rd];
        last_posX = posX;
        last_posY = posY;
        // Display_Field();
    }//cant spawn game over
    else {
        last_spawn = nullptr;
        m_isrunning = false;
    }
    //change last state to current but after movement
    // last_playing_field = playing_field;
}

Tetris::~Tetris()
{
    delete[] last_spawn;
    delete[] playing_field;
    delete[] last_playing_field;
}

#endif