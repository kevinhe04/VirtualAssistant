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
void displayWelcome();
void addTask(std::vector<std::string>& tasks, const std::string& filePath);
void removeTask(std::vector<std::string>& tasks, const std::string& filePath);
void saveTasks(const std::vector<std::string>& tasks, const std::string& filePath);
void loadTasks(std::vector<std::string>& tasks, const std::string& filePath);
void clearScreen();
void save(const std::string& wordFilePath, const std::string& pdfFilePath, const std::string& googleDriveFileId);
std::string getAccessToken();


int main() {
    std::unordered_map<std::string, std::vector<std::string>> linkMap;
    linkMap["jobs"] = {
        "start https://www.notion.so/Internship-Tracker-a3f47e8497ca4a3e9e029e402e23dcd1",
        "start https://github.com/cvrve/Summer2025-Internships?tab=readme-ov-file",
        "start https://github.com/SimplifyJobs/Summer2025-Internships",
    };
    linkMap["302"] = {
        "start https://mycourses2.mcgill.ca/d2l/le/lessons/761768/units/8253943",
    };
    linkMap["223"] = {
        "start https://mycourses2.mcgill.ca/d2l/le/lessons/760742",
    };
    linkMap["251"] = {
        "start https://mycourses2.mcgill.ca/d2l/le/lessons/760694/units/8266935",
    };
    linkMap["310"] = {
        "start https://mycourses2.mcgill.ca/d2l/le/lessons/764709/units/8264299",
    };
    linkMap["204"] = {
        "start https://mycourses2.mcgill.ca/d2l/le/lessons/761014/units/8231371",
    };
    linkMap["312"] = {
        "start https://mycourses2.mcgill.ca/d2l/le/lessons/757544/units/8249044",
    };
    linkMap["cv"] = {
        "start C:\\Users\\ipman\\Desktop\\CV.docx",
        "start https://drive.google.com/drive/starred",
    };
    linkMap["va"] = {
        R"(cmd /k ""C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" && cd C:\Users\ipman\Desktop\VirtualAssistant && code ."")"
    };
    linkMap["web"] = {
        "code C:\\Users\\ipman\\portfolio-v2",
    };
    linkMap["app"] = {
        "code C:\\Users\\ipman\\picky-eats-mobile",
        "start https://expo.dev/",
        "start https://www.notion.so/Journal-tech-oriented-1251f47e48ae8039b505e8eed818300c",
        "start https://play.google.com/console/u/2/developers/6084813515183301990/app-list",
        "start https://chatgpt.com/",
        "start https://claude.ai/new",
    };


    // Task list and file path for saving/loading
    std::vector<std::string> tasks;
    const std::string taskFilePath = "./tasks.txt";

    loadTasks(tasks, taskFilePath);

    std::string command;

    while (true) {
        displayWelcome();
        std::cout << RESET << "\n=== Your Current Tasks ===\n" << RESET;
        displayTasks(tasks);

        // Prompt for command
        std::cout << RESET << "\nAdd/Remove task (add/remove) || Open links shortcut (sc) || Work on CV and upload to Google Drive (save)\n" << RESET;
        std::cout << RESET << ">> "<< RESET;
        std::getline(std::cin, command);

        if (command == "add") {
            addTask(tasks, taskFilePath);
        } else if (command == "save") {
            const std::string wordFilePath = "C:\\Users\\ipman\\Desktop\\CV.docx";
            const std::string pdfFilePath = "C:\\Users\\ipman\\Desktop\\CV.pdf";
            const std::string googleDriveFileId = "1JWfl8-4oR-525v0Jn7hS2tYlR8kE_zR9";
            save(wordFilePath, pdfFilePath, googleDriveFileId);
        } else if (command == "remove") {
            removeTask(tasks, taskFilePath);
        } else if (command == "clear") {
            clearScreen();
        } else if (command == "sc") {
            std::cout << CYAN << "\n=== Available Links ===\n" << RESET;
            std::cout << CYAN << "Jobs & Internships (jobs) \nMcGill (mcgill) \nEdit Resume (cv) \nEdit Virtual Assistant (va) \nEdit Web Portfolio (web) \nWork on PickyEats (app)\n" << RESET;
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

void displayWelcome() {
    std::cout << RESET << R"(  ____               _   _                   _  __          _         _ 
 / ___|_ __ ___  ___| |_(_)_ __   __ _ ___  | |/ /_____   _(_)_ __   | |
| |  _| '__/ _ \/ _ \ __| | '_ \ / _` / __| | ' // _ \ \ / / | '_ \  | |
| |_| | | |  __/  __/ |_| | | | | (_| \__ \ | . \  __/\ V /| | | | | |_|
 \____|_|  \___|\___|\__|_|_| |_|\__, |___/ |_|\_\___| \_/ |_|_| |_| (_)
                                 |___/                                  )" << RESET << '\n';
}
void displayTasks(const std::vector<std::string>& tasks) {
    for (size_t i = 0; i < tasks.size(); ++i) {
         std::cout << i + 1 << ". " << tasks[i] << "\n";
    }
}
void addTask(std::vector<std::string>& tasks, const std::string& filePath) {
    while (true) {
        std::cout << CYAN << "Enter the task (type 'q' to stop): " << RESET;
        std::string task;
        std::getline(std::cin, task);

        if (task == "q") {
            break;
        }

        tasks.push_back(task);
        std::cout << GREEN << "Task added: " << task << "\n" << RESET;
        saveTasks(tasks, filePath);
        clearScreen();
    }
}
void removeTask(std::vector<std::string>& tasks, const std::string& filePath) {
    if (tasks.empty()) {
        std::cout << YELLOW << "\nTask list is empty.\n" << RESET;
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
    saveTasks(tasks, filePath);
    clearScreen();
}
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
}

void clearScreen() {
    system("cls");
}

void save(const std::string& wordFilePath, const std::string& pdfFilePath, const std::string& googleDriveFileId) {
    // Convert Word to PDF
    std::string convertCommand = "start /wait winword.exe \"" + wordFilePath + "\" /mFileSaveAsPDF /q";
    int convertResult = system(convertCommand.c_str());

    if (convertResult != 0) {
        std::cout << RED << "Failed to convert Word document to PDF.\n" << RESET;
        return;
    }

    std::cout << GREEN << "Word document converted to PDF successfully.\n" << RESET;

    // Retrieve Access Token
    std::string accessToken = getAccessToken();
    if (accessToken.empty()) {
        std::cerr << RED << "Failed to retrieve access token.\n" << RESET;
        return;
    }

    // Upload PDF to Google Drive
    std::string uploadCommand = "curl -X PATCH "
                                 "-H \"Authorization: Bearer " + accessToken + "\" "
                                 "-H \"Content-Type: application/pdf\" "
                                 "--data-binary @" + pdfFilePath + " "
                                 "\"https://www.googleapis.com/upload/drive/v3/files/" + googleDriveFileId + "?uploadType=media\"";

    int uploadResult = system(uploadCommand.c_str());

    if (uploadResult == 0) {
        std::cout << GREEN << "Google Drive PDF updated successfully.\n" << RESET;
    } else {
        std::cerr << RED << "Failed to update PDF in Google Drive.\n" << RESET;
    }
}

std::string getAccessToken() {
    const std::string refreshToken = "1//04_xpC-T30NcLCgYIARAAGAQSNwF-L9IrqypV7KpSDi4qaSzXsgLeQo2D_lm5-5gsLWybiBXryUu1ujleTu3_Zw7pcr7B0mJKgBs";
    const std::string clientId = "1056673306501-73kn6ukbeedbh5nm558gm164c5e0sdt5.apps.googleusercontent.com";
    const std::string clientSecret = "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";
    const std::string tempFilePath = "./token_response.json";

    // Command to get a new access token and save the response to a file
    std::string tokenCommand = "curl -X POST "
                               "-d \"client_id=" + clientId +
                               "&client_secret=" + clientSecret +
                               "&refresh_token=" + refreshToken +
                               "&grant_type=refresh_token\" "
                               "https://oauth2.googleapis.com/token -s > " + tempFilePath;

    int result = system(tokenCommand.c_str());
    if (result != 0) {
        std::cerr << RED << "Failed to execute token command.\n" << RESET;
        return "";
    }

    // Read the token response from the file
    std::ifstream tokenFile(tempFilePath);
    if (!tokenFile) {
        std::cerr << RED << "Failed to open token response file.\n" << RESET;
        return "";
    }

    std::string tokenResponse((std::istreambuf_iterator<char>(tokenFile)), std::istreambuf_iterator<char>());
    tokenFile.close();    
    // Check if the response is empty
    if (tokenResponse.empty()) {
        std::cerr << RED << "Empty token response.\n" << RESET;
        return "";
    }

    // Find the access token with more robust parsing
    size_t startPos = tokenResponse.find("\"access_token\"");
    if (startPos == std::string::npos) {
        // Try alternative format
        startPos = tokenResponse.find("access_token");
        if (startPos == std::string::npos) {
            std::cerr << RED << "Access token not found in response.\n" << RESET;
            return "";
        }
    }

    // Find the next colon
    size_t colonPos = tokenResponse.find(":", startPos);
    if (colonPos == std::string::npos) {
        std::cerr << RED << "Malformed response - no colon found.\n" << RESET;
        return "";
    }

    // Find the next quote after the colon
    size_t quoteStart = tokenResponse.find("\"", colonPos);
    if (quoteStart == std::string::npos) {
        std::cerr << RED << "Malformed response - no opening quote found.\n" << RESET;
        return "";
    }

    // Find the closing quote
    size_t quoteEnd = tokenResponse.find("\"", quoteStart + 1);
    if (quoteEnd == std::string::npos) {
        std::cerr << RED << "Malformed response - no closing quote found.\n" << RESET;
        return "";
    }

    // Extract the token
    return tokenResponse.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
}