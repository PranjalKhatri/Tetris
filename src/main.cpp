#include <iostream>
// #include "..\include\utils.hpp"
#include "..\include\tetramino.hpp"
#include "..\include\tetris.hpp"
#include <pthread.h>

/// @brief Contains options for different types of menu
enum Menu {
    start = 1,
    High_Scores = 2,
    terminate = 3,
    Main_Menu
};
/// @brief Starts the game
void Play();
/// @brief Opens Main Menu
void MainMenu();
/// @brief Opens Scores Menu
void HighScores();
/// @brief Terminates the program
void Terminate();
/// @brief Saves the player score to the file
/// @param name name of the player
/// @param score Score of the player
void SetScore(string name, int score);

void displaymenu();

string ScorePath = "..\\UserData\\Scores.bin";

using namespace std;
int main()
{
    MainMenu();
    // Sleep(100);

    return 0;
}

void Play() {
    pthread_t ptid;
    Tetris t;
    pthread_create(&ptid, NULL, &(Tetris::GetInput), (void*)&t);
    t.GameLoop();
    pthread_join(ptid, NULL);
    Sleep(100);
    cout << "Press any key to Continue...";
    Sleep(400);
    cin.ignore();
    cin.clear();
    getch();
    system("color 07");
    cout << "YOUR NAME ? ";
    string s;
    cin.ignore();
    cin.clear();
    cin >> s;
    SetScore(s, t.current_Score);
    MainMenu();
}

void MainMenu() {
    displaymenu();
    //set colour to white
    system("color 07");
    int m;
    ///open main menu
    // MainMenu();
    // take user choice
    cin >> m;

    switch (m) {
    case Menu::start:
        Play();
        break;
    case Menu::terminate:
        break;
    case Menu::High_Scores:
        HighScores();
        break;
    default:
        MainMenu();
        break;
    }

}

void displaymenu() {
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

void SetScore(string name,int score){
    FileOps fops(ScorePath);
    fops.Write(name + "  -->  " + to_string(score));
}

void HighScores(){
    std::cout<<"####################\n";
    std::cout<<"        HIGH SCORES    \n";
    FileOps fops(ScorePath);
    std::vector<std::string> lines = fops.read();
    for(auto i : lines){
        std::cout<<i<<std::endl;
    }
    std::cout<<"Press any key to go back...\n";
    Sleep(100);
    getch();
    MainMenu();
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
