/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2019
 *
 * @file    Demo.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Entry point of hw06Demo target.
 */

#include "csc232.h"

int main() {
#if EXECUTE_BLOCK
    std::cout << "Hello, Demo!" << std::endl;
#endif
    std::ifstream data{"demoData.txt"};
    if (data.is_open())
    {
        std::cout << "\nOpened file: \"demoData.txt\"\n" << std::endl;

        int eventTime;
        int eventDuration;
        while (data >> eventTime >> eventDuration)
        {
            std::cout << "Time:" << std::setw(3) << eventTime
                      << ", duration:" << std::setw(3) << eventDuration
                      << std::endl;
        }
    }
    else
    {
        std::cerr << "Couldn't open \"demoData.txt\"" << std::endl;
    }

    if (data.is_open())
    {
        std::cout << "\nClosing file: \"demoData.txt\"" << std::endl;
        data.close();
    }
    return EXIT_SUCCESS;
}