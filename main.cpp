#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>  // For saving/loading tasks
#include <cstdlib>  // For system()

// Define ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"

// Function declarations for task management
void displayTasks(const std::vector<std::string>& tasks);
void addTask(std::vector<std::string>& tasks);
void removeTask(std::vector<std::string>& tasks);
void saveTasks(const std::vector<std::string>& tasks, const std::string& filePath);
void loadTasks(std::vector<std::string>& tasks, const std::string& filePath);

int main() {
    // Create a map of nicknames to lists of URLs
    std::unordered_map<std::string, std::vector<std::string>> linkMap;
    linkMap["jobs"] = {
        "start https://www.notion.so/Internship-Tracker-a3f47e8497ca4a3e9e029e402e23dcd1",
        "start https://github.com/cvrve/Summer2025-Internships?tab=readme-ov-file",
        "start https://mail.google.com/mail/u/0/#inbox"
    };
    linkMap["mcgill"] = {
        "start https://mycourses2.mcgill.ca/d2l/home",
        "start https://chatgpt.com/"
    };
    linkMap["cv"] = {
        "start C:\\Users\\ipman\\Desktop\\CV.docx",
        "start https://drive.google.com/drive/starred"
    };
    linkMap["va"] = {
        "code C:\\Users\\ipman\\Desktop\\VirtualAssistant\\main.cpp",
    };
    linkMap["web"] = {
        "code C:\\Users\\ipman\\portfolio-v2\\src\\app\\page.js",
    };

    // Task list and file path for saving/loading
    std::vector<std::string> tasks;
    const std::string taskFilePath = "./tasks.txt";

    // Load tasks from file
    loadTasks(tasks, taskFilePath);

    std::string command;

    // Print the banner with colors
    std::cout << CYAN << R"( _   _ _ 
| | | (_)
| |_| | |
|  _  | |
|_| |_|_|)" << RESET << '\n';

    while (true) {
        // Display tasks
        std::cout << GREEN << "\n=== Your Current Tasks ===\n" << RESET;
        displayTasks(tasks);

        // Prompt for command
        std::cout << YELLOW << "\nCommands: add, remove, link\n" << RESET;
        std::cout << BLUE << "> " << RESET;
        std::getline(std::cin, command);

        if (command == "add") {
            addTask(tasks);
        } else if (command == "remove") {
            removeTask(tasks);
        } else if (command == "link") {
            // Display links and prompt for link command
            std::cout << CYAN << "\n=== Available Links ===\n" << RESET;
            for (const auto& pair : linkMap) {
                std::cout << MAGENTA << pair.first << "\n" << RESET;
            }

            std::cout << YELLOW << "\nType a link command or 'back' to return:\n" << RESET;
            std::string linkCommand;
            std::getline(std::cin, linkCommand);

            if (linkCommand != "back") {
                auto it = linkMap.find(linkCommand);
                if (it != linkMap.end()) {
                    for (const auto& url : it->second) {
                        system(url.c_str());
                    }
                } else {
                    std::cout << RED << "Unknown link command.\n" << RESET;
                }
            }
        } else {
            std::cout << RED << "Unknown command. Try again.\n" << RESET;
        }
    }

    return 0;
}

// Display the task list
void displayTasks(const std::vector<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << YELLOW << "No tasks added yet." << RESET;
    } else {
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i] << "\n";
        }
    }
}

// Add a task to the task list
void addTask(std::vector<std::string>& tasks) {
    std::cout << CYAN << "Enter the task: " << RESET;
    std::string task;
    std::getline(std::cin, task);
    tasks.push_back(task);
    std::cout << GREEN << "Task added: " << task << "\n" << RESET;
}

// Remove a task from the task list
void removeTask(std::vector<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << YELLOW << "Task list is empty.\n" << RESET;
        return;
    }

    displayTasks(tasks);

    std::cout << CYAN << "Enter the task number to remove: " << RESET;
    int index;
    std::cin >> index;
    std::cin.ignore();  // Ignore leftover newline

    if (index > 0 && index <= static_cast<int>(tasks.size())) {
        std::cout << GREEN << "Task removed: " << tasks[index - 1] << "\n" << RESET;
        tasks.erase(tasks.begin() + index - 1);
    } else {
        std::cout << RED << "Invalid task number.\n" << RESET;
    }
}

// Save tasks to a file
void saveTasks(const std::vector<std::string>& tasks, const std::string& filePath) {
    std::ofstream outFile(filePath);
    if (!outFile) {
        std::cout << RED << "Failed to save tasks.\n" << RESET;
        return;
    }
    for (const auto& task : tasks) {
        outFile << task << "\n";
    }
    std::cout << GREEN << "Tasks saved successfully.\n" << RESET;
}

// Load tasks from a file
void loadTasks(std::vector<std::string>& tasks, const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        std::cout << YELLOW << "No previous tasks found. Starting fresh.\n" << RESET;
        return;
    }

    std::string task;
    while (std::getline(inFile, task)) {
        tasks.push_back(task);
    }
    std::cout << GREEN << "Tasks loaded successfully.\n" << RESET;
}