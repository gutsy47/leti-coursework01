#include <iostream>
#include <iomanip>
#include "modules/data-types.h"
#include "modules/arrays.h"
#include "modules/pointers.h"
#include "modules/strings.h"

void clear() {
    system("cls");
}

int main() {
    while (true) {

        clear();

        // Help
        std::cout << "Available modules:\n";
        std::cout << std::setw(32) << std::setfill('-') << '\n';
        std::cout << "1: Data types and their binary representation\n";
        std::cout << "2: Arrays, searches and sorts\n";
        std::cout << "3: References & pointers. Matrices\n";
        std::cout << "4: Strings and their methods\n";
        std::cout << std::setw(32) << std::setfill('-') << '\n';
        std::cout << "0: Exit\n";
        std::cout << std::setw(32) << std::setfill('-') << '\n';
        std::cout << std::setfill(' ');

        // Get command from user
        char userAction;
        std::cout << "<< Module:\n>> ";
        std::cin.sync();
        std::cin >> userAction;

        // Exit
        if (userAction == '0') break;

        switch (userAction) {
            case '1': {
                clear();
                dataTypes();
                break;
            }

            case '2': {
                clear();
                arrays();
                break;
            }

            case '3': {
                clear();
                pointers();
                break;
            }

            case '4': {
                clear();
                strings();
                break;
            }

            // Unknown module error
            default: std::cout << "RuntimeError: unknown module\n";
        }
    }

    return 0;
}
