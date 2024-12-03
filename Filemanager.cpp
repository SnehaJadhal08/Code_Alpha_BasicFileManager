#include <iostream>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void displayMenu() {
    std::cout << "\n=== File Manager ===\n";
    std::cout << "1. List Directory Contents\n";
    std::cout << "2. Change Directory\n";
    std::cout << "3. View File\n";
    std::cout << "4. Create Directory\n";
    std::cout << "5. Copy File\n";
    std::cout << "6. Move File\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

void listDirectory(const fs::path& currentPath) {
    std::cout << "\nContents of " << currentPath << ":\n";
    for (const auto& entry : fs::directory_iterator(currentPath)) {
        std::cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ") 
                  << entry.path().filename().string() << '\n';
    }
}

void changeDirectory(fs::path& currentPath) {
    std::string newPath;
    std::cout << "Enter directory to navigate to: ";
    std::cin >> newPath;

    fs::path tempPath = currentPath / newPath;
    if (fs::exists(tempPath) && fs::is_directory(tempPath)) {
        currentPath = tempPath;
        std::cout << "Changed directory to " << currentPath << '\n';
    } else {
        std::cout << "Invalid directory.\n";
    }
}

void viewFile(const fs::path& currentPath) {
    std::string fileName;
    std::cout << "Enter file name to view: ";
    std::cin >> fileName;

    fs::path filePath = currentPath / fileName;
    if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
        std::ifstream file(filePath);
        std::string line;
        std::cout << "\nContents of " << filePath << ":\n";
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }
        file.close();
    } else {
        std::cout << "File does not exist or is not readable.\n";
    }
}

void createDirectory(const fs::path& currentPath) {
    std::string dirName;
    std::cout << "Enter directory name to create: ";
    std::cin >> dirName;

    fs::path dirPath = currentPath / dirName;
    if (!fs::exists(dirPath)) {
        fs::create_directory(dirPath);
        std::cout << "Directory created successfully.\n";
    } else {
        std::cout << "Directory already exists.\n";
    }
}

void copyFile(const fs::path& currentPath) {
    std::string sourceFile, destFile;
    std::cout << "Enter source file name: ";
    std::cin >> sourceFile;
    std::cout << "Enter destination file name: ";
    std::cin >> destFile;

    fs::path sourcePath = currentPath / sourceFile;
    fs::path destPath = currentPath / destFile;

    if (fs::exists(sourcePath) && fs::is_regular_file(sourcePath)) {
        fs::copy(sourcePath, destPath);
        std::cout << "File copied successfully.\n";
    } else {
        std::cout << "Source file does not exist.\n";
    }
}

void moveFile(const fs::path& currentPath) {
    std::string sourceFile, destFile;
    std::cout << "Enter source file name: ";
    std::cin >> sourceFile;
    std::cout << "Enter destination file name: ";
    std::cin >> destFile;

    fs::path sourcePath = currentPath / sourceFile;
    fs::path destPath = currentPath / destFile;

    if (fs::exists(sourcePath) && fs::is_regular_file(sourcePath)) {
        fs::rename(sourcePath, destPath);
        std::cout << "File moved successfully.\n";
    } else {
        std::cout << "Source file does not exist.\n";
    }
}

int main() {
    fs::path currentPath = fs::current_path();
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: listDirectory(currentPath); break;
            case 2: changeDirectory(currentPath); break;
            case 3: viewFile(currentPath); break;
            case 4: createDirectory(currentPath); break;
            case 5: copyFile(currentPath); break;
            case 6: moveFile(currentPath); break;
            case 7: std::cout << "Exiting...\n"; return 0;
            default: std::cout << "Invalid choice. Try again.\n"; break;
        }
    }
}
