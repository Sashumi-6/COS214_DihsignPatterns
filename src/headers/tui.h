#ifndef TUI_H
#define TUI_H

#include <iostream>

/**
 * @class TUI
 * @brief This class is for basic i/o to terminal
 */
class TUI {
    public:
        void consoleLog();

        // Give options, returns option picked
        // variadic function
        int printOptions();
};

#endif