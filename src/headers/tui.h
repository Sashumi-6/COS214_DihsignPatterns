/**
 * @file tui.h
 * @brief Declares the text user interface helper used for console I/O.
 */
#ifndef TUI_H
#define TUI_H

#include <iostream>

/**
 * @class TUI
 * @brief This class is for basic i/o to terminal
 */
class TUI {
    public:
        /**
         * @brief Writes queued log information to the console.
         */
        void consoleLog();

        // Give options, returns option picked
        // variadic function
        /**
         * @brief Displays options and captures the user's selection.
         * @return Index of the chosen option.
         */
        int printOptions();
};

#endif
