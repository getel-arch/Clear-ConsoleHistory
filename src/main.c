#include <windows.h>
#include <stdio.h>

// Declare the function prototypes
BOOL WINAPI ExpungeConsoleCommandHistoryA(LPCSTR exeName);
DWORD WINAPI GetConsoleCommandHistoryLengthA(LPCSTR exeName);
DWORD WINAPI GetConsoleCommandHistoryA(LPSTR buffer, DWORD bufferLength, LPCSTR exeName);

void printConsoleHistory(const char *exeName) {
    DWORD historyLength = GetConsoleCommandHistoryLengthA(exeName);
    if (historyLength == 0) {
        printf("No console history found for %s.\n", exeName);
        return;
    }

    char *buffer = (char *)malloc(historyLength + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for console history.\n");
        return;
    }

    if (GetConsoleCommandHistoryA(buffer, historyLength, exeName)) {
        buffer[historyLength] = '\0'; // Null-terminate the buffer
        printf("Console history for %s:\n%s\n", exeName, buffer);
    } else {
        printf("Failed to retrieve console history for %s. Error code: %lu\n", exeName, GetLastError());
    }

    free(buffer);
}

int main() {
    const char *exeName = "powershell.exe";

    printf("Console history before clearing:\n");
    printConsoleHistory(exeName);

    // Call ExpungeConsoleCommandHistoryA to clear the console history for PowerShell
    if (ExpungeConsoleCommandHistoryA(exeName)) {
        printf("PowerShell console history cleared successfully.\n");
    } else {
        printf("Failed to clear PowerShell console history. Error code: %lu\n", GetLastError());
    }

    printf("Console history after clearing:\n");
    printConsoleHistory(exeName);

    return 0;
}
