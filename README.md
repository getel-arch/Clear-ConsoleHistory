# Clear-ConsoleHistory
[![Build & Release](https://github.com/getel-arch/Clear-ConsoleHistory/actions/workflows/build_and_release.yaml/badge.svg)](https://github.com/getel-arch/Clear-ConsoleHistory/actions/workflows/build_and_release.yaml)

## Overview

`Clear-ConsoleHistory` is a utility designed to clear the PowerShell command history stored on Windows systems. It achieves this by directly truncating the `ConsoleHost_history.txt` file used by PowerShell's PSReadLine module to store command history.

## Technique Used

The program uses the following steps to clear the PowerShell history:

1. **Retrieve the User Profile Path**: The program uses the `SHGetFolderPathA` function from the Windows API to retrieve the user's profile directory. This ensures the program dynamically locates the correct path for the current user.

2. **Construct the History File Path**: The program appends the relative path to the PowerShell history file (`AppData\Roaming\Microsoft\Windows\PowerShell\PSReadLine\ConsoleHost_history.txt`) to the retrieved profile path.

3. **Open the History File**: Using the `CreateFileA` function, the program opens the history file with write permissions.

4. **Truncate the File**: The `SetEndOfFile` function is used to truncate the file, effectively clearing its contents without deleting the file itself.

5. **Error Handling**: The program includes robust error handling to provide feedback if any step fails, such as the inability to locate the file or insufficient permissions.

## Why It Is Stealthy

The technique used by this program is considered stealthy for the following reasons:

1. **No File Deletion**: Instead of deleting the history file, the program truncates it. This avoids creating a new file, which could leave traces in the file system or alert monitoring tools.

2. **Direct File Access**: By directly accessing the file using Windows API functions, the program bypasses higher-level PowerShell commands or scripts that might be logged or monitored.

3. **Minimal Footprint**: The program does not create any temporary files or leave behind artifacts. It operates entirely in memory and modifies only the target file.

4. **Native API Usage**: The use of native Windows API functions ensures compatibility and reduces the likelihood of detection by security tools that monitor for suspicious PowerShell activity.

5. **No External Dependencies**: The program does not rely on external libraries or tools, making it self-contained and less likely to trigger alarms.

## Usage

1. Compile the program using a C compiler (e.g., GCC).
2. Run the executable on a Windows system.
3. The program will clear the PowerShell history for the current user.

## Disclaimer

This program is provided under the GNU General Public License (GPLv3). It is intended for educational and ethical purposes only. The authors are not responsible for any misuse of this software.
