#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to clear console window
void clearConsole() {
#ifdef _WIN32 // check if the operating system is Windows
    std::system("cls"); // clear the console window
#else // for other operating systems (e.g. Linux, macOS)
    std::system("clear"); // clear the console window
#endif
}

// Function to check if a given character is in the target word
bool isCharInWord(char c, const std::string& word);

// Function to play the Hangman game
void playHangman(int maxTries, const std::vector<std::string>& words);

// Main function
int main() {

    // Set the maximum number of tries for the game
    const int MAX_TRIES = 6;

    // Define lists of words for each difficulty level
    const std::vector<std::string> easyWords = { "dog", "cat", "rat", "hat", "cup", "egg", "sun", "fan", "pen", "map" };
    const std::vector<std::string> mediumWords = { "elephant", "zebra", "giraffe", "ostrich", "rhinoceros", "hippopotamus", "crocodile", "gazelle", "buffalo", "cheetah" };
    const std::vector<std::string> hardWords = { "university", "encyclopedia", "xylophone", "ophthalmology", "parliamentarian", "pharmaceutical", "zoological", "mythological", "encyclopedic", "unbelievable" };

    // Get the difficulty level from the user
    int level;
    std::cout << "Welcome to Hangman!\nPlease select a difficulty level (1-easy, 2-medium, 3-hard): ";
    std::cin >> level;

    // Set the list of words based on the chosen difficulty level
    std::vector<std::string> words;
    switch (level) {
    case 1:
        words = easyWords;
        break;
    case 2:
        words = mediumWords;
        break;
    case 3:
        words = hardWords;
        break;
    default:
        std::cout << "Invalid difficulty level. Exiting game." << std::endl;
        return 0;
    }

    // Seed the random number generator
    std::srand(std::time(0));

    // Start the game
    playHangman(MAX_TRIES, words);

    return 0;
}
// A function that returns true if the given character is in the given word
bool isCharInWord(char c, const std::string& word) {
    for (int i = 0; i < word.size(); i++) {
        if (c == word[i]) {
            return true;
        }
    }
    return false;
}

// A function that plays the Hangman game with the given maximum number of tries and list of words to choose from
void playHangman(int maxTries, const std::vector<std::string>& words) {
    // Choose a random word from the list of words
    std::string word = words[std::rand() % words.size()];

    // Initialize the guessed string with underscores for each letter, except for the first and last letter of the word
    std::string guessed(word.size(), '_');
    guessed[0] = word[0];
    guessed[word.size() - 1] = word[word.size() - 1];

    int numTries = 0; // Keep track of the number of tries so far

    while (numTries < maxTries) { // Loop until the maximum number of tries is reached
        clearConsole(); // Clear the console screen

        // Display the number of tries left and the current guessed word
        std::cout << "You have " << maxTries - numTries << " tries left." << std::endl;
        for (int i = 0; i < guessed.size(); i++) {
            std::cout << guessed[i] << " ";
        }
        std::cout << std::endl;

        // Ask the user to guess a letter or the full word
        std::string guess;
        std::cout << "Guess a letter or enter the full word: ";
        std::cin >> guess;

        if (guess == word) { // If the guess is the full word
            clearConsole(); // Clear the console screen
            std::cout << "Congratulations! You win! The word is " << word << std::endl; // Display the win message with the word
            return; // End the game
        }

        if (guess.size() == 1 && isCharInWord(guess[0], word)) { // If the guess is a single letter and it is in the word
            for (int i = 1; i < word.size() - 1; i++) { // Loop through the letters of the word, skipping the first and last letters
                if (word[i] == guess[0]) { // If the current letter matches the guess
                    guessed[i] = guess[0]; // Replace the underscore in the guessed string with the guessed letter
                }
            }
            if (guessed == word) { // If the guessed string is now equal to the word
                clearConsole(); // Clear the console screen
                std::cout << "Congratulations! You win! The word is " << word << "!" << std::endl; // Display the win message with the word
                return; // End the game
            }
        }
        else {
            clearConsole();
            std::cout << "Sorry, that letter is not in the word." << word << "!" << std::endl;
            numTries++;
        }
    }

    std::cout << "You lose! The word was " << word << "." << std::endl;
}
