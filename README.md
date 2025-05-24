# 🚴 Vélo Game – Bike Racing Game in C++ / SDL2

## 🎯 Introduction

This project was developed as part of the Object-Oriented Programming (OOP) module. The goal was to apply key OOP concepts in C++ through the development of an interactive game using the SDL2 library.

We made use of concepts such as:
- Class design, inheritance, polymorphism  
- Friend functions, templates, exceptions  
- Use of the STL  
- Modular code structure  

This game was also an opportunity to strengthen our skills in teamwork, planning, and problem-solving.

---

## 🧠 Design and Modeling

### 📌 Class Diagram (UML)

- `Game` is the main class, orchestrating the entire game.
- `Player`, `Obstacle`, `Timer`, `Menu`, and `Constantes` are components used by `Game`.
- `Game` owns a `Timer` (composition).
- The other classes are used via simple associations.

---

## 🧩 Class Descriptions

### `Game`
- Manages the game logic: `init()`, `run()`, `render()`, `handleEvents()`, etc.
- Handles end-game buttons with `renderButtons()`.

### `Player`
- Represents the cyclist.
- Methods: `handleInput()`, `update()`, `render()`, `collidesWith()`...

### `Obstacle`
- Represents obstacles on the road.
- Methods: `update()`, `render()`, `getType()`...

### `Timer`
- Manages the countdown.
- Methods: `reset()`, `getRemainingTime()`, `render()`

### `Menu`
- Displays the home screen, buttons, and the About page.

### `Constantes.h`
- Contains global configuration values (dimensions, speeds, paths...).

---

## ⚙️ Work Environment

### 🧰 Microsoft Visual Studio
- Main IDE used.
- Good support for C++ and SDL2.
- Efficient for managing complex projects.

### 🎮 SDL2
- Multimedia library for graphics rendering, keyboard/mouse events, etc.
- Open-source, cross-platform, widely used for games.

---

## 🛠️ Implementation

The project is divided into several files:
- `main.cpp`, `Game.cpp/.h`, `Player.cpp/.h`, `Obstacle.cpp/.h`, `Timer.cpp/.h`, `Menu.cpp/.h`, `Constantes.h`

### 🔁 Workflow
- **Initialization**: loading images, fonts, textures
- **Main loop**: events → update → render
- **Obstacles**: generated dynamically, some fatal, others slowing down the player
- **Player**: can jump, collisions are detected

---

## 🖥️ Game Interfaces

### 🎮 Main Screen
- Player, obstacles, animated background, timer, win/lose display

### ❌ Game Over / Victory Screen
- Image + `Retry` and `Quit` buttons

### 🏠 Main Menu
- Buttons: `Play`, `About`, `Quit` with hover effects

### ℹ️ About Page
- Game rules, controls, tips

---

## 💣 Obstacles

- Fatal obstacles generated dynamically  
- Collision → immediate `Game Over`

---

## ✅ Conclusion

This project allowed us to:
- Strengthen our C++ skills  
- Manage a project from start to finish  
- Solve real challenges independently  
- Collaborate efficiently and structure our work  

It marks an important step in our learning journey and serves as a springboard for future professional or personal projects.
