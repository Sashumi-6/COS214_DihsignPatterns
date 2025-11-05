/**
 * @file tui.cpp
 * @brief Implements the text-based user interface for the simulator.
 */
#include "../headers/tui.h"

#include "../headers/plantDatabase.h"
#include "../headers/simulator.h"
#include <cctype>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace {

/**
 * @brief Reads an integer within bounds from standard input.
 * @param prompt Text to display before reading.
 * @param minValue Minimum accepted value.
 * @param maxValue Maximum accepted value.
 * @return Validated integer inside the range.
 */
int readInt(const std::string& prompt, int minValue, int maxValue) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minValue && value <= maxValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Please enter a number between " << minValue << " and " << maxValue << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * @brief Reads a yes/no response from the user.
 * @param prompt Question presented to the user.
 * @return True for yes, false for no.
 */
bool readYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " (y/n): ";
        char ch = '\0';
        if (std::cin >> ch) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            if (ch == 'y') {
                return true;
            }
            if (ch == 'n') {
                return false;
            }
        } else {
            std::cin.clear();
        }
        std::cout << "Please answer with 'y' or 'n'.\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * @brief Prompts the user to select a business level for a given day.
 * @param dayNumber Day index displayed in the prompt.
 * @return Selected business level.
 */
BusinessLevel selectBusinessLevelForDay(int dayNumber) {
    std::cout << "\nChoose business level for day " << dayNumber << ":\n";
    std::cout << "  1) Low\n";
    std::cout << "  2) Medium\n";
    std::cout << "  3) High\n";
    int choice = readInt("Selection: ", 1, 3);
    switch (choice) {
        case 1:
            return BusinessLevel::LOW;
        case 2:
            return BusinessLevel::MEDIUM;
        default:
            return BusinessLevel::HIGH;
    }
}

/**
 * @brief Converts a business level enum into a human-readable string.
 * @param level Business volume level.
 * @return Descriptive string.
 */
std::string businessLevelToString(BusinessLevel level) {
    switch (level) {
        case BusinessLevel::LOW:
            return "Low";
        case BusinessLevel::MEDIUM:
            return "Medium";
        case BusinessLevel::HIGH:
            return "High";
    }
    return "Unknown";
}

/**
 * @brief Waits for the user to press Enter before continuing.
 */
void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Guides the user through configuring plant quantities.
 * @return Mapping of plant names to requested quantities.
 */
std::map<std::string, int> configurePlants() {
    const std::map<std::string, PlantInfo>& database = PlantDatabase::getAllPlants();
    std::vector<std::string> plantNames;
    plantNames.reserve(database.size());
    for (const auto& entry : database) {
        plantNames.push_back(entry.first);
    }

    std::map<std::string, int> selection;
    bool done = false;
    while (!done) {
        std::cout << "\nAvailable plants:\n";
        for (std::size_t i = 0; i < plantNames.size(); ++i) {
            const std::string& plantName = plantNames[i];
            int current = selection.count(plantName) ? selection[plantName] : 0;
            std::cout << "  " << (i + 1) << ") " << plantName;
            if (current > 0) {
                std::cout << " (selected: " << current << ")";
            }
            std::cout << "\n";
        }
        std::cout << "  0) Done selecting plants\n";

        int choice = readInt("Select a plant to set quantity (0 to finish): ",
                             0, static_cast<int>(plantNames.size()));
        if (choice == 0) {
            done = true;
            continue;
        }
        const std::string& selectedPlant = plantNames[static_cast<std::size_t>(choice - 1)];
        int quantity = readInt("Enter quantity (0 to remove): ", 0, 100);
        if (quantity == 0) {
            selection.erase(selectedPlant);
        } else {
            selection[selectedPlant] = quantity;
        }
    }

    if (selection.empty()) {
        std::cout << "No plants selected. Using a small default assortment.\n";
        int added = 0;
        for (const auto& plantName : plantNames) {
            selection[plantName] = 2;
            if (++added >= 3) {
                break;
            }
        }
    }

    return selection;
}

/**
 * @brief Reads a random seed value from the user.
 * @return Unsigned integer seed.
 */
unsigned int readSeed() {
    while (true) {
        std::cout << "Enter a non-negative seed value: ";
        long long value = 0;
        if (std::cin >> value && value >= 0 && value <= std::numeric_limits<unsigned int>::max()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return static_cast<unsigned int>(value);
        }
        std::cout << "Invalid seed value. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * @brief Displays a daily report summary alongside logged events.
 * @param summary Summary for the day.
 * @param eventLog Chronological event log.
 */
void displayDayReport(const DaySummary& summary, const std::vector<std::string>& eventLog) {
    std::cout << "\n========================================\n";
    std::cout << "Day " << summary.dayIndex << " Report ("
              << businessLevelToString(summary.businessLevel) << ")\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Customers served:   " << summary.customersServed << "\n";
    std::cout << "Orders completed:   " << summary.ordersCompleted << "\n";
    std::cout << "Queries answered:   " << summary.queriesAnswered << "\n";
    std::cout << "Maintenance tasks:  " << summary.maintenanceCommands << "\n";

    std::string dayHeader = "Day " + std::to_string(summary.dayIndex);
    std::string completionToken = "Day " + std::to_string(summary.dayIndex) + " completed.";

    bool capturing = false;
    for (std::size_t i = 0; i < eventLog.size(); ++i) {
        const std::string& entry = eventLog[i];
        if (!capturing) {
            if (entry.find(dayHeader) != std::string::npos) {
                capturing = true;
            } else {
                continue;
            }
        }

        std::cout << "  - " << entry << "\n";
        if (entry.find(completionToken) != std::string::npos) {
            break;
        }
    }
    std::cout << "========================================\n";
}

} // namespace

/**
 * @brief Runs the interactive simulation console workflow.
 */
void TUI::consoleLog() {
    std::cout << "========================================\n";
    std::cout << " Welcome to the Nursery Simulation TUI\n";
    std::cout << "========================================\n";

    std::map<std::string, int> plantSelection = configurePlants();
    int numDays = readInt("\nEnter number of days to simulate (1-30): ", 1, 30);

    bool manualSchedule = !readYesNo("Let the simulator randomise daily business levels");
    std::vector<BusinessLevel> schedule;
    if (manualSchedule) {
        for (int day = 1; day <= numDays; ++day) {
            schedule.push_back(selectBusinessLevelForDay(day));
        }
    }

    int caretakerCount = readInt("\nEnter number of caretakers (at least 1): ", 1, 20);
    int totalEmployees = caretakerCount + 2;

    bool useSeed = readYesNo("\nProvide a custom random seed");
    unsigned int seed = 0;
    if (useSeed) {
        seed = readSeed();
    }

    Simulation simulation(numDays);
    simulation.configureEmployees(totalEmployees);
    simulation.configurePlantSelection(plantSelection);
    if (manualSchedule) {
        simulation.configureBusinessLevels(schedule);
    } else {
        simulation.autoGenerateBusinessLevels(true);
    }
    if (useSeed) {
        simulation.setRandomSeed(seed);
    }

    std::cout << "\nStarting simulation...\n";
    simulation.startSimulation();

    const std::vector<DaySummary>& summaries = simulation.getDailySummaries();
    const std::vector<std::string>& eventLog = simulation.getEventLog();

    for (std::size_t i = 0; i < summaries.size(); ++i) {
        displayDayReport(summaries[i], eventLog);
        waitForEnter();
    }

    std::cout << "\nSimulation complete. Thank you for using the TUI!\n";
}

/**
 * @brief Placeholder implementation demonstrating option handling.
 */
int TUI::printOptions() {
    std::cout << "Options are handled interactively in consoleLog().\n";
    return 0;
}
