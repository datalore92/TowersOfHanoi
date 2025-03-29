# Towers of Hanoi Interactive Game

An interactive implementation of the classic Towers of Hanoi puzzle with a graphical interface. Features multiple difficulty levels, intuitive mouse controls, and cross-platform support for Windows and Linux.

## Quick Start (Pre-built Binaries)

1. Go to the [Releases](../../releases) page
2. Download the appropriate file for your system:
   - Windows: `TowersOfHanoi-windows.zip`
   - Linux: `TowersOfHanoi-linux.tar.gz`

### Windows Users
1. Extract `TowersOfHanoi-windows.zip` to any folder
2. Double-click `hanoi.exe`

### Linux Users
1. Download the Linux release tar.gz
2. Extract: `tar xzf TowersOfHanoi-linux.tar.gz`
3. Run: `./hanoi`

Note: The Linux binary requires SDL2 and SDL2_ttf to be installed:
```bash
# Ubuntu/Debian
sudo apt-get install libsdl2-2.0-0 libsdl2-ttf-2.0-0

# Fedora
sudo dnf install SDL2 SDL2_ttf
```

## Overview
This is an interactive Towers of Hanoi game implemented in C using SDL2 and SDL2_ttf. Unlike an automatic solver, the game lets you play by moving disks between towers with your mouse. You can choose your difficulty level during startup.

## Features
- **Interactive Play:** Click on a tower to select the top disk and then click on another tower to move it—only valid moves are allowed.
- **Difficulty Selection:** Choose between Easy (3 disks), Medium (5 disks), or Hard (8 disks).
- **Win Screen:** When you complete the puzzle, you’ll see a “You win!” message along with options to either play again or quit.

## Dependencies

### Windows
1. **Install MSYS2:**
   - Download the installer from https://www.msys2.org/
   - Run the installer and follow the prompts
   - At the end of installation, keep "Run MSYS2 now" checked and click Finish
   - When MSYS2 opens, first update the package database and core packages:
     ```
     pacman -Syu
     ```
   - Close the terminal when it asks you to
   - Reopen MSYS2 (from Start Menu: MSYS2 MSYS) and run:
     ```
     pacman -Su
     ```
   - Finally, install required development packages:
     ```
     pacman -S mingw-w64-x86_64-gcc
     pacman -S mingw-w64-x86_64-SDL2
     pacman -S mingw-w64-x86_64-SDL2_ttf
     pacman -S mingw-w64-x86_64-cmake
     pacman -S make
     ```
   - Add MSYS2's mingw64 bin folder to your Windows PATH:
     1. Open Windows Settings
     2. Search for "Edit the system environment variables"
     3. Click "Environment Variables"
     4. Under "System variables", find and select "Path"
     5. Click "Edit"
     6. Click "New"
     7. Add this path: `C:\msys64\mingw64\bin` (or wherever you installed MSYS2)
     8. Click "OK" on all windows
   - Restart any open terminals or IDEs

### Linux
Ubuntu/Debian:
```bash
sudo apt-get install gcc make cmake
sudo apt-get install libsdl2-dev libsdl2-ttf-dev
```

Fedora:
```bash
sudo dnf install gcc make cmake
sudo dnf install SDL2-devel SDL2_ttf-devel
```

## Building from Source

If you prefer to build from source:

1. Clone the repository:
   ```bash
   git clone https://github.com/YourUsername/TowersOfHanoi.git
   cd TowersOfHanoi
   ```

2. Follow the build instructions below for your platform.

## Build Instructions

### Windows
Using Command Prompt (cmd.exe):
```
mkdir build
cd build
cmake ..
cmake --build .
```

Or using the provided build script:
```
build.bat
```

### Linux/MSYS2
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Using Make (Linux/MSYS2)
```bash
make
```

### Run the Game
On Linux/MSYS2:
```bash
./hanoi
```

On Windows (CMD):
```bash
hanoi.exe
```

## Gameplay
- **Difficulty Selection:** When you start the program, click on one of the buttons to select the number of disks.
- **Move Disks:** Click on a tower to select the disk (only the top disk can be moved), then click on another tower to move it. A move is only allowed if the disk is placed on an empty rod or on a larger disk.
- **Winning:** Once all disks are moved to a non-initial tower, a win screen appears showing a "You win!" message with "Play Again" and "Quit" options.

Enjoy the game and have fun solving the puzzle!
