#include "Listener.h"
#include "Song.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* DESCRIPTION GOES HERE */ 





// HELPER FUNCTIONS


/* 
This function takes a string and splits into pieces based on a seperator and stores the pieces in an array of a user-given size
Parameters: string myStr (the string being split), char seperator, string arr[] (where pieces are stored), int arr_size (cannot get size of arr[] without input)
Return: int num_pieces (number of pieces the string was split into)
*/
int split(string myStr, char seperator, string arr[], int arr_size){

    int previous_index = 0;
    int counter = 0;
    int num_pieces = 0;

    

    for(int i = 0; i < myStr.length(); i++){

        if(num_pieces + 1 > arr_size){
            return -1;
        }

        string temp;

        if(i == myStr.length() - 1){

            // if at end of string, take last string (no comma at the end)
            temp = myStr.substr(previous_index, i - previous_index + 1);
            arr[counter] = temp;
            num_pieces++;
            
            

        }else if(myStr[i] == seperator){

            if(previous_index == 0){
                // first substr
                temp = myStr.substr(previous_index, i - previous_index);
                previous_index = i + 1;
                arr[counter] = temp;
                counter++;
                num_pieces++;

            }else{
                // middle substr's sandwiched by commas
                temp = myStr.substr(previous_index , i - previous_index);
                previous_index = i + 1;
                arr[counter] = temp;
                counter++;
                num_pieces++;
            }
            
        }


    }



    return num_pieces;
}

/*
This function takes in a string and returns it in its uppercase form
Parameters - string input (string w/ possible lowercase letters)
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




// FUNCTIONS


/*
This function reads .txt file of songs and stores Song objects in array with size songArrSize
Parameters: string fileName (name of .txt file), Song arr[] (array of Song objects), int numSongsStored (Song objects already in the array), int songArrSize (size of array)
Return: int counter (total number of Song objects stored in Song arr[])
*/
int readSongs(string fileName, Song arr[], int numSongsStored, int songArrSize){

    // input validation for numSongsStored and songArrSize
    if(numSongsStored < 0 || songArrSize < 0){
        return 0;
    }

    // if numSongsStored = size of song arrary, return -2
    if(numSongsStored == songArrSize){
        return -2;
    }



    ifstream input;
    input.open(fileName);

    if(input.is_open() ){

        input.seekg(0, ios::end);
        unsigned long long last_pos = input.tellg();

        if(last_pos != 0){

            string line;
            int counter = numSongsStored;
            input.seekg(0, ios::beg);

            while(getline(input,line) && counter != songArrSize){ // run loop while there are still lines and the array hasn't reached max capacity

                // temporary array for title, artist, and genre
                string temp[3];

                // if line isn't empty, split line and store as Song in array
                if(line != ""){

                    split(line,',', temp,3);

                    arr[counter].setTitle(temp[0]);
                    arr[counter].setArtist(temp[1]);
                    arr[counter].setGenre(temp[2]);

                    counter++;

                }else{
                    continue;
                }


            }


            return counter;

        }else{
            // empty file
            return -1;
        }

    }else{
        return -1;
    }

    


}


/*
This function prints all the Song objects in a Song array
Parameters: Song arr[] (array of Song objects), int numSongs (number of Song objects stored in Song arr[])
Return: void (no return value)... it just prints to terminal
*/
void printAllSongs(Song arr[], int numSongs){

    if(numSongs <= 0){ // no songs in arr
        cout << "No songs are stored" << endl;
    }else{
        cout << "Here is a list of songs" << endl;
        // print all songs in arr that are not empty
        for(int i = 0; i < numSongs; i++){
            string title = arr[i].getTitle();
            string artist = arr[i].getArtist();

            cout << title << " is by " << artist << endl;
        }
    }
}


/*
This function goes through array of Song objects and counts how many match the given genre
Parameters- strin genre (the genre the function searches through), Song arr[] (array of Songs searched through), int numSongsStored (number of Song objects in array)
Return- int genreCount (number of Songs with genre that matches the given genre)
*/
int countGenre(string genre, Song arr[], int numSongsStored){

    int genreCount = 0;
    genre = toUpper(genre); // uppercase for comparison purposes

    // go through Song arr[] up until number of Songs stored
    for(int i = 0; i < numSongsStored; i++){
        string genreAtI = toUpper(arr[i].getGenre()); // look at genre of the Song at i in arr[]

        // if this genre = the genre we are looking for, add one to genreCount
        if(genreAtI == genre){
            genreCount++;
        }

    }

    return genreCount;
}

/*
This function takes in a Song array and returns the count of the genre that appears most in the array
Parameters- Song arr[] (the array of Songs that's looped through), int numSongsStored (number of Songs stored in Song array)
Return- maxCount (the count of the genre that appears most in the Song array)
*/
int frequentGenreSongs(Song arr[], int numSongsStored){

    if(numSongsStored <= 0){
       return 0; 
    }


    string uniqueGenres[numSongsStored];
    int genreCounts[numSongsStored];
    int numUniqueGenres = 0;

    int maxCount = 0;


    // go through each Song object in arr[] to collect unique genres and corresponding counts
    for(int i = 0; i < numSongsStored; i++){

        string currentGenre = toUpper(arr[i].getGenre()); // uppercase genre at arr[i] for comparison purposes

        bool alreadyStored = false; // assume the genre isn't already stored in uniqueGenres[]

        // if the currentGenre matches a genre in the uniqueGenres[], then it is not unique... so set alreadyStored to true
        for(int i = 0; i < numSongsStored; i++){
            if(currentGenre == uniqueGenres[i]){
                alreadyStored = true;
            }
        }


        // if the currentGenre is alreadyStored, move on to next Song object
        if(alreadyStored){
            
            continue;

        }else{

            // otherwise, add currentGenre to uniqueGenres array
            uniqueGenres[numUniqueGenres] = currentGenre;

            // call countGenre to see how many times the new unique genre is seen in the Song array
            int currentGenreCount = countGenre(currentGenre, arr, numSongsStored);

            // add the count of the current genre into genreCounts array
            genreCounts[numUniqueGenres] = currentGenreCount;

            // signify that we added a new unique genre by adding one to numUniqueGenres
            numUniqueGenres++;

        }
    }

    // get the maximum genre count
    for(int j = 0; j < numUniqueGenres; j++){
        maxCount = max(maxCount, genreCounts[j]);
    }

    
    // another way to get maxCount:

    // for(int j = 0; j < numUniqueGenres; j++){
    //     if(maxCount < genreCounts[j]){
    //         maxCount = genreCounts[j];
    //     }
    // }

    return maxCount;
}


/*
This function adds new listener to listeners array
Parameters- string listenerName (name of new listener), listeners[] (array of Listener objects), int numSongs, int numListenersStored, int listenersArrSize
Return- int numListenerStored (number of listeners stored in listeners[] after function is executed OR error #)
*/
int addListener(string listenerName, Listener listeners[],int numSongs,int numListenersStored, int listenersArrSize){

    // input validation for numListenersStored and numSongs
    if(numListenersStored < 0 || numSongs < 0){
        return 0;
    }

    // numListenersStored is greater than listenersArrSize
    if(numListenersStored >= listenersArrSize){
        return -1;
    }

    // listenerName is empty
    if(listenerName == ""){
        return -3;
    }

    // check if name is already in array
    string comparisonName = toUpper(listenerName);
    

    // iterate through listeners[] to check if listener is already in array
    for(int i = 0; i < numListenersStored; i++){
        string currentName = toUpper(listeners[i].getListenerName());
        
        
        if(currentName == comparisonName){
            
            return -2;
        }
    }

    // add listener to listeners[]
    listeners[numListenersStored].setListenerName(listenerName);
    numListenersStored++;

    return numListenersStored;

}



/*
This function takes in a file of listeners and stored it into the listeners array up until it reaches its max size, then returns number of listeners stored in array post-function
Parameters- string fileName, listeners[] (array of Listener objects), int numListenersStored (current # of listeners in array), int listenerArrSize (size of listeners[]), int maxCol (should be 51)
Return- int numListeners (number of listeners stored in listeners[] after function is performed OR error #)
*/
int readListenerInfo(string fileName, Listener listeners[], int numListenersStored, int listenerArrSize, int maxCol=51){

    // input validation for numListenersStored, listenerArrSize, and maxCol
    if(numListenersStored < 0 || listenerArrSize < 0 || maxCol < 0){
        return 0; 
    }

    // if number of listeners stored is greater than listenerArrSize, then return -2
    if(numListenersStored >= listenerArrSize){
        return -2;
    }
    
    
    int numListeners = numListenersStored;

    ifstream input;

    input.open(fileName);

    // if able to open file, continue program
    if(input.is_open()){

        

        input.seekg(0, ios::end);
        unsigned long long last_pos = input.tellg();

        

        // if file isn't empty, continue program
        if(last_pos != 0){

            input.seekg(0, ios::beg);

            string line;

            // while there's still a line in file and numListeners hasn't reached listenerArrSize, add listener to listeners array
            while(getline(input,line) && numListeners < listenerArrSize){

                // if line is empty, move on to next line
                if(line == ""){
                    continue;
                }

                // split line and store in temp array
                string temp[maxCol];
                int numColumns = split(line, ',', temp, maxCol);

                // set listener name to first element of temp 
                listeners[numListeners].setListenerName(temp[0]);

                // iterate through rest of temp[] to set fill playCount[] for listener
                for(int i = 1; i < numColumns; i++){
                    int currentPlayCount = stoi(temp[i]);
                    listeners[numListeners].setPlayCountAt((i - 1),currentPlayCount);
                }
                // the play counts after numColumns should be zero b/c Listener() sets all play counts to zero


                numListeners++;

            }


        }else{
            // file is empty
            return 0;
        }


    }else{
        // file unable to be opened
        return -1;
    }


    return numListeners;


}


/*
This function gets the number of times a listener has listened to a given song
Parameters- string listenerName, string songName, listeners[] (array of Listener objects), songs[] (array of Song objects), int numListenersStored, int numSongsStored
Return- int songPlayCount (number of times the listener listened to the given song)
*/
int getSongPlayCount(string listenerName, string songName, Listener listeners[], Song songs[], int numListenersStored, int numSongsStored){

    // input validation for numListenersStored and numSongsStored
    if(numListenersStored < 0 || numSongsStored < 0){
        return 0;
    }
    
    // uppercase listenerName and songName for comparison reasons
    listenerName = toUpper(listenerName);
    songName = toUpper(songName);

    // assum songs and listener are not in listeners and songs arrays
    bool songFound = false;
    bool listenerFound = false;

    // go through each song in songs[] to see if any have title that matches songName
    int songIndex;
    for(int i = 0; i < numSongsStored; i++){
        string currentSong = toUpper(songs[i].getTitle());

        // if the song is stored in songs array, then update that the song was found and save the song index
        if(currentSong == songName){
            songFound = true;
            songIndex = i;
            break;
        }
    }

    // go through each listener in listeners[] to see if any listener has name that matches listenerName
    int listenerIndex;
    for(int i = 0; i < numListenersStored; i++){
        string currentListener = toUpper(listeners[i].getListenerName());

        // if listener is in listeners[], update that listener was found and save their index
        if(currentListener == listenerName){
            listenerFound = true;
            listenerIndex = i;
            break;
        }
    }


    if(!songFound && listenerFound){
        // song not found but listener found
        return -1;
    }else if(songFound && !listenerFound){
        // song found but listener not found
        return -2;
    }else if(!songFound && !listenerFound){
        // both song and listener not found
        return -3;
    }else{
        // both song and listener were found

        // get the play count of listener for song
        int songPlayCount = listeners[listenerIndex].getPlayCountAt(songIndex);
        return songPlayCount;
    }



}


/*
This function gets the number of unique songs and the average number of listens of a given listener
Parameters- string listenerName, listeners[] (array of Listener objects), int numListenersStored (Listeners stored in listeners), int numSongs (Songs stored in songs)
Return- integer based on success or error of function... returns 1 if the function performed as expected
*/
int getListenerStats(string listenerName, Listener listeners[], int numListenersStored, int numSongs){

    // uppercase listenerName for comparison purposes
    string name = toUpper(listenerName);

    // assume listener is not in listeners array
    bool listenerFound = false;
    int listenerIndex;

    // iterate through listeners[] to see if any Listeners have name as listenerName
    for(int i = 0; i < numListenersStored; i++){
        string currentListener = toUpper(listeners[i].getListenerName());
        if(currentListener == name){
            listenerFound = true;
            listenerIndex = i; // save index of listener
            break;
        }
    }

    // if listener is found, get listener stats
    if(listenerFound){

        Listener listener = listeners[listenerIndex];
        int totalPlayCount = listener.totalPlayCount();

        
        if(totalPlayCount == 0){
            // listener hasn't listened to any songs
            cout << listenerName << " has not listened to any songs."<< endl;
            return 0;
        }else{

            // listener has listened to some songs
            cout << listenerName << " listened to " << listener.getNumUniqueSongs() << " songs." << endl;
            double averageListens = (double)totalPlayCount / (double)listener.getNumUniqueSongs();
            cout << listenerName << "'s average number of listens was " << setprecision(2) << fixed << averageListens << endl;

            return 1;
        }
    }else{
        // name does not match any of the Listener's listenerName
        cout << listenerName << " does not exist." << endl;
        return -3;
    }



}




/*
This function runs a menu that has 9 valid options for interacting with the Song and Listener objects
Parameters- none
Return- void
*/
void interactive(){

    bool continueProgram = true;

    Song songArr[50];
    const int SONG_ARR_SIZE = 50;
    int numSongsStored = 0;

    Listener listenerArr[100];
    const int LISTENERS_ARR_SIZE = 100;
    int numListenersStored = 0;

    do{

        

        // print menu
        cout << "Select a numerical option:\n======Main Menu=====\n1. Read songs from file\n2. Print all songs\n3. Song-count by genre\n4. Songs from most common genre\n5. Add listener\n6. Read listens from file\n7. Get number of listens by a listener\n8. Get listener statistics\n9. Quit"   << endl;
        // get user input
        int choice;
        cin >> choice;

        

        switch(choice){
            case 1: // Read songs from file
                {

                    // get song file
                    string songFileName;
                    cout << "Enter a song file name:"<< endl;
                    cin >> songFileName;

                    int numSongs = readSongs(songFileName,songArr,numSongsStored,SONG_ARR_SIZE);


                    if(numSongs == -1){
                        cout << "No songs saved to the database." << endl;
                    }else if(numSongs == -2){
                        cout << "Database is already full. No songs were added." << endl;
                    }else if(numSongs == SONG_ARR_SIZE){
                        cout << "Total songs in the database: " << numSongs << endl;
                        cout << "Database is full. Some songs may have not been added." << endl;
                        numSongsStored = numSongs;
                    }else{
                        cout << "Total songs in the database: " << numSongs << endl;
                        numSongsStored = numSongs;
                    }



                    break; 
                }
            case 2: // Print all songs
                {

                    printAllSongs(songArr,numSongsStored);

                    break;
                }
                
            case 3: // Song-count by genre
                {
                    // get genre
                    string genre;
                    cout << "Enter the genre:" << endl;
                    cin >> genre;

                    int count = countGenre(genre, songArr, numSongsStored);

                    cout << "Total " << genre << " songs in the database: " << count << endl;


                    break;
                }
            case 4: // Songs from most common genre
                {

                    int maxCount = frequentGenreSongs(songArr, numSongsStored);

                    cout << "Number of songs in most common Genre: " << maxCount << endl;


                    break;
                }
            case 5: // Add listener
                {
                    string listenerName;
                    cout << "Enter a listener name: " ;
                    cin.ignore();
                    getline(cin,listenerName);

                    cout << "\n" ;

                    int result = addListener(listenerName, listenerArr,numSongsStored,numListenersStored, LISTENERS_ARR_SIZE);

                    if(result == -1){
                        cout << "Database is already full. Listener cannot be added." << endl;
                    }else if(result == -2){
                        cout << "Listener already exists." << endl;
                    }else if(result == -3){
                        cout << "The listenerName is empty." << endl;
                    }else{
                        cout << "Welcome, " << listenerName << "!" << endl;
                        numListenersStored = result;
                    }

                    break;
                }
            case 6: // Read listeners from file
                {

                    string listenerFileName;
                    cout << "Enter the listener info file name: " ;
                    cin >> listenerFileName;
                    
                    cout << "\n";

                    int numListeners = readListenerInfo(listenerFileName, listenerArr, numListenersStored, LISTENERS_ARR_SIZE, 51);

                    if(numListeners == -1){
                        cout << "Nothing saved to the database." << endl;
                    }else if(numListeners == -2){
                        cout << "Database is already full. No listeners were added." << endl;
                    }else{
                        cout << "Total listeners in the database: " << numListeners << endl;
                        numListenersStored = numListeners;
                        if(numListenersStored == LISTENERS_ARR_SIZE){
                            cout << "Database is full. Some listeners may have not been added." << endl;
                        }
                    }

                    break;
                }
            case 7: // Get song listens by a listener
                {
                    

                    string listenerName;
                    string songName;

                    // get listener name
                    cout << "Enter a listener name: " ;
                    cin >> listenerName;
                    cin.ignore();

                    cout << "\n";

                    // get song name
                    cout << "Enter a song name: " ;
                    getline(cin,songName);

                    cout << "\n";


                    int playCount = getSongPlayCount(listenerName,songName, listenerArr, songArr, LISTENERS_ARR_SIZE, SONG_ARR_SIZE);

                    if(playCount == -1){
                        cout << songName << " does not exist." << endl;
                    }else if(playCount == -2){
                        cout << listenerName << " does not exist." << endl;
                    }else if(playCount == -3){
                        cout << listenerName << " and " << songName << " do not exist." << endl;
                    }else{
                        cout << listenerName << " has listened to " << songName << " " << playCount << " times." << endl;
                    }


                    break;
                }
            case 8: // Get listener statistics
                {
                    // get listener name
                    string listenerName;
                    cout << "Enter a listener name:" << endl;
                    cin >> listenerName;

                    getListenerStats(listenerName,listenerArr,numListenersStored,numSongsStored);

                
                    break;
                }
            case 9: // Quit

                cout << "Good bye!" << endl;
                continueProgram = false;
                break;
                
            default: // Invalid choice
                {
                    cout << "Invalid input." << endl;
                    break;
                }
        }
    }while(continueProgram);
}



int main(){

    interactive();

    return 0;
}
