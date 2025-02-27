# Go Game 🎮

This is a simple implementation of the classic board game **Go** with a visually interactive interface in the terminal. 🖥️

## About the Game 🏆
Go is a strategic board game that originated in China over 2,500 years ago. 🇨🇳 It is played by two players who take turns placing black and white stones ⚫⚪ on a grid. The goal is to control more territory than your opponent by surrounding empty spaces with your stones.

This project provides a terminal-based version of the game with a visual representation of the board, allowing players to move the cursor, place stones, and track scores.

At the beginning of the game, players can choose the board size before starting their match.

## Features ✨
- 🎲 Interactive board with visual representation in the terminal
- 📜 Basic implementation of Go rules
- 💾 Save and load game states
- 👥 Supports two-player local matches
- 📏 Players can choose the board size at the start of the game

## Installation & Running 🚀
Follow these steps to download, compile, and run the game on Windows:

### 1. Clone the Repository 📂
```sh
git clone https://github.com/your-username/Go_game.git
```

### 2. Navigate to the Project Directory 📁
```sh
cd Go_game
```

### 3. Run the Precompiled Version 🏁
The repository already includes a compiled `main.exe` file, so you can run the game without compilation:
```sh
cls
main.exe
```

### 4. (Optional) Compile the Program 🔧
If you want to compile the program yourself, use the following commands:

For MinGW (g++ compiler):
```sh
g++ -o Go_game main.cpp display.cpp file_managment.cpp game_state_editor.cpp stones.cpp variable_managment.cpp -std=c++17
```
Or for Visual Studio's `cl.exe`:
```sh
cl /EHsc main.cpp display.cpp file_managment.cpp game_state_editor.cpp stones.cpp variable_managment.cpp finish.cpp conio2.cpp
```

## Controls 🎮
- **Arrow keys**: Move the cursor over the board
- **Q**: Quit the game
- **N**: Start a new game
- **I**: Place a stone on the board
- **S**: Save the game state
- **L**: Load a saved game
- **F**: Finish the game and calculate scores

## Requirements 📌
- Windows OS 🪟
- C++ compiler (MinGW g++ or Visual Studio cl.exe) 🛠️ (only if compiling manually)
- Terminal that supports ASCII-based UI

## Screenshot 📸
Below is an example of the game running in the terminal:

![Go Game Terminal Interface](https://github.com/user-attachments/assets/07078469-a4ee-4ec4-ac90-acfac64bd4be)

## License 📜
This project is open-source and available under the MIT License.
