#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace state;

State::State():cursor(10,10,2){ // call a specific constructor
    round=1;
    endGame=false;
    curPlayerID=1;
    nbOfPlayers=1;

}
State::~State(){}

//getters
void State::initPlayers(){
    // for now 2 Players
    unique_ptr<Player> ptrPlayer1(new Player(1));
    unique_ptr<Player> ptrPlayer2(new Player(1));
    listPlayers.push_back(move(ptrPlayer1));

}

  std::vector<std::vector<std::unique_ptr<MapCell>>>& State::getMap (){
      return map;
  }

  void State::initMapCell(){

    int nbWidthTile= 26;
    int nbHeightTile=24;

    std::ifstream file("res/textures/map.csv",ios::in);
    std::string content, line, tile_code;
    int map_tile_code[nbWidthTile*nbHeightTile]; // width*height

        // Read the file by storing all the data into one string -> content

    if (file){
        while (std::getline(file,line)){
            line = line + ",";
            content = content + line;
 
        }
        file.close();
    }
     std::stringstream contentStream(content); 
    int i=0;
    
    while(std::getline(contentStream, tile_code, ',')){ // ',' is a delimiter of a line
        // Convert string tile codes into integers and store it in an array
        map_tile_code[i] = (int) std::stoi(tile_code);
        i++;
    }
    

    int k=0;
    for (int i=0; i<nbHeightTile;i++){
        std::vector<std::unique_ptr<MapCell>> mapLine;
        for(int j=0;j<nbWidthTile;j++){
            
            if(map_tile_code[k]<9){ // In the map tileset only the first nine tiles are not obstacles
                std::unique_ptr<MapCell> ptr_space (new SpaceMapTiles(Sand,j,i,map_tile_code[k]));
                mapLine.push_back(move(ptr_space)); 

            }else{

                std::unique_ptr<MapCell> ptr_obstacle(new ObstacleMapTiles(Rock,j,i,map_tile_code[k]));
                mapLine.push_back(move(ptr_obstacle));
            }
            k++;
        }
        map.push_back(move(mapLine));
    }

}

void State::initCharacters(){
   
    //init Player 1 Characters
    unique_ptr<Character> ptrCrook(new Character(CROOK,"CROOK",,10,24));
    unique_ptr<Character> ptrKnight(new Character(KNIGHT,"KNIGHT",10,10,24));
    unique_ptr<Character> ptrDwarf(new Character(DWARF,"DWARF",10,10,24));
    listPlayers[0]->getListCharacters().push_back(move(ptrCrook));
    listPlayers[0]->getListCharacters().push_back(move(ptrKnight));
    listPlayers[0]->getListCharacters().push_back(move(ptrDwarf));

    //init Player 2 Characters
    unique_ptr<Character> ptrCrook(new Character(CROOK,"CROOK",10,10,24));
    unique_ptr<Character> ptrKnight(new Character(KNIGHT,"KNIGHT",10,10,24));
    unique_ptr<Character> ptrDwarf(new Character(DWARF,"DWARF",10,10,24));
    listPlayers[1]->getListCharacters().push_back(move(ptrCrook));
    listPlayers[1]->getListCharacters().push_back(move(ptrKnight));
    listPlayers[1]->getListCharacters().push_back(move(ptrDwarf));

/*
    // set Index for Characets for each Players
    for(int j=0; j<listPlayers.size();j++){
        for (int i=0; i<listPlayers[0]->getListCharacters().size();i++)
            listPlayers[j]->getListCharacters()[i]->setIndex(i);   
    }
*/
}

void State::deletePlayer(Player& player){
    for(unsigned int i=0; i<listPlayers.size(); i++){
        if(listPlayers[i]->getId() == player.getId() ){
            listPlayers.erase(listPlayers.begin() + i);
        }
    }
}


// A character has been selected
bool State::ifStelected(){
    for(unsigned int i=0;i<listPlayers.size();i++){
        for(unsigned int j=0;j<listPlayers[i]->getListCharacters().size();j++){
            if(listPlayers[i]->getListCharacters()[j]->getStatus() == SELECTED)
                return true;
        }
    }
    return false;
}

// getters and setters
bool State::getEndGame(){ return endGame;}
int State::getRound(){ return round;}
int State::getCurPlayerID(){ return curPlayerID;}
int State::getNbOfPlayers(){ return nbOfPlayers;}
Cursor& State::getCursor(){ return cursor;}
CurActionID State::getCurAction(){return curAction;}

void State::setRound(int newRound){ round= newRound;}
void State::setEndGame(bool res){ endGame=res;}
void State::setCurPlayerID(int newPlayer){curPlayerID=newPlayer;}
void State::setCurAction(CurActionID newAction){curAction=newAction;}

