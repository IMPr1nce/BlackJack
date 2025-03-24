# BlackJack Game Implementation

## Overview
This is a C implementation of the classic **BlackJack** card game. The project features a command-line interface that allows players to engage in a realistic card-playing experience, with functionalities such as saving and resuming gameplay.

## Features
- **Save and Resume Gameplay:** Uses a text file (`save.txt`) to store game progress.
- **Object-Oriented Design:** Implements structured data types for efficient card and deck management.
- **File Handling:** Reads and writes game data using structured text files.
- **User-Friendly Interface:** Interactive text-based gameplay experience.
- **Dealer AI:** Implements logic for automated dealer gameplay.

## Technologies Used
- **Programming Language:** C
- **Libraries:** Standard C Library (stdio.h, stdlib.h, string.h)
- **File Format:** Text file for game state persistence

## Installation
1. Clone this repository:
   ```sh
   git clone https://github.com/yourusername/blackjack-game.git
   cd blackjack-game
   ```
2. Compile the program using gcc:
   ```sh
   gcc main.c deck.c hand.c -o blackjack
   ```
3. Run the game:
   ```sh
   ./blackjack
   ```

## How to Play
1. The player starts with two cards and can choose to **hit** (draw a card) or **stand** (keep current hand).
2. The dealer also draws cards, following fixed rules.
3. The goal is to reach a hand value as close to 21 as possible without exceeding it.
4. The game supports saving and resuming progress using `save.txt`.
5. The game allows betting and tracks player chips.

## File Structure
```
blackjack-game/
│── src/
│   ├── main.c       # Main game logic
│   ├── deck.c       # Deck management
│   ├── deck.h       # Deck header file
│   ├── hand.c       # Hand management
│   ├── hand.h       # Hand header file
│── data/
│   ├── save.txt     # Saved game data
│── README.md
│── LICENSE
```

## Future Improvements
- Add graphical UI using SDL or OpenGL
- Implement multiplayer mode
- Enhance AI decision-making for dealer moves
- Improve save file format using JSON or binary serialization

## Contributing
Contributions are welcome! Feel free to submit a pull request or open an issue.
