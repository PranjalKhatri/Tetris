#include <iostream>
#include "..\include\tetramino.hpp"
#include "..\include\tetris.hpp"
#include <pthread.h>

enum Menu {
    start = 1,
    High_Scores,
    Main_Menu,
    terminate
};
void Play();
//Menu MenuSelect(int menu);
void MainMenu();
void HighScores();
void Terminate();


using namespace std;
int main()
{
    system("color 07");

    int m;
    MainMenu();
    cin >> m;

    switch (m) {

    case Menu::start:
        Play();
        break;
    case Menu::terminate:
        break;
    case Menu::High_Scores:
        break;
    }

    // Sleep(100);

    return 0;
}

void Play() {
    pthread_t ptid;
    Tetris t;
    pthread_create(&ptid, NULL, &(Tetris::GetInput), (void*)&t);
    t.GameLoop();
    pthread_join(ptid, NULL);
    cout << "Press any key to Continue...";
    Sleep(200);
    system("color 07");
    cin.ignore();
    MainMenu();
}

void MainMenu() {
    system("cls");
    std::cout << "#########################\n"
        "|         TETRIS        |\n"
        "|                       |\n"
        "|      1 PLAY           |\n"
        "|      2 SCORES         |\n"
        "|      3 EXIT           |\n"
        "|                       |\n"
        "|                       |\n"
        "|                       |\n"
        "#########################\n";
}

void HighScores(){

}

/// @brief Selects the menus ; same as static cast but SLOWER :)
/// @param menu menu type
/// @return true if the menu selected is play
/* Menu MenuSelect(int menu) {
    switch (menu)
    {
    case Menu::Main_Menu:
        MainMenu();
        return Menu::Main_Menu;
        break;
    case Menu::terminate:
        return Menu::terminate;
        break;
    case Menu::start:
        return Menu::start;
        break;
    default:
        MainMenu();
        return Menu::Main_Menu;
        break;
    };
} */
