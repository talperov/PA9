#include <iostream>
#include "Game.hpp"
#include "TestCharacter.hpp"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    int choice = 0;
    do
    {
        cout << "=============================" << endl;
        cout << "       MAIN MENU" << endl;
        cout << "=============================" << endl;
        cout << "1. Run Tests" << endl;
        cout << "2. Run Game" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;



        switch (choice)
        {
        case 1:
            cout << "Running tests...\n";
            runAllTests();
            break;

        case 2:
            cout << "Starting game...\n";
            runGame();
            break;

        case 3:
            cout << "Goodbye!\n";
            return 0;

        default:
            cout << "Invalid option.\n";
        }
    } while (choice != 3);
    return 0;
}