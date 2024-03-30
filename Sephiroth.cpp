#include <iostream>
#include <windows.h>
#include <string.h>
#include <lm.h>
#include <filesystem>
#include <stdlib.h>
#include <lmaccess.h>

// g++ Sepiroth.cpp -o Sephiroth.exe -lnetapi32

#pragma comment(lib, "netapi32.lib")

// Clean the "reverse shell" from startup folder
int cleanStartupFolder() { 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::filesystem::path target = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\cmd.exe";

    try {
        if (std::filesystem::remove(target)) {
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << "Successfully cleaned file from Startup Folder" << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        } else {
            SetConsoleTextAttribute(hConsole, 6);
            std::cout << "File doesn't exist" << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
    } catch (std::exception& e) {
        std::cout << e.what();
    }
    
    return 0;
} 

int removeRunKey() {
    HKEY hKey = NULL;
    const char* exe = "C:\\Windows\\System32\\cmd.exe";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    LONG res = RegOpenKeyExA(
        HKEY_CURRENT_USER,
        (LPCSTR)"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
        0,
        KEY_ALL_ACCESS,
        &hKey
    );

    if (res == ERROR_SUCCESS) {
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << "Successfully opened key, attempting to delete now..." << std::endl;
        SetConsoleTextAttribute(hConsole, 15);

        LONG res2 = RegDeleteValueA(
            hKey,
            (LPCSTR)"hacked"
        );
        if (res2 == ERROR_SUCCESS) {
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << "Successfully deleted key, closing key now..." << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        } else {
            SetConsoleTextAttribute(hConsole, 6);
            std::cout << "Key doesn't exist " << res << std::endl;;
            SetConsoleTextAttribute(hConsole, 15);
        }
        RegCloseKey(hKey);
    } else {
        SetConsoleTextAttribute(hConsole, 4); 
        std::cout << "Failed with code: " << res << std::endl;;
        SetConsoleTextAttribute(hConsole, 15);
    }

    return 0;
}



// Delete HackedAdmin User
int deleteUser() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const wchar_t* username = L"HackedAdmin";

    try {
        // Add the user
        LONG res = NetUserDel(
            NULL,
            username
        );

        if (res == NERR_Success) {
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << "Successfully deleted HackedAdmin user" << std::endl;
        SetConsoleTextAttribute(hConsole, 15);
        } else {
            SetConsoleTextAttribute(hConsole, 6);
            std::cout << "Couldn't delete HackedAdmin user, this probably means they don't exist" << std::endl;
            SetConsoleTextAttribute(hConsole, 15);  
        }
    } catch (std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}



int removeService() {
    return 0;
}



int removeHKCUEnvironment() {
    HKEY hKey = NULL;
    const char* exe = "C:\\Windows\\System32\\cmd.exe";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    LONG res = RegOpenKeyExA(
        HKEY_CURRENT_USER,
        (LPCSTR)"Environment",
        0,
        KEY_ALL_ACCESS,
        &hKey
    );

    if (res == ERROR_SUCCESS) {
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << "Successfully opened Environment key, attempting to delete now..." << std::endl;
        SetConsoleTextAttribute(hConsole, 15);

        LONG res2 = RegDeleteValueA(
            hKey,
            (LPCSTR)"UserInitMprLogonScript"
        );
        if (res2 == ERROR_SUCCESS) {
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << "Successfully deleted Environment key, closing key now..." << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        } else {
            SetConsoleTextAttribute(hConsole, 6);
            std::cout << "Key doesn't exist " << res << std::endl;;
            SetConsoleTextAttribute(hConsole, 15);
        }
        RegCloseKey(hKey);
    } else {
        SetConsoleTextAttribute(hConsole, 4); 
        std::cout << "Failed with code: " << res << std::endl;;
        SetConsoleTextAttribute(hConsole, 15);
    }

    return 0;
}

int main() {
    cleanStartupFolder();
    removeRunKey();
    deleteUser();
    removeService();
    removeHKCUEnvironment();

    return 0;
}
