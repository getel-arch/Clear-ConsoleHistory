#include <windows.h>
#include <stdio.h>

void printConsoleHistory(const char *exeName) {
    DWORD historyLength = GetConsoleCommandHistoryLengthA((LPSTR)exeName);
    if (historyLength == 0) {
        printf("No console history found for %s.\n", exeName);
        return;
    }

    char *buffer = (char *)malloc(historyLength + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for console history.\n");
        return;
    }

    if (GetConsoleCommandHistoryA(buffer, historyLength, (LPSTR)exeName)) {
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
    ExpungeConsoleCommandHistoryA((LPSTR)exeName);
    printf("PowerShell console history cleared successfully.\n");

    printf("Console history after clearing:\n");
    printConsoleHistory(exeName);

    return 0;
}
