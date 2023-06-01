#include <iostream>
#include "Comics.h"
#include "PEArray.h"
#include "Library.h"
using namespace std;

int main() {
    int choice;
    bool running = true;
    bool problem = false;
    try {
        std::ifstream file("library.dat", std::ios::binary);
        if (!file.is_open()) {
            problem = true;
            file.close();
            std::ofstream file2("library.dat", std::ios::binary);
            if (!file2.is_open()) {
                throw "File couldnt open";
            }
            file2.close();
        }
        if (problem) {
            std::ifstream file3("library.dat", std::ios::binary);
            if (!file3.is_open()) {
                throw "File couldnt open";
            }
            Library::getInstance().readFile(file3);
            file3.close();
        }
        else {
            Library::getInstance().readFile(file);
            file.close();
        }
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }

    while (running) {
        cout << "------------- MENU -------------" << endl;
        cout << "1. Add Printed Edition" << endl;
        cout << "2. Remove Printed Edition" << endl;
        cout << "3. Print Printed Editions" << endl;
        cout << "4. Add User" << endl;
        cout << "5. Remove User" << endl;
        cout << "6. Print Users Reading Printed Edition" << endl;
        cout << "7. Print Users" << endl;
        cout << "8. Take Printed Edition" << endl;
        cout << "9. Return Printed Edition" << endl;
        cout << "0. Exit" << endl;
        cout << "-------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int typeChoice;
            cout << "Select the type of Printed Edition to add:" << endl;
            cout << "1. Book" << endl;
            cout << "2. Periodical Edition" << endl;
            cout << "3. Comics" << endl;
            cout << "Enter your choice: ";
            cin >> typeChoice;
    
            unsigned year = 0;
            char heading[64] = { '\0' };
            char description[128] = { '\0' };
            unsigned libraryNumber = 0;
            cout << "Enter the heading of the Book: ";
            cin.ignore();
            cin.getline(heading, 64);
            cout << "Enter the description of the Book: ";
         //   cin.ignore();
            cin.getline(description, 64);
            cout << "Enter the year of the Book: ";
           // cin.ignore();
            cin >> year;
            cout << "Enter the library number of the Book: ";
          //  cin.ignore();
            cin >> libraryNumber;

            switch (typeChoice) {
            case 1: {
                unsigned genre = 0;
                char author[28] = { '\0' };
                char publisher[64] = { '\0' };

                cout << "Enter the author of the Book: ";
                cin.ignore();
                cin.getline(author, 64);
                cout << "Enter the publisher of the Book: ";
                //cin.ignore();
                cin.getline(publisher, 64);
                cout << "Enter the genre of the Book: ";
                //cin.ignore();
                cin >> genre;
                PrintedEdition* book = new Book(heading, description, libraryNumber, year, author, publisher, genre);
                Library::getInstance().addPrint(book);

                cout << "Book added successfully!" << endl;
                break;
            }
            case 2: {
                unsigned period = 0;
                unsigned number = 0;
                cout << "Enter the period of the Book (WEEKLY = 0, MONTHLY = 1, YEARLY = 2): ";
                cin.ignore();
                cin >> period;
                cout << "Enter the number of the Book: ";
                // cin.ignore();
                cin >> number;
                Period periodE;
                switch (period)
                {
                case 0:
                    periodE = WEEKLY;
                    break;
                case 1:
                    periodE = MONTHLY;
                    break;
                case 2:
                    periodE = YEARLY;
                }
                PeriodicalEdition* periodical = new PeriodicalEdition(heading, description, libraryNumber, year, periodE, number);
                Library::getInstance().addPrint(periodical);

                cout << "Periodical Edition added successfully!" << endl;
                break;
            }
            case 3: {
                unsigned genre = 0;
                unsigned period = 0;
                unsigned number = 0;
                char author[28] = { '\0' };
                char publisher[64] = { '\0' };

                cout << "Enter the author of the Book: ";
                cin.ignore();
                cin.getline(author, 64);
                cout << "Enter the publisher of the Book: ";
                // cin.ignore();
                cin.getline(publisher, 64);
                cout << "Enter the genre of the Book: ";
                // cin.ignore();
                cin >> genre;
                cout << "Enter the period of the Book (WEEKLY = 0, MONTHLY = 1, YEARLY = 2): ";
                //cin.ignore();
                cin >> period;
                cout << "Enter the number of the Book: ";
                //cin.ignore();
                cin >> number;
                Period periodE;
                switch (period)
                {
                case 0:
                    periodE = WEEKLY;
                    break;
                case 1:
                    periodE = MONTHLY;
                    break;
                case 2:
                    periodE = YEARLY;
                }

                PrintedEdition* comics = new Comics(heading, description, libraryNumber, year, author, publisher, genre, periodE, number);
                Library::getInstance().addPrint(comics);

                cout << "Comics added successfully!" << endl;
                break;
            }
            default:
                cout << "Invalid type choice. Please try again." << endl;
                break;
            }

            break;
        }
        case 2: {
            unsigned libraryNum = 0;
            cout << "Enter the library number of the Printed Edition to remove: ";
            //cin.ignore();
            cin >> libraryNum;
            Library::getInstance().removePrint(libraryNum);

            cout << "Printed Edition removed successfully!" << endl;
            break;
        }
        case 3: {
            Library::getInstance().printPrints();
            break;
        }
        case 4: {
            char name[28] = { '\0' };
            cout << "Enter the username of the User to add: ";
            cin.ignore();
            cin.getline(name, 28);
            User user(name);
            Library::getInstance().addUsers(user);

            cout << "User added successfully!" << endl;
            break;
        }
        case 5: {
            char name[28] = { '\0' };
            cout << "Enter the username of the User to remove: ";
            cin.ignore();
            cin.getline(name, 28);
            Library::getInstance().removeUser(name);

            cout << "User removed successfully!" << endl;
            break;
        }
        case 6: {
            unsigned libraryNum = 0;
            cout << "Enter the library number of the Printed Edition to check: ";
            //cin.ignore();
            cin >> libraryNum;
            Library::getInstance().printUsersReadingPrint(libraryNum);
            break;
        }
        case 7: {
            Library::getInstance().printUsers();
            break;
        }
        case 8: {
            unsigned libnum;
            char name[28] = { '\0' };
            cout << "Enter the username of the User: ";
            cin.ignore();
            cin.getline(name, 28);
            cout << "Enter the library num of the Printed Edition to take: ";
            //cin.ignore();
            cin >> libnum;
            Library::getInstance().takePrint(libnum, name);

            cout << "Printed Edition taken successfully!" << endl;
            break;
        }
        case 9: {
            unsigned libnum;
            char name[28] = { '\0' };
            cout << "Enter the username of the User: ";
            cin.ignore();
            cin.getline(name, 28);
            cout << "Enter the library num of the Printed Edition to take: ";
           // cin.ignore();
            cin >> libnum;
            Library::getInstance().getPrintBack(libnum, name);

            cout << "Printed Edition returned successfully!" << endl;
            break;
        }
        case 0: {
            running = false;
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        cout << endl;
    }

    try {
        std::ofstream file("library.dat", std::ios::binary);
        if (!file.is_open()) {
            throw "File couldnt open";
        }
        Library::getInstance().writeFile(file);
        file.close();
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
}
