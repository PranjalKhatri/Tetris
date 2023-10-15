#ifndef __TETRIS_HPP_
#define __TETRIS_HPP_

#pragma region include_directives
#include ".\tetramino.hpp"
#include <windows.h>
#include ".\utils.hpp"
#include <pthread.h>
#include <conio.h>
#include <iostream>
/*
// template <class T>
// class Vector2
// {
// private:
// public:
//     T x;
//     T y;
// public:
//     Vector2() = default;
//     void Set(T x,T y){
//     this->x = x;
//     this->y  =y;
// }
//     ~Vector2() = default;
// };
*/
#pragma endregion
class Tetris
{
#pragma region Variables
public:
    //Add any tetramino you define to this enum and increment size_tet_types, Plus define the tetramino inside inittetramino dunction, define them in tets_array
    enum tet_types {
        tet_square,
        tet_l,
        tet_s,
        tet_bar,
        tet_t,
        //used to denote random by tet_rand but its legacy now
        //tet_rand
    };
    static const int size_tet_types = 5;
    int current_Score = 0;
    int rowscore = 10;
    int multiplier = 2;
private:
    //Classic Tetris dimensions
    bool is_rotated = false;
    const int SCREENWIDTH = 12;
    const int SCREENHEIGHT = 18;

    //Current playing fied
    unsigned char* playing_field;
    unsigned char* last_playing_field;

    bool m_isrunning = true;
    bool can_godown = true;

    //To access our utility random class
    Random random;

    //next_spawn to display and last_spawn to run
    Tetramino* last_spawn = nullptr;
    tet_types next_spawn;

    //last positions of last_spawn
    int last_posX = 0, last_posY = 0;

    Tetramino tets[size_tet_types];
    //our input vector
    int px = 0, py = 1;

#pragma endregion

private:

    /// @brief Checks if the given Tetramino fits at the given position in the playing field
    /// @param t Tetramino to check
    /// @param PosX,PosY origin of Tetramino on board 
    /// @return true if it fits and false if it dont
    bool DoesPieceFit(Tetramino t, int PosX, int PosY);

    /// @brief initialize all your tetraminos here
    void InitTetraminos(void);
    void setcolor(int color);

public:
    /// @brief Well it rotates the piece if it can But even i dont know what is the fucking origin with respect to it is rotating 
    void Rotate();

    Tetris();

    /// @brief Main Game loop of function which hadles all the game loginc and GUI
    void GameLoop(void);

    /// @brief Displays the playing field and next Tetramino
    void Display_Field(void);

    /// @brief Spawns the given tetramino at the given position; if it cant spawn it sets last_spawn to null
    /// @param posX,posY position to spawn on
    /// @param t type of tetramino
    void spawn(int posX, int posY, tet_types t);

    /// @brief Moves the last_spawn to given location
    void Move(int x, int y, bool randomize);

    /// @brief Check if a row is compelete and gives points and move all other rows down after erasing it
    /// @return row numbers that were full
    vector<char> CheckRow(void);

    /// @brief Handles the Key Presses , works on a separate thread
    static void* GetInput(void*);

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
    int rd;
    rd = random.GetRandomNumber(5);
    next_spawn = static_cast<tet_types>(rd);
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
    playing_field[(int(SCREENHEIGHT / 2) - 1) * SCREENWIDTH] = ' ';
    playing_field[(int(SCREENHEIGHT / 2)) * SCREENWIDTH] = ' ';
    playing_field[(int(SCREENHEIGHT / 2) + 1) * SCREENWIDTH] = ' ';
    InitTetraminos();
}

void Tetris::GameLoop()
{
    while (m_isrunning) {
        //Timings

        //Input
            //Taken via threading
        //Logic
        if (is_rotated)
        {
            Rotate();

        }

        if (last_spawn != nullptr) {
            if (px != 0) {
                int i = 0;
                if (px > 0) {
                    for (i = px; i >= 0; i--)
                    {
                        if (DoesPieceFit((*last_spawn), (last_posX + i), (last_posY + py))) {
                            break;
                        }
                    }
                }
                else {
                    for (i = px; i <= 0; i++)
                    {
                        if (DoesPieceFit((*last_spawn), (last_posX + i), (last_posY + py))) {
                            break;
                        }
                    }

                }
                std::cout << "fit at px : " << i << endl;
                px = i;
            }
            if (DoesPieceFit((*last_spawn), (last_posX + px), (last_posY + py)))
            {
                Move(px, py, false);
            }
            else
            {
                Move(px, py, true);
            }
        }
        else {
            spawn(8, 3, next_spawn);
        }
        std::cout << "x " << px << " y" << -py << endl;

        //Handles the score
        std::cout << CheckRow().size();
        int s = CheckRow().size();
        s--;
        current_Score += rowscore * s;
        while (s > 0)
        {
            current_Score += rowscore * multiplier;
            s--;
        }

        //output
        Sleep(500);
        system("cls");

        Display_Field();

    }
    // CheckRow();
    std::cout << "YOU LOSE\n";
    std::cout << "\t\tYOUR TOTAL SCORE WAS " << current_Score << endl;
    system("color 04");
}

void Tetris::Display_Field()
{
    // playing_field[9*SCREENWIDTH+1] = '#';
    // playing_field[9*SCREENWIDTH+2] = '#';
    std::cout << "Next Tetramino : ";
    switch (next_spawn)
    {
    case 0:
        std::cout << "Square";
        break;

    case 1:
        std::cout << "L";
        break;

    case 2:
        std::cout << "S";
        break;

    case 3:
        std::cout << "Straight";
        break;
    case 4:
        std::cout << "T";
        break;

    default:
        break;
    }
    std::cout << endl;
    for (int i = 0; i < SCREENWIDTH; i++)
    {
        for (int j = 0; j < SCREENHEIGHT; j++)
        {
            // std::cout<<(j*SCREENWIDTH +i)<<" ";
            std::cout << playing_field[j * SCREENWIDTH + i];
            // Sleep(1);
        }
        std::cout << endl;
    }

}

void Tetris::Move(int x, int y, bool randomize) {
    //get the piece array of last spawn
    vector<vector<int>> arr = last_spawn->GetPiece();
    //check if it fits
    if (randomize == false) {
        // std::cout<<"pop"<<last_spawn->GetPiece()[0][0]<<" pop";
        for (int i = 0; i < last_spawn->GetWidth(); i++)
        {
            for (int j = 0; j < last_spawn->GetHeight(); j++)
            {
                if ((arr[j][i] == 1) && (playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] == '0')) {
                    // set pieces last position as empty
                    playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = ' ';

                    // move the current piece down 
                    playing_field[((j + last_posX + x) * SCREENWIDTH) - i + last_posY + y] = '0';
                    //update last playing field
                    last_playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = '0';
                }
            }
        }

        last_posX += x;
        last_posY += y;
    }
    else {
        //Chage the letters
        for (int i = 0; i < last_spawn->GetWidth(); i++)
        {
            for (int j = 0; j < last_spawn->GetHeight(); j++)
            {
                if ((arr[j][i] == 1) && (playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] == '0')) {

                    playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = "ABCD"[random.GetRandomNumber(4)];

                    last_playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = 'G';
                }
            }
        }

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
                    // std::cout << "   " << i << "   " << endl;
                    // Sleep(10);
                    rowsnums.push_back(i);
                }
                else {
                    continue;
                }
            }
        }

    }
    if (rowsnums.size() > 1) {
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
        Sleep(300);
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

void* Tetris::GetInput(void* obj)
{
    Tetris* t = (Tetris*)obj;
    while (t->m_isrunning) {
        int a;
        //if the mostsignificat bit (0x800) = 1<<15 is set then key is down
        //refer to microsoft for more details https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
        if (GetKeyState('A') & 0x8000) {
            a = -1;
        }
        else if (GetKeyState('D') & 0x8000) {
            a = 1;
        }
        else if (GetKeyState('Q') & 0x8000) {
            a = -2;
        }
        else if (GetKeyState('E') & 0x8000) {
            a = 2;
        }
        else {
            a = 0;
            // b = 1;
        }
        if (GetKeyState('Z') & 0x8000) {
            if (t->is_rotated == false)
                t->is_rotated = true;  
        }
        t->px = a;
        Sleep(100);
        // t->py = b;
    }
}


void Tetris::InitTetraminos() {
    //23 345
    //01 012
    char sq[5] = { '0','1','2','3','\0' };
    char s[5] = { '0','2','3','5','\0' };
    char l[5] = { '0','1','2','3','\0' };
    char bar[5] = { '0','1','2','3','\0' };
    char t[5] = { '1','2','3','5','\0' };
    tets[tet_square].SetVars(2, 2, sq);
    tets[tet_s].SetVars(3, 2, s);
    tets[tet_t].SetVars(3, 2, t);
    tets[tet_l].SetVars(2, 3, l);
    tets[tet_bar].SetVars(4, 1, bar);
}

/// @brief well it was supposedly made to change color but hey sometimes thing dont work according to you so don't use it, i will update if its ready
/// @param color color to set ; type in console {color /?} without brackets of course the integer corresponds to the foregound colors
/* void Tetris::setcolor(int color)
// {
//     switch (color)
//     {
//     case 1:
//         system("color 01");
//         break;

//     case 2:
//         system("color 02");
//         break;

//     case 3:
//         system("color 03");
//         break;

//     case 4:
//         system("color 04");
//         break;

//     case 5:
//         system("color 05");
//         break;

//     case 6:
//         system("color 06");
//         break;

//     case 7:
//         system("color 07");
//         break;

//     case 8:
//         system("color 08");
//         break;

//     case 9:
//         system("color 09");
//         break;

//     default:
//         break;
//     }
//     // string color = "color 0"+to_string(2);
//     system("color 02");
// }
*/

void Tetris::spawn(int posX, int posY, tet_types t)
{
    int rd;
    rd = random.GetRandomNumber(size_tet_types);

    Tetramino spawned = tets[t];
    next_spawn = static_cast<tet_types>(rd);
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

                    // std::cout << " filled" << ((j + posX) * SCREENWIDTH) - i + posY << "\n";
                    playing_field[((j + posX) * SCREENWIDTH) - i + posY] = '0';

                }
            }
        }
        last_spawn = &tets[t];
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

void Tetris::Rotate() {
    Tetramino rp = *(last_spawn->GetRotatedPiece());
    if (DoesPieceFit(rp, last_posX, last_posY)) {
        for (int i = 0; i < SCREENWIDTH; i++)
        {
            for (int j = 0; j < SCREENHEIGHT; j++)
            {
                if (playing_field[j * SCREENWIDTH + i] == '0')
                    playing_field[j * SCREENWIDTH + i] = ' ';
            }

        }

        last_spawn = last_spawn->GetRotatedPiece();
        // std::cout<<"last spawn h"<<last_spawn->GetHeight()<<" w"<<last_spawn->GetWidth()<<endl;
        vector<vector<int>> arr = last_spawn->GetPiece();
        for (int i = 0; i < last_spawn->GetWidth(); i++)
        {
            for (int j = 0; j < last_spawn->GetHeight(); j++)
            {
                if ((arr[j][i] == 1) && (playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] == ' ')) {

                    // playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = "ABCD"[random.GetRandomNumber(4)];
                    playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = '0';
                    // last_playing_field[((j + last_posX) * SCREENWIDTH) - i + last_posY] = 'G';
                }
            }
        }


    }
    is_rotated = false;
}

Tetris::~Tetris()
{
    delete[] last_spawn;
    delete[] playing_field;
    delete[] last_playing_field;
}

#endif