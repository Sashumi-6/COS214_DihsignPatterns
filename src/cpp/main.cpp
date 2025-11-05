/**
 * @file main.cpp
 * @brief Entry point launching the text user interface.
 */
#include "../headers/tui.h"

/**
 * @brief Program entry that initializes and runs the console interface.
 * @return Exit status code.
 */
int main() {
    TUI tui;
    tui.consoleLog();
    return 0;
}
