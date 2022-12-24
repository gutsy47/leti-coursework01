#include <iostream>
#include <iomanip>
#include "modules/p1-datatypes.h"
#include "modules/p2-arrays.h"
#include "modules/p3-pointers.h"
#include "modules/p4-strings.h"

int main() {
    while (true) {
        // Help
        system("cls");
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

        system("cls");
        switch (userAction) {
            case '1': {
                dataTypes();
                break;
            }

            case '2': {
                arrays();
                break;
            }

            case '3': {
                pointers();
                break;
            }

            case '4': {
                strings();
                break;
            }

            // Unknown module error
            default: std::cout << "RuntimeError: unknown module\n";
        }
    }

    return 0;
}
