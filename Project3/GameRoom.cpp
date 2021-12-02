//Project 3
//Grace Ohlsen and Justin Jamrowski
#include "GameRoom.h"
#include <iostream>
#include <ctime>
using namespace std;

/*
This function takes in a string and returns it in its uppercase form
Parameters - string input (string w/ possible lowercase letters)
Return - string off input uppercases
*/
string toUpper(string input){
    int length = input.length();
    for (int i = 0; i < length; i++){
        
        if(input.at(i) >= 97 && input.at(i) <= 122){
            input.at(i) = (char)(input.at(i) - 32);
        }

    }
    return input;
}

/*
This function takes in a maximum and returns a random integer between 0 and the max.
Parameters - int max
Return - random number between 0 and max
*/
int getRand(int max)
{    
    int randNum = 0;
    
    randNum = rand() % max;
    return randNum;
}

// Constructor for GameRoom
GameRoom::GameRoom()
{
    srand(time(NULL));

    // randomize hangmanWord selction between 3 hangman words
    string words[] = {"bug", "rat", "fly"};
    int indexWords = getRand(3);
    hangmanWord = words[indexWords];

    // randomize fileName selection between 3 names 
    string fileNames[] = {"Zuckerberg.txt", "Bezos.txt", "Gates.txt"};
    int indexFile = getRand(3);
    fileName = fileNames[indexFile];


}

/*
This function returns the hangman word
Parameters - n/a
Return - hangmanWord (string)
*/
string GameRoom::getHangmanWord(){
    return hangmanWord;
}

/*
This function returns the filename to defeat the SuperComputer
Parameters - n/a
Return - fileName (string) where encryption to destroy computer is stored
*/
string GameRoom::getFileName(){
    return fileName;
}

/*
This function returns the string vector containing the encryption necessary to destroy the super computer
Parameters - n/a
Return - content (Vector<string)
*/
vector<string> GameRoom::getFileContent(){
    return fileContent;
}

/*
This function initiates the game of Hangman for the user and reveals the password to defeat the SuperComputer
Parameters - none
Return - void
*/
bool GameRoom::hangman()
{
    // assume the player has not won
    bool won = false;

    // start screen
    char start;


    cout << "\n\n\n   Hangman   " << endl;
    cout << "_____________" << endl;
    cout << "|      }     " << endl;
    cout << "|      O     " << endl;
    cout << "|      |     " << endl;
    cout << "|    / | \\  " << endl;
    cout << "|   /  |  \\ " << endl;
    cout << "|     / \\   " << endl;
    cout << "|    /   \\  " << endl;
    cout << "|            " << endl;
    cout << "|____________" << endl;
    
    cout << "\nPress any key to start." << endl;
    cin >> start;

    // game 

    // set variables used throughout the game
    string word = hangmanWord;
    

    // makes hidden word the length of the word
    string mysteryWord(word.length(),'*');

    int tries = 6; // max number of attempts to guess correctly
    char guess;
    bool correctGuess = false; // assume they guess wrong until proven otherwise
    char previousGuesses[7]; // array of guesses, needs to be one longer than the user can guess
    previousGuesses[0] = '\0';

    // start with no previous guesses
    for(int i = 1; i < 6; i++){
        previousGuesses[i] = '-';
    }

    previousGuesses[6] = '\0';

    // while the player still has tries, play game 
    while(tries >= 0){

        // reset bool
        correctGuess = false;

        // Display word information
        cout << "The word you have to guess is:\n" << endl;
        cout << mysteryWord << endl;

        // display number of letters in the word
        cout << "\nThere are " << mysteryWord.length() << " letters in the word\n\n";

        // display number of guesses left
        cout << "You have " << tries << " guesses left" << endl;

        // display previous guesses
        if(previousGuesses[0] == '\0'){
            cout << endl;
        }else{
            cout << "You have guessed: " << previousGuesses << endl;
        }

        // get player guess
        cout << "\n\nGuess a letter (lowercase)" << endl;
        cin >> guess;

        // Check if guess is correct
        for(int i = 0; i < mysteryWord.length(); i++){

            // if guess is correct, fill in letter in mysteryWord and indicate the guess was correct
            if(word[i] == guess){
                mysteryWord[i] = guess;

                correctGuess = true;
            }
        }
        // won game
        if(word == mysteryWord){ 
            cout << "\n\nCongrats! You've got the word correct: " << mysteryWord << endl;
            won = true;
            break; // end game
        }
        // incorrect guess
        if(correctGuess == false){
            tries--;
            cout << "Incorrect. " << guess << " is not part of the word." << endl;

        }else{
            // correct guess display... made this way so if letter is in word twice, doesn't print twice
            cout << "Correct! " << guess << " is one of the letters!" << endl;
        }

        // switch statement that prints hangman based on number of tries left
        switch(tries){
            case 6:{
                cout << "_____________" << endl;
                cout << "|      }     " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|____________" << endl;
                
                break;
            }
            case 5:{
                cout << "_____________" << endl;
                cout << "|      }     " << endl;
                cout << "|      O     " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|____________" << endl;
                
                // store incorrect guess in previousGuesses
                if(correctGuess == false){
                    previousGuesses[0] = guess;
                }
                break;
            }
            case 4:{

                cout << "_____________" << endl;
                cout << "|      }     " << endl;
                cout << "|      O     " << endl;
                cout << "|      |     " << endl;
                cout << "|      |     " << endl;
                cout << "|      |     " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|____________" << endl;

                // store incorrect guess in previousGuesses
                if(correctGuess == false){
                    previousGuesses[1] = guess;
                }
                break;
            }
            case 3:{

                cout << "_____________" << endl;
                cout << "|      }     " << endl;
                cout << "|      O     " << endl;
                cout << "|      |     " << endl;
                cout << "|    / |     " << endl;
                cout << "|   /  |     " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|____________" << endl;

                // store incorrect guess in previousGuesses
                if(correctGuess == false){
                    previousGuesses[2] = guess;
                }
                break;
            }
            case 2:{

                cout << "_____________" << endl;
                cout << "|      }     " << endl;
                cout << "|      O     " << endl;
                cout << "|      |     " << endl;
                cout << "|    / | \\  " << endl;
                cout << "|   /  |  \\ " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|            " << endl;
                cout << "|____________" << endl;

                // store incorrect guess in previousGuesses
                if(correctGuess == false){
                    previousGuesses[3] = guess;
                }
                break;
            }
            case 1:{

                cout << "_____________" << endl;
                cout << "|      }     " << endl;
                cout << "|      O     " << endl;
                cout << "|      |     " << endl;
                cout << "|    / | \\  " << endl;
                cout << "|   /  |  \\ " << endl;
                cout << "|     /      " << endl;
                cout << "|    /       " << endl;
                cout << "|            " << endl;
                cout << "|____________" << endl;

                // store incorrect guess in previousGuesses
                if(correctGuess == false){
                    previousGuesses[4] = guess;
                }
                break;
            }
            case 0:{

                // lost the game

                cout << "\nGAME OVER!\n\n" << endl;
                cout << "_____________" << endl;
                cout << "|      }     " << endl;
                cout << "|      O     " << endl;
                cout << "|      |     " << endl;
                cout << "|    / | \\  " << endl;
                cout << "|   /  |  \\ " << endl;
                cout << "|     / \\   " << endl;
                cout << "|    /   \\  " << endl;
                cout << "|            " << endl;
                cout << "|____________" << endl;
                
                if(correctGuess == false){
                    previousGuesses[5] = guess;
                }
                tries = -1;
                won = false;
                break;
            }
            default:{
                // shouldn't ever see this
                cout << "Error!" << endl;
            }
        }
        
    }
    return won; // return true if won, false if lost
 
}

/*
This function initiates the game of Trivia for the user and writes out to file needed to defeat SuperComputer
Parameters - none
Return - void
*/
bool GameRoom::trivia()
{
    // display option to play trivia
    int choice;
    cout << "Welcome to MetaVerse Trivia! Would you like to play? Press 1 to play and 2 to exit game." << endl;
    cin >> choice;

    // assume player has not won trivia unless proven otherwise
    bool won = false;

    do{
        switch(choice){
            case 1: { // PLAY TRIVIA
                
                string guess;

                // first question
                cout << "What year was Facebook created?"<< endl;
                cin >> guess;

                if(guess == "2004"){

                    // second question
                    cout << "Correct!" << endl;
                    cout << "What's President Zuckerberg's zodiac sign?" << endl;
                    cin >> guess;

                    if(toUpper(guess) == "TAURUS"){

                        // third question
                        cout << "Correct!" << endl;
                        cout << "What year did Facebook change its name to Meta?" << endl;
                        cin >> guess;

                        if(guess == "2021"){

                            // fourth question
                            cout << "Correct!" << endl;
                            cout << "What's the name of the Meta resistance organization?" << endl;
                            cin >> guess;

                            if(toUpper(guess)=="INFRA"){
                                // won trivia
                                cout << "Correct again, soldier. You've passed the test. Passed to you will be a file with the encryption code necessary to" << endl;
                                cout << "compromise the MetaComputer. Make sure you have it as well as the password to the computer before you try to shut it down." << endl;
                                cout << "We're counting on you... good luck." << endl;
                                won = true; // player won trivia
                                break; // exit trivia
                            }
                        }

                    }


                }
                // at some point, got a question wrong and did not win game 
                cout << "Incorrect. Maybe you'll do better next time." << endl;
                
                // return true if won, false if lost
                return won;
            }
            case 2: // QUIT
            
                cout << "Goodbye!" << endl;
                won = false;
            default: // INVALID INPUT
                cout << "Invalid input" << endl;
                won = false;
        }
    }while(choice > 2 || choice <= 0); // keep going if choice is between 0 and 2

    return won; // return true if won, false if lost
}