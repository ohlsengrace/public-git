//Project 3
//Grace Ohlsen and Justin Jamrowski
#include "Player.h"
#include "CheatCode.h"
#include "Lobby.h"
#include "GameRoom.h"
#include "SuperComputer.h"
#include "Map.h"


#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;


/*
This function takes in a maximum and returns a random integer between 0 and the max.
Parameters - int max
Return - random number between 0 and max
*/
int getRandNum(int max)
{    
    int randNum = 0;
    
    randNum = rand() % max;
    return randNum;
}

/*
This function sorts an array of players by sorting by game status (win or loss) and number of steps
Parameters - Player arr[] (array of players), int n (number of players in player array)
Return - n/a... just prints to terminal
*/
void sortArray(Player arr[], int n)
{
    // Base case
    if (n == 1)
    {
        return;
    }

    // One pass of bubble sort. After the pass, the largest element is moved to end.
    for (int i = 0; i < n - 1; i++)
    {
        //sort by number of steps
        if(arr[i].getSteps() > arr[i+1].getSteps())
        {
            swap(arr[i], arr[i+1]);
        }

        //sort by wins and losses
        if ((arr[i].getGameStatus() == false && arr[i+1].getGameStatus() == true))
        {
            swap(arr[i], arr[i+1]);
        }
    }
 
    // Largest element is fixed, now it will recur for remaining array
    sortArray(arr, n - 1);
}

/*
Prints opening text of game
Parameters - n/a
Return - n/a
*/
void printOpeningText(){
    char randVariable;
    cout << "\nWelcome to the Metaverse!\n" << endl;
    cout << "Background: Today is December 2nd, 2051. It is the 30th anniversary of the Metaverse." << endl;
    cout << "The metaverse was created by Mark Zuckerberg and his company Facebook. It was advertised as" << endl;
    cout << "a place where you can virtually meet, work and play using a VR headset, glasses or your device." << endl;
    cout << "Users, in the billions, flocked to the stores to get their own VR headsets and everyone joined the Metaverse." << endl;
    cout << "At first, it was an addicting, incredible experience. One could escape the perils of capitalism, materialism," << endl;
    cout << "and social hierarchies. Every player was created equal. That is, until Metaverse started to evolve." << endl;
    cout << "As more players joined, the hierarchies from real life began to seep into the game. An online government and economy" << endl;
    cout << "emerged. Hit any key."<< endl;
    cin >> randVariable;
    cout << "Everything was under Zuckerberg's control. Crazed by the power from owning trillion dollar companies in both reality" << endl;
    cout << "and virtual reality... Zuckerberg became an online dictator. He began creating and distributing wealth to a select" << endl;
    cout << "few members of the game and censored any online chatter about his wrongdoings. People in reality and virtual reality" << endl;
    cout << "tried to fight back, but Zuckerberg has started to have total control of governments across the globe. He had created so much wealth" << endl;
    cout << "that every world leader and politician was under lobbyist control. And because of how much personal data the Metaverse" << endl;
    cout << "collected from players, it was impossible to live as usual in reality. With your data, companies knew if you stopped playing" << endl;
    cout << "in the Metaverse, and would halt your ability to live life outside of the game... limiting access to your capital, home, family, etc." << endl;
    cout << "Both worlds were becoming more and more corrupt. The power of the citizen had gone practically extinct. Hit any key." << endl;
    cin >> randVariable;
    cin.ignore();
    cout << "While hope is mostly lost, there are a few underground movements still attempting to shut down the game and restore" << endl;
    cout << "liberty and freedom to the world. Now, enter's you. The secret organization, 'Infra', created you, a completely virtual" << endl;
    cout << "entity that doesn't exist in reality but isn't under the control of the Metaverse. Free to roam the Metaverse under no" << endl;
    cout << "control, you are the world's last hope for defeating Zuckerberg. Go through the map to gain access to the Meta SuperComputer" << endl;
    cout << "and shut down the game. Watch out for viruses and keep a look out for Zuckerberg... or he'll shut you down" << endl;
    cout << "and the hope for peace will be long gone... Hit any key." << endl;
    cin >> randVariable;
    cin.ignore();
    cout << "Instructions: To move through the map, use 'w','s','a', and 'd'. You have an inventory of 3 items that can be viewed at anytime." << endl;
    cout << "The goal of the game is to disable the Super Computer (S) by entering the password and name of the destruction encryption file." << endl;
    cout << "Go to the Cheat Code, Game Room, or Lobby to collect what you need to disable the Super Computer. Beware of hidden viruses!" << endl;
    cout << "And be careful when you go to the Super Computer. If you put the wrong codes in, you will be destroyed! You only get one shot! " << endl;
    cout << "Good luck, soldier! Hit any key to begin.\n" << endl;
    cin >> randVariable;
    cin.ignore();
}

/*
This function runs the game
Parameters - none
Return - void
*/
void interactive()
{
    bool continuePlaying = true;
    int numTimesPlayed = 0;
    Player playerArray[5]; //new player added every attempts

    printOpeningText();

    do{


    // Initiate Player and set difficulty
    string playerName;
    cout << "Enter Player Name:" << endl;
    getline(cin,playerName);
    
    //set player name
    playerArray[numTimesPlayed].setName(playerName);

    // initialize difficulty and maxSteps
    int difficulty;
    int maxSteps ;

    bool invalidInput = false;

    // select level difficulty
        do{
            cout << "\nChoose difficulty: \n1: Easy\n2: Medium\n3: Hard" << endl;
            int difficultyChoice;
            cin >> difficultyChoice;
            
            if(difficultyChoice != 1 && difficultyChoice != 2 && difficultyChoice != 3){
                cout << "Invalid input. Try again." << endl;
                continue;
            }
            

            switch(difficultyChoice){
                case 1: // EASY
                {
                    difficulty = 1;
                    maxSteps = 80;
                    invalidInput = false;
                    break;
                }
                case 2: // MEDIUM
                {
                    difficulty = 2;
                    maxSteps = 55;
                    invalidInput = false;
                    break;
                }
                case 3: // DIFFICULT
                {
                    difficulty = 3;
                    maxSteps = 45;
                    invalidInput = false;
                    break;
                } 
                default:
                {
                    cout << "Invalid Input" << endl;
                    invalidInput = true;
                    break;
                }
            }
        }while(invalidInput == true);

    //print player name, difficulty, and max steps
    cout << "\nPlayer Name: "<< playerArray[0].getName() << ", Difficulty: " << difficulty << ", Max Steps: " << maxSteps << endl;

    // Build the Metaverse
    srand(time(0));

    GameRoom gm;
    Lobby lb(gm.getHangmanWord());
    SuperComputer sc(lb.getDestroyComputerCode(), gm.getFileName());

    // initialize Map

    Map map;  // create object called map of type Map
    map.spawnGameRoom(2, 0);
    map.spawnLobby(1,8);
    map.spawnSuperComputer(4,7);
    map.spawnCheatCode(0,3);

    int virusXCoord;
    int virusYCoord;

    bool terminated = false; //player not killed until proven otherwise
    
    //spawn viruses
    for(int i = 0; i < difficulty; i++){
        int yCoord = getRandNum(9);
        bool spawned = map.spawnVirus(3,yCoord);
        if(spawned){
            if(i == 0){ // if first virus spawned, save its coordinates
                virusXCoord = 3;
                virusYCoord = yCoord;
            }
        }
    }

    //one of the viruses coordinates are saved and displayed by cheatcode
    CheatCode cc(virusXCoord,virusYCoord);

    char move;  // for storing user input


    // Run Game

    // quit after maxSteps
    for(int i = 0; i < maxSteps; i++) {

        cout << "\nYou have " << maxSteps - i << " steps left.\n" << endl;
        map.displayMap();  // pretty print map_data in terminal

        cout << "Valid moves are: " << endl; 
        map.displayMoves();  // give user a menu of valid moves to pick from
        
        cout << "Input a move: "; 
        cin >> move;
        cout << endl;
        map.executeMove(move, playerArray[numTimesPlayed]);  // move the player on map based on user input

        if (map.isGameRoomLocation()) {


            bool continueGameRoom = true;

            do{
            
            //print gameroom menu
            cout << "Welcome to the Game Room!" << endl;
            cout << "Select one of the following options:" << endl;
            cout << "1. Play hangman" << endl;
            cout << "2. Play trivia" << endl;
            cout << "3. Exit" << endl;
            int choice;
            cin >> choice;
            
            //input validation
            if(choice != 1 && choice != 2 && choice != 3){
                cout << "Invalid input. Try again." << endl;
                continue;
            }

            switch(choice){
                case 1:{ // hangman
                    bool hangman = gm.hangman();

                    if(hangman){
                        //won hangman and word saved into inventory
                        bool added = playerArray[numTimesPlayed].addToInventory("hangman word: " + gm.getHangmanWord());
                        if(added){
                            cout << "Hangman word was added to inventory." << endl;
                        }else{
                            cout << "Error in adding hangman to inventory." << endl;
                        }
                    //lost hangman
                    }else{
                        cout << "Better luck next time!\n" << endl;
                    }

                    cout << "\n" ;
                    continueGameRoom = true;
                    
                    break;
                }
                case 2:{ // trivia
                    bool trivia = gm.trivia();
                    if(trivia){

                        //won trivia and file stored into inventory
                        cout << "You won trivia. The name of the destruction encryption file will be stored in your inventory." << endl;

                        // write out to file
                        ofstream outfile;
                        outfile.open(gm.getFileName());

                        if(outfile.is_open()){

                        for(int i = 0; i < sc.getFileContent().size(); i++){
                            outfile << sc.getFileContent().at(i) << "\n" ;
                        }

                        playerArray[numTimesPlayed].addToInventory("file: " + gm.getFileName());

                        }else{
                            cout << "Error in uploading file" << endl;
                        }
                        outfile.close();

                    //lost trivia
                    }else{
                        cout << "You lost trivia."<< endl;
                    }

                    cout << "\n" ;
                    continueGameRoom = true;
                    break;
                }
                case 3:{ // quit
                    cout << "Exiting game room..." << endl;
                    continueGameRoom = false;
                    break;
                }
                default:{
                    cout << "Invalid input." << endl;
                    continueGameRoom = true;
                }
            }

            }while(continueGameRoom == true);

        }

        if(map.isLobbyLocation()) {

            bool continueLobby = true;

            do{
                //print lobby menu
                cout << "Welcome to the Lobby!" << endl;
                cout << "Select one of the following options:" << endl;
                cout << "1. Enter chat room 1" << endl;
                cout << "2. Enter chat room 2" << endl;
                cout << "3. Enter chat room 3" << endl;
                cout << "4. Exit" << endl;

                int lobbyChoice;
                cin >> lobbyChoice;

                //input validation
                if(lobbyChoice != 1 && lobbyChoice != 2 && lobbyChoice != 3 && lobbyChoice != 4){
                    cout << "Invalid input. Try again." << endl;
                    continue;
                }
                

                switch(lobbyChoice){
                    case 1:{ //Room 1
                        lb.printRoomOneChat();
                        continueLobby = true;
                        break;
                    }
                    case 2:{ //Room 2
                        lb.printRoomTwoChat();
                        continueLobby = true;
                        break;
                    }
                    case 3:{ //Room 3
                        bool correct = lb.roomThreeEntrance();
                        if(correct){
                            //correct password
                            string passcode = "passcode: " + lb.printRoomThreeChat();
                            
                            bool added = playerArray[numTimesPlayed].addToInventory(passcode);
                            //added to inventory
                            if(added){
                                cout << "Passcode added to inventory." << endl;
                            }
                            //unable to add to inventory
                            else{
                                cout << "Unable to add passcode to inventory. May be already stored." << endl;
                            }
                            
                            
                        }
                        //incorrect password
                        else{
                            cout << "Password to room 3 incorrect." << endl;
                        }
                        continueLobby = false;
                        break;
                    }
                    case 4:{ //EXIT
                        continueLobby = false;
                        cout << "Exiting Lobby..." << endl;
                        break;
                    }
                    default:{
                        cout << "Invalid Input." << endl;
                        continueLobby = true;
                    }
                }

            }while(continueLobby);
        }

        if(map.isSuperComputerLocation()){
            bool continueComputer = true;

            do{
            //if terminated, end game
            if(terminated == true){
                break;
            }
            //print super computer menu
            cout << "\nYou have accessed the SuperComputer." << endl;
            cout << "Select one of the following options:" << endl;
            cout << "1. Deactivate the computer" << endl;
            cout << "2. Exit" << endl;

            int computerChoice;
            cin >> computerChoice;

            switch(computerChoice){
                case 1:{ // DEACTIVATE COMPUTER

                    //display inventory
                    cout << "Here is your inventory: ";
                    playerArray[numTimesPlayed].printInventory();
                    cout << "\n";

                    //get user input for password
                    cout << "Enter password: " ;
                    string inputPass;
                    cin >> inputPass;

                    if(inputPass == sc.getPasswordToDestroy()){
                        // password was correct
                        cout << "The password was correct." << endl;

                        //get user input for file name
                        cout << "Enter name of the file to deactivate the computer (include .txt extension): " ;
                        string inputFile;
                        cin >> inputFile;

                        if(inputFile == sc.getFileName()){
                            // correct filename
                            bool correctFile = sc.fileContentMatches(inputFile);
                            if(correctFile){
                                // won game 
                                cout << "Congratulations you have won the game!\n" << endl;
                                playerArray[numTimesPlayed].setGameStatus(true); //set game status to won
                                continueComputer = false;
                                break;
                            //incorrect file, game is over
                            }else{
                                cout << "Incorrect file. You have been terminated.\n" << endl;
                                continueComputer = false;
                                terminated = true; //player terminated
                                break;
                            }
                        }
                        //incorrect file
                        else{
                            cout << "Incorrect file. You have been terminated.\n" << endl;
                            continueComputer = false;
                            terminated = true; //player terminated
                            break;
                        }
                    }
                    //incorrect password
                    else{
                        cout << "Incorrect password. You have been terminated.\n" << endl;
                        terminated = true; //player terminated
                        break;;
                    }

                    break;
                }
                case 2:{ // EXIT
                    cout << "Exiting Super Computer..." << endl;
                    continueComputer = false;
                    break;
                }
                default:{
                    cout << "Invalid input." << endl;
                    continueComputer = true;
                }
            }

            }while(continueComputer);

        }

        if(map.isCheatCodeLocation()){
            //print cheatcode information
            cout << "Information drop from Infra..." << endl;
            cout << "Intelligence has detected a virus at " ;
            cc.printCheatCode();
            cout << "\n";
        }

        if (map.isVirusLocation()) {
            cout << "You've encountered a Virus!" << endl;

            int num;
            //print virus message, and get user input
            cout << "Enter a number between 0-2. If the number is correct, the virus will be deactivated. If not, the game is over." << endl;
            cin >> num;

            //input validation
            if(num != 0 && num != 1 && num != 2){
                cout << "Invalid input. Game terminated." << endl;
                terminated = true; //player terminated
                break;
            }

            int deactivateNum = getRandNum(3);

            //if correct number, continue game
            if(num == deactivateNum){
                cout << "Correct! The virus has been deactivated.\n" << endl;
            }
            //if the number is incorrect, game is ended
            else{
                cout << "The number was incorrect. The answer was "<< deactivateNum << ". Game terminated.\n" << endl;
                terminated = true; //player terminated
                break;
            }
            
        }

        //if the game is won or player is killed, the game is ended
        if(playerArray[numTimesPlayed].getGameStatus() == true || terminated == true){
            break;
        }
        playerArray[numTimesPlayed].addStep();
    }

    // Game Over
    numTimesPlayed++;

    // End of Game Menu

    // select end of menu choice
        bool wrongInput;
        do{
            
            //print end menu
            cout << "-----END OF GAME-----" << endl;
            playerArray[numTimesPlayed - 1].getPlayerStats();
            cout << "Select one of the following options:" << endl;
            cout << "1: See leaderboard" << endl;
            cout << "2: Play again" << endl;
            cout << "3: Quit" << endl;

            //get user input
            int endChoice;
            cin >> endChoice;

            //input validation
            if(endChoice != 1 && endChoice != 2 && endChoice != 3){
                cout << "Invalid input. Try again." << endl;
                continue;
            }

            switch(endChoice){
                case 1: // LEADERBOARD
                {
                    //print leaderboard
                    cout << "\nLEADERBOARD:" << endl;
                    sortArray(playerArray, numTimesPlayed);

                    for(int i = 0; i < numTimesPlayed; i++)
                    {
                        cout << i + 1 << ". " ;
                        playerArray[i].getPlayerStats();
                    }
                    cout << "\n";
                    wrongInput = true;
                    break;
                }
                case 2: // PLAY AGAIN
                {
                    wrongInput = false;

                    //if player has played 5 times (max number of times avaiable to play), exit program
                    if(numTimesPlayed == 5){
                        cout << "Sorry, you've reached the max number of tries. Better luck next time!" << endl;
                    }
                    cin.ignore();
                    break;
                }
                case 3: // QUIT
                {
                    cout << "Exiting game..." << endl;

                    //remove files
                    remove("Bezos.txt");
                    remove("Zuckerberg.txt");
                    remove("Gates.txt");

                    continuePlaying = false;
                    wrongInput = false;
                    break;
                } 
                default:
                {
                    cout << "Invalid Input" << endl;
                    wrongInput = true;
                    break;
                }
            }
        }while(wrongInput == true);
    
    }
    //continue program while number of times played is under 5 and player still wants to play
    while(numTimesPlayed < 5 && continuePlaying);

}

int main()
{
    interactive();

    return 0;
}