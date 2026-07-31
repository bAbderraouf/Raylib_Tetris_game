# Raylib Tetris Game

A modern implementation of the classic **Tetris** game developed in **C++** using the **Raylib** graphics library. The project demonstrates object-oriented programming, game loop management, collision detection, grid manipulation, and real-time rendering.

▶️ Full gameplay video:  🔗 [Portfolio : https://babderraouf.github.io/portfolio/](https://babderraouf.github.io/portfolio/)

# Screenshot
![Tetris Game Screenshot](assets/screenshoots/C++Tetris2DGameraylib.gif)
## Features

* Classic Tetris gameplay
* Random Tetromino generation
* Piece movement and rotation
* Collision detection
* Automatic line clearing
* Score management
* Game Over detection
* Keyboard controls
* Clean object-oriented architecture

## Technologies

* **Language:** C++
* **Graphics Library:** Raylib
* **IDE:** Visual Studio
* **Version Control:** Git & GitHub

## Project Structure

```text
Raylib_Tetris_game/
│
├── assets/                 # Fonts, textures and game resources
├── include/                # Header files
├── src/                    # Source files
├── screenshots/            # Project screenshots
│
├── README.md
├── LICENSE
├── .gitignore
├── Tetris_raylib.sln
└── Tetris_raylib.vcxproj
```

## Project Architecture

The application is organized into several independent components:

* **Game** – Main game controller and game loop.
* **Grid** – Represents the game board and manages occupied cells.
* **Piece** – Defines the Tetrominoes and their behavior.
* **Position** – Utility structure for block coordinates.
* **main.cpp** – Application entry point.

This modular architecture makes the project easier to understand, maintain, and extend.

## Controls

| Key                                                    | Action       |
| ------------------------------------------------------ | ------------ |
| ←                                                      | Move Left    |
| →                                                      | Move Right   |
| ↓                                                      | Soft Drop    |
| ↑                                                      | Rotate Piece |

## Building the Project

### Requirements

* C++17 compatible compiler
* Raylib
* Visual Studio 2022 (recommended)

### Build

1. Clone the repository.

```bash
git clone https://github.com/bAbderraouf/Raylib_Tetris_game.git
```

2. Open the solution file:

```text
Tetris_raylib.sln
```

3. Build and run the project.

## Screenshots

Add screenshots inside the `screenshots/` directory and display them here.

Example:

```markdown
![Gameplay](screenshots/gameplay.png)
```

## Learning Objectives

This project was developed to strengthen skills in:

* Object-Oriented Programming
* Game Programming
* Collision Detection
* Data Structures
* Real-time Rendering
* Software Design
* C++ Best Practices

## Future Improvements

* Next piece preview
* Hold piece feature
* High score persistence
* Sound effects and music

## License

This project is released under the MIT License.
