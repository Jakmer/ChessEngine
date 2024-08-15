#include "WindowManager.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

namespace WindowManager
{
    WindowManager::WindowManager() {
    }

    WindowManager::~WindowManager() {
    }

    int WindowManager::showDialogAndAwaitResponse() {
        spdlog::info("WindowManager: showDialogAndAwaitResponse");
        std::cout << "Please choose an option:\n";
        std::cout << "1. Join game\n";
        std::cout << "2. Create new game\n";
        std::cout << "3. Exit\n";

        int choice;
        std::cin >> choice;

        while (choice < 1 || choice > 3) {
            std::cout << "Invalid choice. Please choose again:\n";
            std::cin >> choice;
        }
        spdlog::info("WindowManager: User chose option {}", choice);
        return choice;
    }
}