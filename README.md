
# Wordle Game in C 

A simple **command-line Wordle game** built in **C**, where players get **5 attempts** to guess a randomly selected 5-letter word. The game provides **color-coded feedback** to guide the player toward the correct word.  

## Features  
- ✅ Random word selection from a predefined word list  
- ✅ Validates user input (only 5-letter words allowed)  
- ✅ Provides color-coded feedback:  
  - 🟩 **Green**: Correct letter in the correct position  
  - 🟨 **Yellow**: Correct letter in the wrong position  
  - 🟥 **Red**: Letter not in the word  
- ✅ Secure coding practices – memory safety, input validation, and error handling  
- ✅ Simple and easy-to-use interface  

##  How to Play  
1. Run the program. 
2. Enter a **valid 5-letter word**.  
3. Get color-coded hints after each guess.  
4. You have **5 attempts** to guess the correct word.  
5. If you guess correctly, you win! Otherwise, the correct word is revealed.  

##  Installation & Compilation  
### Prerequisites  
- GCC compiler (or any C compiler)  
- Linux/macOS (or Windows with WSL)  

### Steps  
#### 1️⃣ Clone the repository:  
   ```
   git clone https://github.com/yourusername/wordle-game-c.git
   cd wordle-game-c
  ```
#### 2️⃣ Compile the program:
 ```
   gcc wordle.c -o wordle
  ```
#### 3️⃣ Run the game:
   ```
    ./wordle
  ```
## 🚀 Future Improvements
- 🔹 Add a **graphical interface (GUI)** for better user experience
- 🔹 Enhance the **word validation mechanism**
- 🔹 Implement **difficulty levels**

## 📢 Contributing
Feel free to **fork** this repository and **submit pull requests**. Any suggestions or improvements are welcome!

## 📜 License
This project is **open-source** and available under the **MIT** License.

## 🎉 Have fun playing Wordle in C!
If you like this project, ⭐ **star** the repo and **share your feedback**!
