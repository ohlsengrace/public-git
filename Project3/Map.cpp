//Project 3
//Grace Ohlsen and Justin Jamrowski
#include "Map.h"
#include "Player.h"

using namespace std; 

Map::Map()
{
    resetMap();
}

// resets player position, count values, and initializes values in position arrays to -1
void Map::resetMap() {
    playerPosition[0] = 0; 
    playerPosition[1] = 0;

    gameRoomPosition[0] = -1;
    gameRoomPosition[1] = -1;

    lobbyPosition[0] = -1;
    lobbyPosition[1] = -1;

    superComputerPosition[0] = -1;
    superComputerPosition[1] = -1;

    cheatCodePosition[0] = -1;
    cheatCodePosition[1] = -1;

    virus_count = 0;
    game_room_on_map = false;
    lobby_on_map = false;
    super_computer_on_map = false;
    cheat_code_on_map = false;


    for (int i = 0; i < num_viruses; i++) {
        virusPositions[i][0] = -1;
        virusPositions[i][1] = -1;
    }

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            mapData[i][j] = '-';
        }
    }
}

// return player's row position
int Map::getPlayerRowPosition() {
    return playerPosition[0];
}

// return player's column position
int Map::getPlayerColPosition() {
    return playerPosition[1];
}

// return number of viruses on map
int Map::getVirusCount() {
    return virus_count;
}

// set player's row position to parameter row
void Map::setPlayerRowPosition(int row) {
    playerPosition[0] = row;
}

// set player's column position to parameter row
void Map::setPlayerColPosition(int col) {
    playerPosition[1] = col;
}

// sets the number of viruses on the map
void Map::setVirusCount(int count) {
    virus_count = count;
}

/* add Virus to map
 * Parameters: where to spawn Virus -- row (int), col (int)
 * Return: (bool) false if no more space in virusPositions array
 *                      or if (row, col) is an invalid position
 *                      or if (row, col) is already populated; else true
 */
bool Map::spawnVirus(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }

    if (virus_count >= num_viruses) {
        return false;
    }

    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }

    if (virusPositions[virus_count][0] == -1 && virusPositions[virus_count][1] == -1) {
        virusPositions[virus_count][0] = row;
        virusPositions[virus_count][1] = col;
        mapData[row][col] = 'V';
        virus_count++;
        return true;
    }

    return false;
}



/* add GameRoom to map
 * Parameters: where to spawn Game Room -- row (int), col (int)
 * Return: (bool) false if (row, col) is an invalid location
 *                      or if (row, col) is already populated
 *                      or if there is a game room already on the map; else true
 */
bool Map::spawnGameRoom(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }

    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }

    if (game_room_on_map) {
        return false;
    }

    if (gameRoomPosition[0] == -1 && gameRoomPosition[1] == -1) {
        gameRoomPosition[0] = row;
        gameRoomPosition[1] = col;
        mapData[row][col] = 'G';
        game_room_on_map = true;
        return true;
    }

    return false;
}

// return true if x, y position has a game room there
bool Map::isGameRoomLocation(){
    return gameRoomPosition[0] == playerPosition[0] && gameRoomPosition[1] == playerPosition[1];
}



/* add Lobby to map
 * Parameters: where to spawn Lobby -- row (int), col (int)
 * Return: (bool) false if (row, col) is an invalid location
 *                      or if (row, col) is already populated
 *                      or if there is a lobby already on the map; else true
 */
bool Map::spawnLobby(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }

    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }

    if (lobby_on_map) {
        return false;
    }

    if (lobbyPosition[0] == -1 && lobbyPosition[1] == -1) {
        lobbyPosition[0] = row;
        lobbyPosition[1] = col;
        mapData[row][col] = 'L';
        lobby_on_map = true;
        return true;
    }

    return false;
}

// return true if x, y position has a lobby there
bool Map::isLobbyLocation(){
    return lobbyPosition[0] == playerPosition[0] && lobbyPosition[1] == playerPosition[1];
}




/* add SuperComputer to map
 * Parameters: where to spawn SuperComputer -- row (int), col (int)
 * Return: (bool) false if (row, col) is an invalid location
 *                      or if (row, col) is already populated
 *                      or if there is a game room already on the map; else true
 */
bool Map::spawnSuperComputer(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }

    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }

    if (super_computer_on_map) {
        return false;
    }

    if (superComputerPosition[0] == -1 && superComputerPosition[1] == -1) {
        superComputerPosition[0] = row;
        superComputerPosition[1] = col;
        mapData[row][col] = 'S';
        super_computer_on_map = true;
        return true;
    }

    return false;
}

// return true if x, y position has a super computer there
bool Map::isSuperComputerLocation(){
    return superComputerPosition[0] == playerPosition[0] && superComputerPosition[1] == playerPosition[1];
}


/* add CheatCode to map
 * Parameters: where to spawn Cheat Code -- row (int), col (int)
 * Return: (bool) false if (row, col) is an invalid location
 *                      or if (row, col) is already populated
 *                      or if there is a cheat code already on the map; else true
 */
bool Map::spawnCheatCode(int row, int col) {
    // out of map bounds
    if (!(row >= 0 && row < num_rows && col >= 0 && col < num_cols)) {
        return false;
    }

    // location must be blank to spawn
    if (mapData[row][col] != '-') {
        return false;
    }

    if (cheat_code_on_map) {
        return false;
    }

    if (cheatCodePosition[0] == -1 && cheatCodePosition[1] == -1) {
        cheatCodePosition[0] = row;
        cheatCodePosition[1] = col;
        mapData[row][col] = 'C';
        cheat_code_on_map = true;
        return true;
    }

    return false;
}

// return true if x, y position has a game room there
bool Map::isCheatCodeLocation(){
    return cheatCodePosition[0] == playerPosition[0] && cheatCodePosition[1] == playerPosition[1];
}


// return true if x, y position has a virus there
bool Map::isVirusLocation() {
    for(int i = 0; i < num_viruses; i++){
        if(virusPositions[i][0] == playerPosition[0] && virusPositions[i][1] == playerPosition[1]){
            return true; 
        }
    }
    return false; 
}

/*
 * This function prints a menu of valid moves based on playerPosition
 * Parameters: none
 * Return: nothing (void)
 */
void Map::displayMoves(){
    if(!(playerPosition[0] == 0)){
        cout << "w (Up)" << endl;
    }
    if(!(playerPosition[0] == (num_rows - 1))){
        cout << "s (Down)" << endl; 
    }
    if(!(playerPosition[1] == 0)){
        cout << "a (Left)" << endl; 
    }
    if(!(playerPosition[1] == (num_cols - 1))){
        cout << "d (Right)" << endl; 
    }
    cout << "i (View inventory)" << endl;
}

/*
 * This function takes in user input
 * and updates playerPosition on the map.
 * Parameters: move (char) -- 'w' (up), 'a' (left), 's' (down), 'd' (right)
 * Return: (bool) if move is valid, then true, else false
 */
bool Map::executeMove(char move, Player player){
    // if user inputs w, move up if it is an allowed move
    if(!(playerPosition[0] == 0) && (tolower(move) == 'w')){
        playerPosition[0] -= 1;
        return true; 
    }
    // if user inputs s, move down if it is an allowed move
    else if(!(playerPosition[0] == (num_rows - 1))&& (tolower(move) == 's')){
        playerPosition[0] += 1;
        return true; 
    }
    // if user inputs a, move left if it is an allowed move
    else if(!(playerPosition[1] == 0)&& (tolower(move) == 'a')){
        playerPosition[1] -= 1;
        return true; 
    }
    // if user inputs d, move right if it is an allowed move
    else if(!(playerPosition[1] == (num_cols - 1))&& (tolower(move) == 'd')){
        playerPosition[1] += 1;
        return true; 
    }
    // if user inputs i, print inventory
    else if(tolower(move) == 'i'){
        cout << "Inventory: " ;
        player.printInventory();
        return true;
    }
    else{
        cout << "Invalid Move" << endl; 
        return false; 
    }
}

/*
 * This function prints a 2D map in the terminal.
 * Parameters: none
 * Return: nothing (void)
 */
void Map::displayMap() {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (playerPosition[0] == i && playerPosition[1] == j) {
                cout << "x";
            } else if (mapData[i][j] == 'V') {  // don't show virus on the map
                cout << "-";
            }
            else {
                cout << mapData[i][j];
            }
        }
        cout << endl;
    }
}

// returns true if there is already a Game Room on the map
bool Map::isGameRoomOnMap() {
    return game_room_on_map;
}

// returns true if there is already a Lobby on the map
bool Map::isLobbyOnMap(){
    return lobby_on_map;
}

// returns true if there is already a SuperComputer on the map
bool Map::isSuperComputerOnMap(){
    return super_computer_on_map;
}

// returns true if there is already a cheat code on the map
bool Map::isCheatCodeOnMap(){
    return cheat_code_on_map;
}

