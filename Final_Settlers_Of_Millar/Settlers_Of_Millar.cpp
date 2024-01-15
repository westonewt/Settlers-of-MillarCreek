#include "win&mac-formatting.h"
#include "typesafe.h"
#include "Settlers_Of_Millar.h"
#include <iomanip>
#include <cstdlib>
#include <algorithm>

void printBoard(hexTile board[], const int AMOUNT_OF_TILES);
void showSettlementSelection(hexTile selectionBoard[], hexTile board[], const int AMOUNT_OF_TILES);
void showRoadSelection(hexTile board[], const int AMOUNT_OF_TILES, structure selectedSettlement);
void showHexagonSelection(hexTile inputHex);
void generateBoard(hexTile board[], const int AMOUNT_OF_TILES);
void setUpGame(hexTile board[], player players[], int &amountOfPlayers, const int MAX_AMOUNT_OF_PLAYERS, const int AMOUNT_OF_TILES, const int SPACING);
void gamePlay (hexTile board[], player players[], int amountOfPlayers, const int MAX_AMOUNT_OF_PLAYERS, const int AMOUNT_OF_TILES, const int SPACING);
void help();
void clearMenu(const int SPACING);
void clearGameMenu(const int SPACING);
void build(hexTile board[], player currentPlayer, const int AMOUNT_OF_TILES, const int SPACING);
void buildRoad(hexTile board[], player currentPlayer, const int AMOUNT_OF_TILES, const int SPACING);
void buildSettlement(hexTile board[], player currentPlayer, const int AMOUNT_OF_TILES, const int SPACING);
void buildCity(hexTile board[], player currentPlayer, const int AMOUNT_OF_TILES, const int SPACING);
void trade(player players[], int amountOfPlayers, int currentPlayer, const int SPACING);
bool addStructure(hexTile board[], const int AMOUNT_OF_TILES, int boardSelecion, char corner, structure &settlement);
bool moveRobber(hexTile board[], player players[], int currentPlayer, const int amountOfPlayers, const int AMOUNT_OF_TILES, const int SPACING, int &robbedSelection);
int diceRoll();

int main(){
  const int X_MAX   = 150;
  const int Y_MAX   = 45;
  const int SPACING = 31;
  const int AMOUNT_OF_TILES  = 19;
  const int AMOUNT_OF_MENUS  = 3;
  const int MAX_AMOUNT_OF_PLAYERS = 4;
  const string MENU[AMOUNT_OF_MENUS] = {"Start new game", "help", "quit"};
  player players[MAX_AMOUNT_OF_PLAYERS];
  hexTile board[AMOUNT_OF_TILES];
  int neighbors[6];
  int amountOfPlayers = 0;
  int selection   = 0;
  int menu_width  = 0;
  int menu_height = 0;
  bool isDone = false;

  for(int i = 0; i < 3; i++){
    board[i].assignOrigin(8 + SPACING, 9 + 9 * i - i);
    board[i].assignIdentifier(i);
  }

  for(int i = 0; i < 4; i++){
    board[i + 3].assignOrigin(26 + SPACING, 5 + 9 * i - i);
    board[i + 3].assignIdentifier(i + 3);
  }

  for(int i = 0; i < 5; i++){
    board[i + 7].assignOrigin(44 + SPACING, 1 + 9 * i - i);
    board[i + 7].assignIdentifier(i + 7);
  }

  for(int i = 0; i < 4; i++){
    board[i + 12].assignOrigin(62 + SPACING, 5 + 9 * i - i);
    board[i + 12].assignIdentifier(i + 12);
  }

  for(int i = 0; i < 3; i++){
    board[i + 16].assignOrigin(80 + SPACING, 9 + 9 * i - i);
    board[i + 16].assignIdentifier(i + 16);
  }

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    board[i].findNeighbors(board);
  }

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    board[i].connectStructures();
  }

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    board[i].correctRoadDirections();
  }

  cout << "Please enter full screen\n\nPress enter to continue...";
  enterKey();
  clear();
  printBoard(board, AMOUNT_OF_TILES);

  do{
    clearMenu(SPACING);
    printMenu(MENU, AMOUNT_OF_MENUS);
    setCursor(12, 5);
    selection = getInt("selection");
    selection = checkRange(selection, AMOUNT_OF_MENUS, 1, "selection");

    switch(selection){
      case 1:
        setUpGame(board, players, amountOfPlayers, MAX_AMOUNT_OF_PLAYERS, AMOUNT_OF_TILES, SPACING);
        gamePlay(board, players, amountOfPlayers, MAX_AMOUNT_OF_PLAYERS, AMOUNT_OF_TILES, SPACING);
      break;
      case 2:
        clear();
        help();
        clear();
        printBoard(board, AMOUNT_OF_TILES);
      break;
      case 3:
        isDone = true;
      break;
    }
  }while(!isDone);

  setCursor(1, 37);
  return 0;
}

void printBoard(hexTile board[], const int AMOUNT_OF_TILES){
  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    board[i].print();
  }
}

void showSettlementSelection(hexTile selectionBoard[], hexTile board[], const int AMOUNT_OF_TILES){
  const char alphabet[19] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's'};
  // replace fill settlements with a new structure. Then add if else chain to determine if structure is already ocupied
  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    selectionBoard[i] = board[i];
    selectionBoard[i].fillSettlements(alphabet[i]);
    selectionBoard[i].print();
  }
}

void showRoadSelection(hexTile board[], const int AMOUNT_OF_TILES, structure selectedSettlement){
  hexTile selectionBoard[19];
  const char selectionCharacters[3] = {'a', 'b', 'c'};
  structure cacheStructure;



  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    selectionBoard[i] = board[i];
  }

  for(int i = 0; i < 3; i++){
    if(selectedSettlement.connectingStructures[i] != nullptr && selectedSettlement.connectingStructures[i] -> color == "grey"){
      cacheStructure = *selectedSettlement.connectingStructures[i];
      cacheStructure.fillChar = selectionCharacters[i];
      for(int j = 0; j < AMOUNT_OF_TILES; j++){
        selectionBoard[j].addIdenticlEdges(cacheStructure);
      }
    }
  }
  printBoard(selectionBoard, AMOUNT_OF_TILES);
}

void generateBoard(hexTile board[], const int AMOUNT_OF_TILES){
  int landscapes[19] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
  const int placementOrder[19] = {0, 1, 2, 6, 11, 15, 18, 17, 16, 12, 7, 3, 4, 5, 10 ,14, 13, 8, 9};
  const int firstBoardDigit[18]  = {5, 2, 6, 3, 8, 1, 9, 1, 1, 4, 8, 1, 9, 4, 5, 6, 3, 1};
  const int secondBoardDigit[18] = {5, 2, 6, 3, 8, 0, 9, 2, 1, 4, 8, 0, 9, 4, 5, 6, 3, 1};

  int counter = 0;
  int adjustment = 0;

  random_shuffle(begin(landscapes), end(landscapes));

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    if(landscapes[i] == 1 || landscapes[i] == 2 || landscapes[i] == 3){
      board[i].assignLandscape("dark_red", "true_black");
      board[i].assignMaterial("brick", "dark_red");
    }
    else if(landscapes[i] == 4 || landscapes[i] == 5 || landscapes[i] == 6){
      board[i].assignLandscape("black", "true_black");
      board[i].assignMaterial("ore", "black");
    }
    else if(landscapes[i] == 7 || landscapes[i] == 8 || landscapes[i] == 9 || landscapes[i] == 10){
      board[i].assignLandscape("dark_yellow", "true_black");
      board[i].assignMaterial("wheat", "dark_yellow");
    }
    else if(landscapes[i] == 11 || landscapes[i] == 12 || landscapes[i] == 13 || landscapes[i] == 14){
      board[i].assignLandscape("green", "true_black");
      board[i].assignMaterial("sheep", "green");
    }
    else if(landscapes[i] == 15 || landscapes[i] == 16 || landscapes[i] == 17 || landscapes[i] == 18){
      board[i].assignLandscape("true_black", "dark_green");
      board[i].assignMaterial("wood", "dark_green");
    }
    else if(landscapes[i] == 19){
      board[i].assignLandscape("white", "true_black");
    }
  }

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    if(board[placementOrder[i]].getColor() == "white"){
      board[placementOrder[i]].assignTileNum(7, 7);
    }
    else{
      board[placementOrder[i]].assignTileNum(firstBoardDigit[counter], secondBoardDigit[counter]);
      counter++;
    }
  }
}

void setUpGame(hexTile board[], player players[], int &amountOfPlayers, const int MAX_AMOUNT_OF_PLAYERS, const int AMOUNT_OF_TILES, const int SPACING){
  const int AMOUNT_OF_COLORS = 4;
  const int SEED_MAX = 1000000; // game contains 1 million board seeds
  const string colors[AMOUNT_OF_COLORS] = {"magenta", "blue", "cyan", "red"};
  string allowed[AMOUNT_OF_COLORS];
  hexTile boardPicker[AMOUNT_OF_TILES];
  int selection = 0;
  int counter = 0;
  int edgeInt = 0;
  char hexagon = ' ';
  char corner = ' ';
  char edge = ' ';

  hexTile hexPicker;
  structure settlement, road;

  bool hexagonFound = false;
  bool cornerFound  = false;
  bool colorValid   = false;
  string name = " ";

  for(int i = 0; i < getRandomNum(1000000); i++){
    generateBoard(board, AMOUNT_OF_TILES);
  }

  printBoard(board, AMOUNT_OF_TILES);

  clearMenu(SPACING);

  cout << "How many players are playing?\n\nAmount: ";
  amountOfPlayers = getInt("amount");
  while(!inRange(amountOfPlayers, MAX_AMOUNT_OF_PLAYERS, 2)){
    changeColor("red");
    cout << "Err: out of range";
    changeColor("white");
    cout << "\nRe-enter amount: ";
    amountOfPlayers = getInt("amount");
  }

  for(int i = 0; i < amountOfPlayers; i++){

    int counter = 0;

    clearMenu(SPACING);
    cout << "Player " << i + 1 << " enter your name: ";
    getline(cin, name);
    cout << "\nChoose your color:\n\n";

    for(int j = 0; j < AMOUNT_OF_COLORS; j++){
      colorValid = true;
      for(int k = 0; k < MAX_AMOUNT_OF_PLAYERS; k++){
        if(colors[j] == players[k].getColor()){
          colorValid = false;
          break;
        }
      }
      if(colorValid){
        changeColor(colors[j]);
        allowed[counter] = colors[j];
        counter++;
        cout << '[' << counter << "]: " << colors[j] << '\n';
      }
    }

    changeColor("white");
    cout << "\nSelection: ";
    selection = getInt("selection");

    while(!inRange(selection, counter, 1)){
      changeColor("red");
      cout << "Err: out of range";
      changeColor("white");
      cout << "\nRe-enter selection: ";
      selection = getInt("selection");
    }

    players[i].populatePlayer(name, allowed[selection - 1]);
  }

  for(int i = 0; i < amountOfPlayers; i++){

    showSettlementSelection(boardPicker, board, AMOUNT_OF_TILES);
    clearMenu(SPACING);

    changeColor("white");
    cout << players[i].getName() << "\nSelect hexagon: (a - s)\n\nHexagon: ";
    hexagon = getChar("hexagon");

    for(int j = 0; j < AMOUNT_OF_TILES; j++){
      if(hexagon == boardPicker[j].getLeftCornerChar() && board[j].valid()){
        hexagonFound = true;
        selection = j;
      }
    }

    while(!hexagonFound){
      changeColor("red");
      cout << "Err: invalid selection";
      changeColor("white");
      cout << "\nplease re-enter selection: ";
      hexagon = getChar("hexagon");

      for(int j = 0; j < AMOUNT_OF_TILES; j++){
        if(hexagon == boardPicker[j].getLeftCornerChar() && board[j].valid()){
          hexagonFound = true;
          selection = j;
        }
      }
    }

    printBoard(board, AMOUNT_OF_TILES);
    clearMenu(SPACING);
    hexPicker = boardPicker[selection];
    hexPicker.showSelection();
    setCursor(1, 1);
    changeColor("white");

    cout << players[i].getName() << "\nSelect corner: (a - f)\n\nCorner: ";
    corner = getChar("corner");

    while(!checkChar(corner, "abcdef")){
      changeColor("red");
      cout << "Err: invalid corner";
      changeColor("white");
      cout << "\nPlease re-enter corner: ";
      corner = getChar("corner");
    }

    settlement.fillChar = 'S';
    settlement.color = players[i].getColor();
    settlement.weight = 1;

    while(!addStructure(board, AMOUNT_OF_TILES, selection, corner, settlement)){
      changeColor("red");
      cout << "Err: settlment could not be placed";
      changeColor("white");
      cout << "\nCorner: ";
      corner = getChar("corner");

      while(!checkChar(corner, "abcdef")){
        changeColor("red");
        cout << "Err: invalid corner";
        changeColor("white");
        cout << "\nPlease re-enter corner: ";
        corner = getChar("corner");
      }
    }

    clearMenu(SPACING);
    showRoadSelection(board, AMOUNT_OF_TILES, settlement);
    setCursor(1, 1);
    changeColor("white");

    cout << players[i].getName() << "\nSelect edge: (a - c)\n\nEdge: ";
    edge = getChar("edge");

    while(!checkChar(edge, "abc")){
      changeColor("red");
      cout << "Err: invalid edge";
      changeColor("white");
      cout << "\nPlease re-enter edge: ";
      edge = getChar("edge");
    }

    switch(edge){
      case 'a':
        edgeInt = 0;
      break;
      case 'b':
        edgeInt = 1;
      break;
      case 'c':
        edgeInt = 2;
      break;
    }

    while(settlement.connectingStructures[edgeInt] == nullptr){
      changeColor("red");
      cout << "Err: edge does not exits";
      changeColor("white");
      cout << "\nPlease re-enter edge: ";
      edge = getChar("edge");

      while(!checkChar(edge, "abc")){
        changeColor("red");
        cout << "Err: invalid edge";
        changeColor("white");
        cout << "\nPlease re-enter edge: ";
        edge = getChar("edge");
      }

      switch(edge){
        case 'a':
          edgeInt = 0;
        break;
        case 'b':
          edgeInt = 1;
        break;
        case 'c':
          edgeInt = 2;
        break;
      }
    }

    road = *settlement.connectingStructures[edgeInt];
    road.color = players[i].getColor();

    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticlEdges(road);
    }

    players[i].incrimentPoints();
  }

  for(int i = amountOfPlayers - 1; i > -1; i--){

      hexagonFound = false;

    showSettlementSelection(boardPicker, board, AMOUNT_OF_TILES);
    clearMenu(SPACING);

    changeColor("white");
    cout << players[i].getName() << "\nSelect hexagon: (a - s)\n\nHexagon: ";
    hexagon = getChar("hexagon");

    for(int j = 0; j < AMOUNT_OF_TILES; j++){
      if(hexagon == boardPicker[j].getLeftCornerChar() && board[j].valid()){
        hexagonFound = true;
        selection = j;
      }
    }

    while(!hexagonFound){
      changeColor("red");
      cout << "Err: invalid selection";
      changeColor("white");
      cout << "\nplease re-enter selection: ";
      hexagon = getChar("hexagon");

      for(int j = 0; j < AMOUNT_OF_TILES; j++){
        if(hexagon == boardPicker[j].getLeftCornerChar() && board[j].valid()){
          hexagonFound = true;
          selection = j;
        }
      }
    }

    printBoard(board, AMOUNT_OF_TILES);
    clearMenu(SPACING);
    hexPicker = boardPicker[selection];
    hexPicker.showSelection();
    setCursor(1, 1);
    changeColor("white");

    cout << players[i].getName() << "\nSelect corner: (a - f)\n\nCorner: ";
    corner = getChar("corner");

    while(!checkChar(corner, "abcdef")){
      changeColor("red");
      cout << "Err: invalid corner";
      changeColor("white");
      cout << "\nPlease re-enter corner: ";
      corner = getChar("corner");
    }

    settlement.fillChar = 'S';
    settlement.color = players[i].getColor();
    settlement.weight = 1;

    while(!addStructure(board, AMOUNT_OF_TILES, selection, corner, settlement)){
      changeColor("red");
      cout << "Err: settlment could not be placed";
      changeColor("white");
      cout << "\nCorner: ";
      corner = getChar("corner");

      while(!checkChar(corner, "abcdef")){
        changeColor("red");
        cout << "Err: invalid corner";
        changeColor("white");
        cout << "\nPlease re-enter corner: ";
        corner = getChar("corner");
      }
    }

    for(int j = 0; j < AMOUNT_OF_TILES; j++){
      if(board[j].hasStructure(settlement) && !board[j].isDesert()){
        players[i].addCard(board[j].getMaterial());
      }
    }

    clearMenu(SPACING);
    showRoadSelection(board, AMOUNT_OF_TILES, settlement);
    setCursor(1, 1);
    changeColor("white");

    cout << players[i].getName() << "\nSelect edge: (a - c)\n\nEdge: ";
    edge = getChar("edge");

    while(!checkChar(edge, "abc")){
      changeColor("red");
      cout << "Err: invalid edge";
      changeColor("white");
      cout << "\nPlease re-enter edge: ";
      edge = getChar("edge");
    }

    switch(edge){
      case 'a':
        edgeInt = 0;
      break;
      case 'b':
        edgeInt = 1;
      break;
      case 'c':
        edgeInt = 2;
      break;
    }

    while(settlement.connectingStructures[edgeInt] == nullptr){
      changeColor("red");
      cout << "Err: edge does not exits";
      changeColor("white");
      cout << "\nPlease re-enter edge: ";
      edge = getChar("edge");

      while(!checkChar(edge, "abc")){
        changeColor("red");
        cout << "Err: invalid edge";
        changeColor("white");
        cout << "\nPlease re-enter edge: ";
        edge = getChar("edge");
      }

      switch(edge){
        case 'a':
          edgeInt = 0;
        break;
        case 'b':
          edgeInt = 1;
        break;
        case 'c':
          edgeInt = 2;
        break;
      }
    }

    road = *settlement.connectingStructures[edgeInt];
    road.color = players[i].getColor();

    for(int j = 0; j < AMOUNT_OF_TILES; j++){
      board[j].addIdenticlEdges(road);
    }
  }

  printBoard(board, AMOUNT_OF_TILES);
}

void gamePlay(hexTile board[], player players[], const int amountOfPlayers, const int MAX_AMOUNT_OF_PLAYERS, const int AMOUNT_OF_TILES, const int SPACING){

  const int AMOUNT_OF_MENUS = 6;
  const string MENU[AMOUNT_OF_MENUS] = {"Build", "Trade", "Play development card", "View Cards", "End turn", "Quit"};

  int selection;
  int roll = 0;
  int menuSelection = 0;
  int robbedSelection = 0;
  bool gameOver = false;
  bool turnDone = false;
  bool canBuild = false;
  char YorN = ' ';
  char lowering = ' ';
  const int AMOUNT_OF_ROAD_CARDS = 2;
  const int AMOUNT_OF_SETTLEMENT_CARDS = 4;
  const int AMOUNT_OF_CITY_CARDS = 5;
  const int AMOUNT_OF_CARDS_SPECIAL = 3;
  card roadRecipie[AMOUNT_OF_ROAD_CARDS];
  card settlementRecipie[AMOUNT_OF_SETTLEMENT_CARDS];
  card cityRecipie[AMOUNT_OF_CITY_CARDS];
  card developmentCardRecipie[AMOUNT_OF_CARDS_SPECIAL];

  roadRecipie[0].name = "brick";
  roadRecipie[1].name = "wood";
  settlementRecipie[0].name = "brick";
  settlementRecipie[1].name = "wood";
  settlementRecipie[2].name = "wheat";
  settlementRecipie[3].name = "sheep";
  cityRecipie[0].name = "ore";
  cityRecipie[1].name = "ore";
  cityRecipie[2].name = "ore";
  cityRecipie[3].name = "wheat";
  cityRecipie[4].name = "wheat";
  developmentCardRecipie[0].name = "ore";
  developmentCardRecipie[1].name = "sheep";
  developmentCardRecipie[2].name = "wheat";


  while(!gameOver){
    for(int i = 0; i < amountOfPlayers; i++){

      turnDone = false;

      if(gameOver){
        break;
      }

      clearMenu(SPACING);

      changeColor("white");
      cout << players[i].getName() << "'s Turn";

      clearMenu(SPACING);
      roll = diceRoll();

      cout << players[i].getName() << "'s Turn\n\nDice Roll: " << roll;

      if(roll == 7){
        for(int j = 0; j < amountOfPlayers; j++){
          if(players[j].getCardAmount() > 7){
            players[j].halfCards(SPACING);
          }
        }

        if(moveRobber(board, players, i, amountOfPlayers, AMOUNT_OF_TILES, SPACING, robbedSelection)){
          players[i].stealCard(players[robbedSelection]);
        }

      }
      else{
        for(int j = 0; j < AMOUNT_OF_TILES; j++){
          for(int k = 0; k < amountOfPlayers; k++){
            for(int l = 0; l < board[j].doesGetMaterial(players[k], roll); l++){
              players[k].addCard(board[j].getMaterial());
            }
          }
        }
      }

      do{
        clearMenu(SPACING);
        changeColor("white");
        cout << players[i].getName() << "'s Turn\n\nDice Roll: " << roll;


        canBuild = false;
        int menuCounter = 1;

        clearGameMenu(SPACING);

        if(players[i].hasCards(roadRecipie, AMOUNT_OF_ROAD_CARDS)){
          canBuild = true;
        }
        else if(players[i].hasCards(settlementRecipie, AMOUNT_OF_SETTLEMENT_CARDS)){
          canBuild = true;
        }
        else if(players[i].hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
          canBuild = true;
        }
        else if(players[i].hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
          canBuild = true;
        }

        changeColor("white");
        if(canBuild){
          cout << '[' << menuCounter << "]: " << MENU[0] << '\n';
          menuCounter++;
        }

        cout << '[' << menuCounter << "]: " << MENU[1] << '\n';
        menuCounter++;

        if(players[i].hasDevelopmentCard()){
          cout << '[' << menuCounter << "]: " << MENU[2] << '\n';
          menuCounter++;
        }

        if(players[i].hasCardsRemaining()){
          cout << '[' << menuCounter << "]: " << MENU[3] << '\n';
          menuCounter++;
        }

        cout << '[' << menuCounter << "]: " << MENU[4] << '\n';
        menuCounter++;
        cout << '[' << menuCounter << "]: " << MENU[5] << '\n';

        cout << "\nSelection: ";
        menuSelection = getInt("selection");
        menuSelection = checkRangeShort(menuSelection, menuCounter, 1, "selection");

        switch(menuSelection){
          case 1:
            if(canBuild){
              build(board, players[i], AMOUNT_OF_TILES, SPACING);
            }
            else if(players[i].hasCardsRemaining()){
              trade(players, amountOfPlayers, i, SPACING);
            }
            else if(players[i].hasDevelopmentCard()){
              if(moveRobber(board, players, i, amountOfPlayers, AMOUNT_OF_TILES, SPACING, robbedSelection)){
                players[i].stealCard(players[robbedSelection]);
              }
            }
            else{
              clearGameMenu(SPACING);
              cout << "Cards:\n\n";
              players[i].displayCards();
              cout << "\n\nPress enter to return\nto actions menu...";
              enterKey();
            }
          break;
          case 2:
            if(canBuild){
              if(players[i].hasCardsRemaining()){
                trade(players, amountOfPlayers, i, SPACING);
              }
              else if(players[i].hasCardsRemaining()){
                trade(players, amountOfPlayers, i, SPACING);
              }
              else if(players[i].hasDevelopmentCard()){
                if(moveRobber(board, players, i, amountOfPlayers, AMOUNT_OF_TILES, SPACING, robbedSelection)){
                  players[i].stealCard(players[robbedSelection]);
                }
              }
              else{
                clearGameMenu(SPACING);
                cout << "Cards:\n\n";
                players[i].displayCards();
                cout << "\n\nPress enter to return\nto actions menu...";
                enterKey();
              }
            }
            else if(players[i].hasDevelopmentCard()){
              if(moveRobber(board, players, i, amountOfPlayers, AMOUNT_OF_TILES, SPACING, robbedSelection)){
                players[i].stealCard(players[robbedSelection]);
              }
            }
            else{
              clearGameMenu(SPACING);
              cout << "Cards:\n\n";
              players[i].displayCards();
              cout << "\n\nPress enter to return\nto actions menu...";
              enterKey();
            }
          break;
          case 3:
            if(canBuild){
              if(players[i].hasCardsRemaining()){
                if(players[i].hasDevelopmentCard()){
                  if(moveRobber(board, players, i, amountOfPlayers, AMOUNT_OF_TILES, SPACING, robbedSelection)){
                    players[i].stealCard(players[robbedSelection]);
                  }
                }
                else{
                  clearGameMenu(SPACING);
                  cout << "Cards:\n\n";
                  players[i].displayCards();
                  cout << "\n\nPress enter to return\nto actions menu...";
                  enterKey();
                }
              }
              else if(players[i].hasDevelopmentCard()){
                if(moveRobber(board, players, i, amountOfPlayers, AMOUNT_OF_TILES, SPACING, robbedSelection)){
                  players[i].stealCard(players[robbedSelection]);
                }
              }
              else{
                clearGameMenu(SPACING);
                cout << "Cards:\n\n";
                players[i].displayCards();
                cout << "\n\nPress enter to return\nto actions menu...";
                enterKey();
              }
            }
            else if(players[i].hasCardsRemaining()){
              if(players[i].hasDevelopmentCard()){
                clearGameMenu(SPACING);
                cout << "Cards:\n\n";
                players[i].displayCards();
                cout << "\n\nPress enter to return\nto actions menu...";
                enterKey();
              }
              else{
                turnDone = true;
              }
            }
            else if(players[i].hasDevelopmentCard()){
              turnDone = true;
            }
            else{
              clearMenu(SPACING);
              cout << "Are you sure you want to quit game?\n\n(y/n): ";
              YorN = getChar("quit permission");
              while(!checkChar(YorN, "yn")){
                changeColor("red");
                cout << "Err: invalid selection";
                changeColor("white");
                cout << "\nplease re-enter selection: ";
                YorN = getChar("quit permission");
              }

              if(tolower(YorN) == 'y'){
                turnDone = true;
                gameOver = true;
              }
            }
          break;
          case 4:
          if(canBuild){
            if(players[i].hasCardsRemaining()){
              if(players[i].hasDevelopmentCard()){
                clearGameMenu(SPACING);
                cout << "Cards:\n\n";
                players[i].displayCards();
                cout << "\n\nPress enter to return\nto actions menu...";
                enterKey();
              }
              else{
                turnDone = true;
              }
            }
            else if(players[i].hasDevelopmentCard()){
              turnDone = true;
            }
            else{
              clearMenu(SPACING);
              cout << "Are you sure you want to quit game?\n\n(y/n): ";
              YorN = getChar("quit permission");
              while(!checkChar(YorN, "yn")){
                changeColor("red");
                cout << "Err: invalid selection";
                changeColor("white");
                cout << "\nplease re-enter selection: ";
                YorN = getChar("quit permission");
              }

              if(tolower(YorN) == 'y'){
                turnDone = true;
                gameOver = true;
              }
            }
          }
          else if(players[i].hasCardsRemaining()){
            if(players[i].hasDevelopmentCard()){
              turnDone = true;
            }
            else{
              clearMenu(SPACING);
              cout << "Are you sure you want to quit game?\n\n(y/n): ";
              YorN = getChar("quit permission");
              while(!checkChar(YorN, "yn")){
                changeColor("red");
                cout << "Err: invalid selection";
                changeColor("white");
                cout << "\nplease re-enter selection: ";
                YorN = getChar("quit permission");
              }

              if(tolower(YorN) == 'y'){
                turnDone = true;
                gameOver = true;
              }
            }
          }
          else{
            clearMenu(SPACING);
            cout << "Are you sure you want to quit game?\n\n(y/n): ";
            YorN = getChar("quit permission");
            while(!checkChar(YorN, "yn")){
              changeColor("red");
              cout << "Err: invalid selection";
              changeColor("white");
              cout << "\nplease re-enter selection: ";
              YorN = getChar("quit permission");
            }

            if(tolower(YorN) == 'y'){
              turnDone = true;
              gameOver = true;
            }
          }
          break;
          case 5:
          if(canBuild){
            if(players[i].hasCardsRemaining()){
              if(players[i].hasDevelopmentCard()){
                turnDone = true;
              }
              else{
                clearMenu(SPACING);
                cout << "Are you sure you want to quit game?\n\n(y/n): ";
                YorN = getChar("quit permission");
                while(!checkChar(YorN, "yn")){
                  changeColor("red");
                  cout << "Err: invalid selection";
                  changeColor("white");
                  cout << "\nplease re-enter selection: ";
                  YorN = getChar("quit permission");
                }

                if(tolower(YorN) == 'y'){
                  turnDone = true;
                  gameOver = true;
                }
              }
            }
            else if(players[i].hasDevelopmentCard()){
              cout << "Are you sure you want to quit game?\n\n(y/n): ";
              YorN = getChar("quit permission");
              while(!checkChar(YorN, "yn")){
                changeColor("red");
                cout << "Err: invalid selection";
                changeColor("white");
                cout << "\nplease re-enter selection: ";
                YorN = getChar("quit permission");
              }

              if(tolower(YorN) == 'y'){
                turnDone = true;
                gameOver = true;
              }
            }
          }
          else if(players[i].hasCardsRemaining()){
            clearMenu(SPACING);
            cout << "Are you sure you want to quit game?\n\n(y/n): ";
            YorN = getChar("quit permission");
            while(!checkChar(YorN, "yn")){
              changeColor("red");
              cout << "Err: invalid selection";
              changeColor("white");
              cout << "\nplease re-enter selection: ";
              YorN = getChar("quit permission");
            }

            if(tolower(YorN) == 'y'){
              turnDone = true;
              gameOver = true;
            }
          }
          break;
          case 6:
          if(canBuild && players[i].hasDevelopmentCard() && players[i].hasCardsRemaining()){
            clearMenu(SPACING);
            cout << "Are you sure you want to quit game?\n\n(y/n): ";
            YorN = getChar("quit permission");
            while(!checkChar(YorN, "yn")){
              changeColor("red");
              cout << "Err: invalid selection";
              changeColor("white");
              cout << "\nplease re-enter selection: ";
              YorN = getChar("quit permission");
            }

            if(tolower(YorN) == 'y'){
              turnDone = true;
              gameOver = true;
            }
          }
          break;
        }

        if(players[i].getPoints() > 10){
          clear();
          changeColor("green");
          cout << players[i].getName() << "You won!";
          changeColor("white");
          cout << "\n\nPress enter to return to main menu...";
          enterKey();
          turnDone = true;
          gameOver = true;
        }
      }while(!turnDone);
    }
  }
}

void help(){
  changeColor("cyan");
  cout << "Help: ";
  cout << "How to play settlers refer to:";
  changeColor("red");
  cout << " https://www.catan.com/service/how-learn-catan/catan-assistant#\n\n";


  changeColor("cyan");
  cout << "How to use terminal settlers:\n\n";
  changeColor("white");
  cout << "\tUpon a starting a new game, the game autmoaticly generates a new random terrain.";
  cout << "\n\tTerminal catan may be navigated using the W, A, S, D keys";

  cout << "\n\nControls:\n\n\t";

  changeColor("white");
  cout << "        ----- \n\t";
  cout << "       |  W  |\n\t";
  cout << "  -----------------\n\t";
  cout << " |  A  |  S  |  D  |\n\t";
  cout << "  -----------------\n\n";
  cout << "\t- W = up";
  cout << "\n\t- A = left";
  cout << "\n\t- S = down";
  cout << "\n\t- D = right\n\n";

  cout << "Press enter to return to main menu";
  enterKey();
}

void clearMenu(const int SPACING){
  setCursor(1, 1);
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < SPACING + 25; j++){
      cout << ' ';
    }
    cout << '\n';
  }
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < SPACING + 18; j++){
      cout << ' ';
    }
    cout << '\n';
  }
  for(int i = 0; i < SPACING - 9; i++){
    for(int j = 0; j < SPACING; j++){
      cout << ' ';
    }
    cout << '\n';
  }
  setCursor(1, 1);
}

void clearGameMenu(const int SPACING){
  setCursor(1, 4);
  for(int i = 0; i < 1; i++){
    for(int j = 0; j < SPACING + 25; j++){
      cout << ' ';
    }
    cout << '\n';
  }
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < SPACING + 18; j++){
      cout << ' ';
    }
    cout << '\n';
  }
  for(int i = 0; i < SPACING - 9; i++){
    for(int j = 0; j < SPACING; j++){
      cout << ' ';
    }
    cout << '\n';
  }
  setCursor(1, 5);
}

void build(hexTile board[], player currentPlayer, const int AMOUNT_OF_TILES, const int SPACING){
  int buildingCounter = 0;
  int selection = 0;
  const int AMOUNT_OF_ROAD_CARDS = 2;
  const int AMOUNT_OF_SETTLEMENT_CARDS = 4;
  const int AMOUNT_OF_CITY_CARDS = 5;
  const int AMOUNT_OF_CARDS_SPECIAL = 3;
  card roadRecipie[AMOUNT_OF_ROAD_CARDS];
  card settlementRecipie[AMOUNT_OF_SETTLEMENT_CARDS];
  card cityRecipie[AMOUNT_OF_CITY_CARDS];
  card developmentCardRecipie[AMOUNT_OF_CARDS_SPECIAL];

  roadRecipie[0].name = "brick";
  roadRecipie[1].name = "wood";
  settlementRecipie[0].name = "brick";
  settlementRecipie[1].name = "wood";
  settlementRecipie[2].name = "wheat";
  settlementRecipie[3].name = "sheep";
  cityRecipie[0].name = "ore";
  cityRecipie[1].name = "ore";
  cityRecipie[2].name = "ore";
  cityRecipie[3].name = "wheat";
  cityRecipie[4].name = "wheat";
  developmentCardRecipie[0].name = "ore";
  developmentCardRecipie[1].name = "sheep";
  developmentCardRecipie[2].name = "wheat";


  clearGameMenu(SPACING);

  cout << "Your Cards:\n\n";
  currentPlayer.displayCards();
  cout << "\n\nWhat you like to build?\n\n";

  if(currentPlayer.hasCards(roadRecipie, AMOUNT_OF_ROAD_CARDS)){
    buildingCounter++;
    cout << '[' << buildingCounter << "]: " << "Road\n(brick + wood)\n";
  }
  else if(currentPlayer.hasCards(settlementRecipie, AMOUNT_OF_SETTLEMENT_CARDS)){
    buildingCounter++;
    cout << '[' << buildingCounter << "]: " << "settlement\n(brick + wood + sheep + wheat)\n";
  }
  else if(currentPlayer.hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
    buildingCounter++;
    cout << '[' << buildingCounter << "]: " << "City\n(ore + ore + ore + wheat + wheat)\n";
  }
  else if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
    buildingCounter++;
    cout << '[' << buildingCounter << "]: " << "Development Card\n(ore + sheep + wheat)\n";
  }
    buildingCounter++;
  cout << '[' << buildingCounter << "]: " << "Back\n";

  cout << "\nSelection: ";
  selection = getInt("selection");
  selection = checkRangeShort(selection, buildingCounter, 1, "selection");

  switch(selection){
    case 1:
      if(currentPlayer.hasCards(roadRecipie, AMOUNT_OF_ROAD_CARDS)){
        buildRoad(board, currentPlayer, AMOUNT_OF_TILES, SPACING);
      }
      else if(currentPlayer.hasCards(settlementRecipie, AMOUNT_OF_SETTLEMENT_CARDS)){
        buildSettlement(board, currentPlayer, AMOUNT_OF_TILES, SPACING);
      }
      else if(currentPlayer.hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
        buildCity(board, currentPlayer, AMOUNT_OF_TILES, SPACING);
      }
      else if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
        currentPlayer.addDevelpomentCard();
      }
    break;
    case 2:
      if(currentPlayer.hasCards(roadRecipie, AMOUNT_OF_ROAD_CARDS)){
        if(currentPlayer.hasCards(settlementRecipie, AMOUNT_OF_SETTLEMENT_CARDS)){
          buildSettlement(board, currentPlayer, AMOUNT_OF_TILES, SPACING);
        }
        else if(currentPlayer.hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
          buildCity(board, currentPlayer, AMOUNT_OF_TILES, SPACING);
        }
        else if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
          currentPlayer.addDevelpomentCard();
        }
      }
      else if(currentPlayer.hasCards(settlementRecipie, AMOUNT_OF_SETTLEMENT_CARDS)){
        if(currentPlayer.hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
          buildCity(board, currentPlayer, AMOUNT_OF_TILES, SPACING);
        }
        else if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
          currentPlayer.addDevelpomentCard();
        }
      }
      else if(currentPlayer.hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
        if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
          currentPlayer.addDevelpomentCard();
        }
      }
    break;
    case 3:
      if(currentPlayer.hasCards(roadRecipie, AMOUNT_OF_ROAD_CARDS)){
        if(currentPlayer.hasCards(settlementRecipie, AMOUNT_OF_SETTLEMENT_CARDS)){
          if(currentPlayer.hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
            buildCity(board, currentPlayer, AMOUNT_OF_TILES, SPACING);
          }
          else if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
            currentPlayer.addDevelpomentCard();
          }
        }
        else if(currentPlayer.hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
          if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
            currentPlayer.addDevelpomentCard();
          }
        }
        else if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
          currentPlayer.addDevelpomentCard();
        }
      }
    break;
    case 4:
    if(currentPlayer.hasCards(roadRecipie, AMOUNT_OF_ROAD_CARDS)){
      if(currentPlayer.hasCards(settlementRecipie, AMOUNT_OF_SETTLEMENT_CARDS)){
        if(currentPlayer.hasCards(cityRecipie, AMOUNT_OF_CITY_CARDS)){
          if(currentPlayer.hasCards(developmentCardRecipie, AMOUNT_OF_CARDS_SPECIAL)){
            currentPlayer.addDevelpomentCard();
          }
        }
      }
    }
    break;
  }

  clearGameMenu(SPACING);
}

void buildRoad(hexTile board[], player currentPlayer, const int AMOUNT_OF_TILES, const int SPACING){
  char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int characterCounter = 0;
  int edgeInt = 0;
  structure roadOrigin, road;

  char originSelection = ' ';
  char edge = ' ';

  roadOrigin.fillChar = '*';

  hexTile boardPicker[AMOUNT_OF_TILES];

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    boardPicker[i] = board[i];
    boardPicker[i].fillSettlements('*');
  }

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    boardPicker[i].showNearbySettlementLocations(boardPicker, AMOUNT_OF_TILES, currentPlayer, characterCounter, alphabet);
  }

  printBoard(boardPicker, AMOUNT_OF_TILES);
  clearGameMenu(SPACING);

  cout << "Where would you like to build your road from?\n\nOrigin: ";
  originSelection = getChar("origin");

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    roadOrigin = boardPicker[i].findSettlementLocation(originSelection);
  }

  while(roadOrigin.fillChar == '*'){
    changeColor("red");
    cout << "Err: invalid location\n";
    changeColor("white");
    cout << "Origin: ";
    originSelection = getChar("origin");

    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      roadOrigin = boardPicker[i].findSettlementLocation(originSelection);
    }
  }

  showRoadSelection(boardPicker, AMOUNT_OF_TILES, roadOrigin);
  clearGameMenu(SPACING);
  changeColor("white");

  cout << currentPlayer.getName() << "\nSelect edge: (a - c)\n\nEdge: ";
  edge = getChar("edge");

  while(!checkChar(edge, "abc")){
    changeColor("red");
    cout << "Err: invalid edge";
    changeColor("white");
    cout << "\nPlease re-enter edge: ";
    edge = getChar("edge");
  }

  switch(edge){
    case 'a':
      edgeInt = 0;
    break;
    case 'b':
      edgeInt = 1;
    break;
    case 'c':
      edgeInt = 2;
    break;
  }

  while(roadOrigin.connectingStructures[edgeInt] == nullptr || roadOrigin.connectingStructures[edgeInt] -> color != "grey"){
    changeColor("red");
    cout << "Err: edge not selectable";
    changeColor("white");
    cout << "\nPlease re-enter edge: ";
    edge = getChar("edge");

    while(!checkChar(edge, "abc")){
      changeColor("red");
      cout << "Err: invalid edge";
      changeColor("white");
      cout << "\nPlease re-enter edge: ";
      edge = getChar("edge");
    }

    switch(edge){
      case 'a':
        edgeInt = 0;
      break;
      case 'b':
        edgeInt = 1;
      break;
      case 'c':
        edgeInt = 2;
      break;
    }
  }
  road = *roadOrigin.connectingStructures[edgeInt];
  road.color = currentPlayer.getColor();

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    board[i].addIdenticlEdges(road);
  }

  printBoard(board, AMOUNT_OF_TILES);
}

void buildSettlement(hexTile board[], player currentPlayer, const int AMOUNT_OF_TILES, const int SPACING){
  char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int characterCounter = 0;
  int edgeInt = 0;
  structure settlement;

  char originSelection = ' ';

  settlement.fillChar = '*';

  hexTile boardPicker[AMOUNT_OF_TILES];
  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    boardPicker[i] = board[i];
    boardPicker[i].fillSettlements('*');
  }

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    boardPicker[i].showPossibleSettlmentAreas(currentPlayer, characterCounter, alphabet);
  }

  if(characterCounter == 0){
    clearGameMenu(SPACING);
    cout << "No locations availible to build settlment\nBuild more roads tobuild a settlement\n\nPress enter to return to menu...";
    enterKey();
  }else{
    printBoard(boardPicker, AMOUNT_OF_TILES);

    clearGameMenu(SPACING);

    cout << "Where would you like to build a new settlment?\n\nOrigin: ";
    originSelection = getChar("origin");

    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      settlement = boardPicker[i].findSettlementLocation(originSelection);
    }

    while(settlement.fillChar == '*'){
      changeColor("red");
      cout << "Err: invalid location\n";
      changeColor("white");
      cout << "Origin: ";
      originSelection = getChar("origin");

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        settlement = boardPicker[i].findSettlementLocation(originSelection);
      }
    }

    settlement.color = currentPlayer.getColor();
    settlement.fillChar = 'S';

    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticleCorners(settlement);
    }

    currentPlayer.incrimentPoints();
  }
}

void buildCity(hexTile board[], player currentPlayer, const int AMOUNT_OF_TILES, const int SPACING){
  char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int characterCounter = 0;
  int edgeInt = 0;
  structure city;

  char originSelection = ' ';

  hexTile boardPicker[AMOUNT_OF_TILES];
  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    boardPicker[i] = board[i];
  }

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    boardPicker[i].selectSetttlments(currentPlayer, characterCounter, alphabet);
  }

  if(characterCounter == 0){
    clearGameMenu(SPACING);
    cout << "No settlements left to upgrade\nBuild more settlements to make city\n\nPress enter to return to menu...";
    enterKey();
  }else{
    printBoard(boardPicker, AMOUNT_OF_TILES);

    clearGameMenu(SPACING);

    cout << "Which settlment would you like\nto upgrade?\n\nOrigin: ";
    originSelection = getChar("origin");

    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      city = boardPicker[i].findSettlementLocation(originSelection);
    }

    while(city.color != currentPlayer.getColor()){
      changeColor("red");
      cout << "Err: invalid location\n";
      changeColor("white");
      cout << "Origin: ";
      originSelection = getChar("origin");

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        city = boardPicker[i].findSettlementLocation(originSelection);
      }
    }

    city.color = currentPlayer.getColor();
    city.fillChar = 'C';

    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticleCorners(city);
    }

    currentPlayer.incrimentPoints();
  }
}

void trade(player players[], const int amountOfPlayers, const int currentPlayer, const int SPACING){
  const int AMOUNT_OF_MENUS = 3;
  const string MENU[AMOUNT_OF_MENUS] = {"Bank", "Player", "Back"};
  int selection = 0;
  int playerCounter = 0;
  int playerSelection = 0;

  clearGameMenu(SPACING);

  printMenu(MENU, AMOUNT_OF_MENUS);
  selection = getInt("selection");
  selection = checkRangeShort(selection, AMOUNT_OF_MENUS, 1, "selection");

  switch(selection){
    case 1:
      clearMenu(SPACING);
      players[currentPlayer].tradeIn();
    break;
    case 2:
    clearGameMenu(SPACING);

    cout << "Select player to trade with:\n\n";

      for(int i = 0; i < amountOfPlayers; i++){
        if(i != currentPlayer){
          changeColor(players[i].getColor());
          playerCounter++;
          cout << '[' << playerCounter << "]: " << players[i].getName() << '\n';
        }
      }

      changeColor("white");
      cout << '[' << amountOfPlayers << "]: Back\n\nSelection: ";
      playerSelection = getInt("selection");
      playerSelection = checkRangeShort(playerSelection, playerCounter + 1, 1, "selection");

      if(playerSelection != amountOfPlayers){
        for(int i = 0; i < amountOfPlayers; i++){
          if(i == playerSelection - 1 && i != currentPlayer){
            clearGameMenu(SPACING);
            players[currentPlayer].offer(players[currentPlayer], players[i], SPACING);
            break;
          }
          else{
            playerSelection++;
          }
        }
      }
    break;
  }
}

bool addStructure(hexTile board[], const int AMOUNT_OF_TILES, int boardSelecion, char corner, structure &settlement){
  bool returnValue = false;

  switch(corner){
    case 'a':
      if(board[boardSelecion].validStructureLocation(settlement, 't', 'l')){
        board[boardSelecion].addStructure(settlement, 't', 'l');
        returnValue = true;
      }
    break;
    case 'b':
      if(board[boardSelecion].validStructureLocation(settlement, '\0', 'l')){
        board[boardSelecion].addStructure(settlement, '\0', 'l');
        returnValue = true;
      }
    break;
    case 'c':
      if(board[boardSelecion].validStructureLocation(settlement, 'b', 'l')){
        board[boardSelecion].addStructure(settlement, 'b', 'l');
        returnValue = true;
      }
    break;
    case 'd':
      if(board[boardSelecion].validStructureLocation(settlement, 'b', 'r')){
        board[boardSelecion].addStructure(settlement, 'b', 'r');
        returnValue = true;
      }
    break;
    case 'e':
      if(board[boardSelecion].validStructureLocation(settlement, '\0', 'r')){
        board[boardSelecion].addStructure(settlement, '\0', 'r');
        returnValue = true;
      }
    break;
    case 'f':
      if(board[boardSelecion].validStructureLocation(settlement, 't', 'r')){
        board[boardSelecion].addStructure(settlement, 't', 'r');
        returnValue = true;
      }
    break;
  }

  if(returnValue == true){
    for(int i = 0; i < AMOUNT_OF_TILES; i++){
    board[i].addIdenticleCorners(settlement);
    }
  }

  return returnValue;
}

bool validRoadLocation(structure inputRoad, structure inputStructure){
  bool returnValue = false;



  return returnValue;
}

bool moveRobber(hexTile board[], player players[], int currentPlayer, const int amountOfPlayers, const int AMOUNT_OF_TILES, const int SPACING, int &robbedSelection){
  hexTile boardPicker[AMOUNT_OF_TILES];
  bool hexagonFound = false;
  bool playerFound = false;
  bool returnValue  = false;
  char hexagon  = ' ';
  int selection = 0;
  int playerCounter = 0;
  int playerSelection = 0;
  int possiblePlayersToSteal[4];

  showSettlementSelection(boardPicker, board, AMOUNT_OF_TILES);
  clearGameMenu(SPACING);

  changeColor("white");
  cout << "\n\nSelect the hexagon that you would\nlike to rob: (a - s)\n\nHexagon: ";
  hexagon = getChar("hexagon");

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    if(hexagon == boardPicker[i].getLeftCornerChar() && boardPicker[i].valid()){
      hexagonFound = true;
      selection = i;
    }
  }

  while(!hexagonFound){
    changeColor("red");
    cout << "Err: invalid selection";
    changeColor("white");
    cout << "\nplease re-enter selection: ";
    hexagon = getChar("hexagon");

    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      if(hexagon == boardPicker[i].getLeftCornerChar()){
        hexagonFound = true;
        selection = i;
      }
    }
  }

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    board[i].replenish();
  }

  board[selection].rob();

  for(int i = 0; i < AMOUNT_OF_TILES; i++){
    board[i].print();
  }

  clearGameMenu(SPACING);

  cout << "Which player would you like to rob?\n\n";

  for(int i = 0; i < amountOfPlayers; i++){
    if(board[selection].hasPlayerStructure(players[i]) && players[i].getColor() != players[currentPlayer].getColor()){
      possiblePlayersToSteal[playerCounter] = i;
      playerCounter++;
      changeColor(players[i].getColor());
      cout << '[' << i + 1 << "]: " << players[i].getName() << '\n';
    }
  }

  if(playerCounter == 0){
    returnValue = false;
  }
  else{
    returnValue = true;

    cout << "\nPlayer: ";
    playerSelection = getInt("player");

    for(int i = 0; i < playerCounter; i++){
      if(playerSelection - 1 == possiblePlayersToSteal[i]){
        playerFound = true;
      }
    }

    while(!playerFound){
      changeColor("red");
      cout << "Err: invalid selection";
      changeColor("white");
      cout << "\nplease re-enter player: ";
      playerSelection = getInt("player");

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        for(int i = 0; i < playerCounter; i++){
          if(playerSelection - 1 == possiblePlayersToSteal[i]){
            playerFound = true;
          }
        }
      }
    }
    clearGameMenu(SPACING);
    robbedSelection = playerSelection - 1;
  }

  return returnValue;
}

int diceRoll(){
  const int MAX_ROLL_POSSIBLILITIES = 35;
  int combinationNumber = 0;
  int roll = 0;

  combinationNumber = getRandomNum(MAX_ROLL_POSSIBLILITIES);

  if(combinationNumber == 0){
    roll = 2;
  }
  else if(combinationNumber == 1 || combinationNumber == 2){
    roll = 3;
  }
  else if(combinationNumber > 2 && combinationNumber < 6){
    roll = 4;
  }
  else if(combinationNumber >= 6 && combinationNumber < 10){
    roll = 5;
  }
  else if(combinationNumber >= 10 && combinationNumber < 15){
    roll = 6;
  }
  else if(combinationNumber >= 15 && combinationNumber < 21){
    roll = 7;
  }
  else if(combinationNumber >= 21 && combinationNumber < 26){
    roll = 8;
  }
  else if(combinationNumber >= 26 && combinationNumber < 30){
    roll = 9;
  }
  else if(combinationNumber >= 30 && combinationNumber < 33){
    roll = 10;
  }
  else if(combinationNumber == 33 || combinationNumber == 34){
    roll = 11;
  }
  else if(combinationNumber == 35){
    roll = 12;
  }

  return roll;
}
