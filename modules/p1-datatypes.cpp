#include <iostream>
#include <iomanip>

void printSizeOfTypes() {
    std::cout << "\n Data Type  | Size (bytes)\n";
    std::cout << "------------+-------------\n";
    std::cout << "        int | " << sizeof(int) << '\n';
    std::cout << "  short int | " << sizeof(short) << '\n';
    std::cout << "   long int | " << sizeof(long) << '\n';
    std::cout << "      float | " << sizeof(float) << '\n';
    std::cout << "     double | " << sizeof(double) << '\n';
    std::cout << "long double | " << sizeof(long double) << '\n';
    std::cout << "       char | " << sizeof(char) << '\n';
    std::cout << "       bool | " << sizeof(bool) << '\n';
}


std::string getBitsOfInt(int value) {
    /*
     * Returns binary representation of int
     * :param value: int - decimal integer
     * :param isDebug: bool - displays every comparison if true
     * :return: std::string - binary representation of value
     */

    unsigned int order = sizeof(int) * 8;
    unsigned int mask = 1 << (order - 1);
    std::string binaryInt;
    for (int i = 1; i <= order; i++) {

        char bit = value & mask ? '1' : '0';

        binaryInt += bit;
        mask >>= 1;

        if (i % 8 == 0 || i == 1)
            binaryInt += ' ';
    }
    return binaryInt;
}


std::string getBitsOfFloat(float input) {
    /*
     * Returns binary representation of float
     * :param input: float - decimal float
     * :param isDebug: bool - displays every comparison if true
     * :return: std::string - binary representation of input
     */

    // Use union due to binary operands isn't working with float
    union FloatIntUnion {
        int i;
        float f;
    };

    FloatIntUnion value{.f = input};
    unsigned int order = sizeof(float) * 8;
    unsigned int mask = 1 << (order - 1);
    std::string binaryFloat;
    for (int i = 1; i <= order; i++) {

        char bit = value.i & mask ? '1' : '0';

        binaryFloat += bit;
        mask >>= 1;

        if (i == 1 || i == 9)
            binaryFloat += ' ';
    }

    return binaryFloat;
}


std::string getBitsOFDouble(double input) {
    /*
     * Returns binary representation of double
     * :param input: double - decimal double
     * :return: std::string - binary representation of input
     */

    // Use union due to binary operands isn't working with double
    // Instead of integer which used in getBitsOfFloat use array of char
    // One element of array represents one byte of double
    union DoubleIntUnion {
        unsigned char c[sizeof(double)];
        double d;
    };

    DoubleIntUnion value{.d = input};
    std::string binaryDouble;
    for (int i = sizeof(double)-1; i >= 0; i--) {
        unsigned int order = sizeof(char) * 8;
        unsigned int mask = 1 << (order - 1);
        for (int j = 1; j <= order; j++) {

            char bit = value.c[i] & mask ? '1' : '0';

            binaryDouble += bit;
            mask >>= 1;

            int currentBitIndex = (7 - i) * 8 + j;
            if (currentBitIndex == 1 || currentBitIndex == 12)
                binaryDouble += ' ';
        }
    }

    return binaryDouble;
}


int dataTypes() {

    std::cout.setf(std::ios::boolalpha);
    std::cout << "Enter 'h' to get list of commands\n";

    // Main loop
    while (true) {

        // Get command number from user
        char userAction;
        std::cout << "<< Action: \n>> ";
        std::cin.sync();
        std::cin >> userAction;

        // Exit
        if (userAction == '0') {
            break;
        }

        switch (userAction) {

            // Print the amount of memory occupied by different types of data
            case '1': {
                std::cout << "Memory occupied by certain data types\n";
                printSizeOfTypes();
                break;
            }

            // Print the binary representation in memory of an integer
            case '2': {
                int userInput;
                std::cout << "<< Enter an integer \n>> ";
                std::cin.sync();
                std::cin >> userInput;
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for int with base 10.\n";
                    std::cin.clear();
                    break;
                }
                std::cout << std::setw(23) << "Decimal integer: " << userInput << '\n';
                std::string binaryInt = getBitsOfInt(userInput);
                std::cout << std::setw(23) << "Binary representation: " << binaryInt << '\n';
                break;
            }

            // Print the binary representation in memory of a float
            case '3': {
                float userInput;
                std::cout << "<< Enter a float \n>> ";
                std::cin.sync();
                std::cin >> userInput;
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for float with base 10.\n";
                    std::cin.clear();
                    break;
                }
                std::cout << std::setw(23) << "Decimal float: " << userInput << '\n';
                std::string binaryFloat = getBitsOfFloat(userInput);
                std::cout << std::setw(23) << "Binary representation: " << binaryFloat << '\n';
                break;
            }

            // Print the binary representation in memory of a double
            case '4': {
                double userInput;
                std::cout << "<< Enter a double \n>> ";
                std::cin.sync();
                std::cin >> userInput;
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for double with base 10.\n";
                    std::cin.clear();
                    break;
                }
                std::cout << std::setw(23) << "Decimal double: " << userInput << '\n';
                std::string binaryDouble = getBitsOFDouble(userInput);
                std::cout << std::setw(23) << "Binary representation: " << binaryDouble << '\n';
                break;
            }

            // Help
            case 'h': {
                std::cout << "Available commands:\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "h: Help\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "1: Print the amount of memory occupied by different types of data\n";
                std::cout << "2: Print the binary representation in memory of an integer\n";
                std::cout << "3: Print the binary representation in memory of a float\n";
                std::cout << "4: Print the binary representation in memory of a double\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "0: Exit\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << std::setfill(' ');
                break;
            }

            // Unknown command
            default: {
                std::cout << "RuntimeError: unknown command\n";
            }
        }
    }

    return 0;
}