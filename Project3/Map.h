//Project 3
//Grace Ohlsen and Justin Jamrowski
#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <iostream>
#include <ctype.h>
#include "Player.h"

using namespace std; 

class Map
{
     private:
          static const int num_rows = 5;
          static const int num_cols = 9;
          static const int num_viruses = 3;

          int playerPosition[2];
          int gameRoomPosition[2];
          int lobbyPosition[2];
          int superComputerPosition[2];
          int cheatCodePosition[2];
          int virusPositions[num_viruses][2];
          char mapData[num_rows][num_cols];

          int virus_count;
          bool game_room_on_map;
          bool lobby_on_map;
          bool super_computer_on_map;
          bool cheat_code_on_map;

     public :
          Map();

          void resetMap();

          // getters
          int getPlayerRowPosition();
          int getPlayerColPosition();
          int getVirusCount();

          // setters
          void setPlayerRowPosition(int);
          void setPlayerColPosition(int);
          void setVirusCount(int);

          bool spawnGameRoom(int, int);
          bool spawnLobby(int,int);
          bool spawnSuperComputer(int,int);
          bool spawnCheatCode(int,int);
          bool spawnVirus(int, int);

          void displayMap();
          void displayMoves();  
          bool executeMove(char,Player);

          bool isGameRoomLocation();
          bool isLobbyLocation();
          bool isSuperComputerLocation();
          bool isCheatCodeLocation();
          bool isVirusLocation();

          bool isGameRoomOnMap();
          bool isLobbyOnMap();
          bool isSuperComputerOnMap();
          bool isCheatCodeOnMap();
};
 
#endif