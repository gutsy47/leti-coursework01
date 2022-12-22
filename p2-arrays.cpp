#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>


void bubbleSort(int *arr, int length) {
    for (int i = length - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void shakerSort(int *arr, int length) {
    for (int i = length - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
        for (int j = i - 1; j > length - i; j--) {
            if (arr[j] < arr[j - 1]) {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}


void combSort(int *arr, int length) {
    int gap = length;

    while (gap != 1) {
        gap /= 1.247;
        if (gap < 1) {
            gap = 1;
        }

        for (int i = 0; i < length - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
            }
        }
    }
}


void insertSort(int *arr, int length) {
    for (int i = 1; i < length; i++) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            std::swap(arr[j - 1], arr[j]);
        }
    }
}


void quickSort(int *arr, int first, int last) {
    int mid = arr[(first + last) / 2];
    int tmpLast = last, tmpFirst = first;
    while (first < last) {
        while (arr[first] < mid) first++;
        while (arr[last] > mid) last--;
        if (first <= last) {
            std::swap(arr[first], arr[last]);
            first++;
            last--;
        }
    }
    if (tmpFirst < last) quickSort(arr, tmpFirst, last);
    if (first < tmpLast) quickSort(arr, first, tmpLast);
}


void additionalTask(int *arr, int length, int *multiplesCount, int key) {
    /* Каждый i & 1 != 0 уменьшить на userInput && *= randint(1, 9+1)
     * Вывести количество кратных 1..9
     */
    std::srand(time(NULL));

    for (int i = 0; i < 9; i++) multiplesCount[i] = 0;
    for (int i = 0; i < length; i++) {
        if ((i & 1) != 0) {
            arr[i] = (arr[i] - key) * (1 + std::rand() % 9);
        }
        for (int divider = 1; divider < 10; divider++) {
            multiplesCount[divider-1] += (arr[i] % divider == 0) ? 1 : 0;
        }
    }
}


int binarySearch(int *arr, int left, int right, int key) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        if ((mid == 0 || key > arr[mid - 1]) && arr[mid] == key) {
            return mid;
        } else if (key > arr[mid]) {
            return binarySearch(arr, mid + 1, right, key);
        } else {
            return binarySearch(arr, left, mid - 1, key);
        }
    }
    return -1;
}


void printArray(int *arr, int length) {
    // Just print array
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << '\t';
    }
    putchar('\n');
}


void fillArray(int *arr, int length) {
    // Fill array with pseudo-random nums in range [-99, 99]
    std::srand(time(NULL));
    for (int i = 0; i < length; i++) {
        arr[i] = -99 + (std::rand() % 199);
    }
}


int main() {

    std::cout.setf(std::ios::fixed);
    std::cout << "Enter 'h' to get list of commands\n";

    // Array initialization
    const int N = 100;
    int array[N], unsortedArray[N];
    bool isArraySorted = false;
    fillArray(array, N);
    std::copy(std::begin(array), std::end(array), std::begin(unsortedArray));

    // Main loop
    while (true) {

        // Get command from user
        char userAction;
        std::cout << "<< Action: \n>> ";
        std::cin.sync();
        std::cin >> userAction;

        // Exit
        if (userAction == '0') {
            break;
        }

        switch (userAction) {

            // Refill the array
            case '1': {
                fillArray(array, N);
                std::cout << "Array refilled successfully\n";
                std::copy(std::begin(array), std::end(array), std::begin(unsortedArray));
                isArraySorted = false;
                break;
            }

            // Sort the array
            case '2': {
                auto start = std::chrono::steady_clock::now();
                quickSort(array, 0, N-1);
                auto end = std::chrono::steady_clock::now();
                auto elapsed_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << "Array sorted. Elapsed time: " << elapsed_us << " ns\n";
                isArraySorted = true;
                break;
            }

            // Find max & min elements in sorted/unsorted array
            case '3': {
                // UnsortedError
                if (!isArraySorted) {
                    std::cout << "Array isn't sorted. Use command '2' to sort it\n";
                    break;
                }

                int min = 100, max = -100;

                // Min & max in unsorted array
                auto start = std::chrono::steady_clock::now();
                for (int i = 0; i < N; i++) {
                    if (unsortedArray[i] < min) {
                        min = unsortedArray[i];
                    }
                    else if (unsortedArray[i] > max) {
                        max = unsortedArray[i];
                    }
                }
                auto end = std::chrono::steady_clock::now();
                auto elapsed_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << "Elements in unsorted array found. Elapsed time: " << elapsed_us << " ns\n";
                std::cout << "min = " << min << "\nmax = " << max << std::endl;

                // Min & max in sorted array
                start = std::chrono::steady_clock::now();
                min = array[0];
                max = array[N-1];
                end = std::chrono::steady_clock::now();
                elapsed_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << "Elements in sorted array found. Elapsed time: " << elapsed_us << " ns\n";
                std::cout << "min = " << min << "\nmax = " << max << std::endl;

                break;
            }

            // Find avg(max, min) and print indexes of elements equals to it
            case '4': {
                // In sorted & in unsorted? wdim?

                // UnsortedError
                if (!isArraySorted) {
                    std::cout << "Array isn't sorted. Use command '2' to sort it\n";
                    break;
                }

                // Average of max and min elements
                int avg = (array[N-1] + array[0]) / 2;

                // Find indexes of elements which equals to average
                std::cout << "Elements equal to average of min and max\n";

                // In sorted array using binary search to find entry
                std::cout << "In sorted array: ";
                auto start = std::chrono::steady_clock::now();
                for (int i = binarySearch(array, 0, N, avg); i < N; i++) {
                    if (array[i] != avg) break;
                    std::cout << i << ' ';
                }
                auto end = std::chrono::steady_clock::now();
                auto elapsed_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << "\nElapsed time: " << elapsed_us << " ns\n";

                // In unsorted array
                std::cout << "In unsorted array: ";
                start = std::chrono::steady_clock::now();
                for (int i = 0; i < N; i++) {
                    if (unsortedArray[i] == avg) std::cout << i << ' ';
                }
                end = std::chrono::steady_clock::now();
                elapsed_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << "\nElapsed time: " << elapsed_us << " ns\n";

                break;
            }

            // Find amount of elements which less than user_input in sorted array
            case '5': {
                // UnsortedError
                if (!isArraySorted) {
                    std::cout << "Array isn't sorted. Use command '2' to sort it\n";
                    break;
                }

                // User input
                int userInput;
                std::cout << "<< Enter an integer:\n>> ";
                std::cin >> userInput;
                std::cin.sync();
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for int with base 10.\n";
                    std::cin.clear();
                    break;
                }

                // Search & display
                int amount = 0;
                for (int i = 0; i < N; i++) {
                    amount += array[i] < userInput ? 1 : 0;
                }
                std::cout << "Elements less than " << userInput << ": " << amount << std::endl;
                break;
            }

            // Find amount of elements which greater than user_input in sorted array
            case '6': {
                // UnsortedError
                if (!isArraySorted) {
                    std::cout << "Array isn't sorted. Use command '2' to sort it\n";
                    break;
                }

                // User input
                int userInput;
                std::cout << "<< Enter an integer:\n>> ";
                std::cin >> userInput;
                std::cin.sync();
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for int with base 10.\n";
                    std::cin.clear();
                    break;
                }

                // Search & display
                int amount = 0;
                for (int i = N-1; i >= 0; i--) {
                    amount += array[i] > userInput ? 1 : 0;
                }
                std::cout << "Elements greater than " << userInput << ": " << amount << std::endl;
                break;
            }

            // Compare binary and default searches (searching for user input). Print time diff
            case '7': {
                // UnsortedError
                if (!isArraySorted) {
                    std::cout << "Array isn't sorted. Use command '2' to sort it\n";
                    break;
                }

                // Input
                int userInput;
                std::cout << "<< Enter an integer:\n>> ";
                std::cin >> userInput;
                std::cin.sync();
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for int with base 10.\n";
                    std::cin.clear();
                    break;
                }
                if (userInput > N-1) {
                    std::cout << "IndexError: list index out of range.\n";
                    break;
                }

                int result;

                // Binary search
                auto start = std::chrono::steady_clock::now();
                result = binarySearch(array, 0, N, userInput);
                auto end = std::chrono::steady_clock::now();
                auto elapsed_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << " Binary search result: " << result << " Elapsed time: " << elapsed_us << " ns\n";

                // Default search
                start = std::chrono::steady_clock::now();
                result = -1;
                for (int i = 0; i < N; i++) {
                    if (array[i] == userInput) {
                        result = i;
                        break;
                    }
                }
                end = std::chrono::steady_clock::now();
                elapsed_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << "Default search result: " << result << " Elapsed time: " << elapsed_us << " ns\n";

                // Output
                if (result != -1) {
                    std::cout << "Element found. Position: " << result << std::endl;
                } else {
                    std::cout << "Element not found.\n";
                }

                break;
            }

            // Swap by indexes entered by the user. Print the time
            case '8': {
                // Input. This one is kinda huge
                int index1, index2;
                std::cout << "<< Enter 1st index:\n>> ";
                std::cin >> index1;
                std::cin.sync();
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for int with base 10.\n";
                    std::cin.clear();
                    break;
                }
                if (index1 > N-1 || index1 < 0) {
                    std::cout << "IndexError: list index out of range.\n";
                    break;
                }
                std::cout << "<< Enter 2nd index:\n>> ";
                std::cin >> index2;
                std::cin.sync();
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for int with base 10.\n";
                    std::cin.clear();
                    break;
                }
                if (index2 > N-1 || index2 < 0) {
                    std::cout << "IndexError: list index out of range.\n";
                    break;
                }

                // Swap
                auto start = std::chrono::steady_clock::now();
                std::swap(unsortedArray[index1], unsortedArray[index2]);
                auto end = std::chrono::steady_clock::now();
                auto elapsed_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << index1 << ": " << unsortedArray[index2] << " | ";
                std::cout << index2 << ": " << unsortedArray[index1] << std::endl;
                std::cout << "Elements swapped. Elapsed time: " << elapsed_us << " ns\n";
                break;
            }

            // Individual task
            case 'i': {
                // Input
                int userInput;
                std::cout << "<< Enter an integer:\n>> ";
                std::cin >> userInput;
                std::cin.sync();
                if (std::cin.fail()) {
                    std::cout << "TypeError: invalid literal for int with base 10.\n";
                    std::cin.clear();
                    break;
                }

                // Task
                int multiplesCount[9];
                std::cout << "Before:\n";
                printArray(unsortedArray, N);
                additionalTask(unsortedArray, N, multiplesCount, userInput);
                isArraySorted = false;

                std::cout << "After:\n";
                printArray(unsortedArray, N);
                std::cout << "T2 res:\n";
                for (int i = 1; i < 10; i++) {
                    std::cout << i << '\t';
                }
                putchar('\n');
                printArray(multiplesCount, 9);

                break;
            }

            // Display array elements
            case '9': {
                std::cout << "Unsorted array:\n";
                printArray(unsortedArray, N);
                if (isArraySorted) {
                    std::cout << "Sorted array:\n";
                    printArray(array, N);
                }
                break;
            }

            // Help
            case 'h': {
                std::cout << "Available commands:\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "h: Help\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "1: Refill the array with random numbers in range [-99, 99]\n";
                std::cout << "2: Sort the array\n";
                std::cout << "3: Find min and max elements. Compare search in sorted and unsorted arrays\n";
                std::cout << "4: Find round average of max & min and print indexes of elements equals to it\n";
                std::cout << "5: Find amount of elements which are less than user input in sorted array\n";
                std::cout << "6: Find amount of elements which are greater than user input in sorted array\n";
                std::cout << "7: Find an element entered by the user via binary and default searches. Compare them\n";
                std::cout << "8: Swap 2 elements by indexes entered by the user\n";
                std::cout << "9: Display array elements\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "0: Exit\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << "NOTE: Script will skip all the useless input (e.g. extra symbols in action input)\n";
                std::cout << std::setw(32) << std::setfill('-') << '\n';
                std::cout << std::setfill(' ');
                break;
            }

            // Unknown command error
            default: {
                std::cout << "RuntimeError: unknown command\n";
            }
        }
    }

    return 0;
}
