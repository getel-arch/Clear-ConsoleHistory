#include <windows.h>
#include <shlobj.h>
#include <stdio.h>

void clearPowerShellHistory() {
    char historyPath[MAX_PATH];

    // Get the path to the PowerShell history file
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, historyPath))) {
        strcat(historyPath, "\\AppData\\Roaming\\Microsoft\\Windows\\PowerShell\\PSReadLine\\ConsoleHost_history.txt");

        // Attempt to truncate the history file
        HANDLE fileHandle = CreateFileA(
            historyPath,
            GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (fileHandle != INVALID_HANDLE_VALUE) {
            if (SetEndOfFile(fileHandle)) {
                printf("PowerShell history cleared successfully.\n");
            } else {
                printf("Failed to truncate PowerShell history file. Error code: %lu\n", GetLastError());
            }
            CloseHandle(fileHandle);
        } else {
            printf("Failed to open PowerShell history file. Error code: %lu\n", GetLastError());
        }
    } else {
        printf("Failed to retrieve the user profile path.\n");
    }
}

int main() {
    printf("Clearing PowerShell history...\n");
    clearPowerShellHistory();
    return 0;
}
