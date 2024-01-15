struct structure{
  string color;
  structure* connectingStructures[3];
  int x;
  int y;
  char fillChar;
  int weight;
};

struct card{
  string color;
  string name;
};

class player{
  private:
    string name;
    string color;
    int points;
    int MAX_AMOUNT_OF_CARDS;
    int MAX_AMOUNT_OF_DEVELOPMENT_CARDS;
    int amountOfCards;
    int amountOfDevelopmentCards;
    bool LongestRoad;
    bool LargestArmy;
    card cards[95];
  public:
    player();
    player(string nm, string clr);

    void populatePlayer(string nm, string clr);
    void addCard(card newCard);
    void removeCards(card inCards[], int amountOfInCards);
    void removeCard(card removalCard);
    void stealCard(player &robbedPlayer);
    void halfCards(const int SPACING);
    void displayCards();
    void incrimentPoints();
    void incrimentPoints(const int AMOUNT);
    void addDevelpomentCard();
    void offer(player currentPlayer, player &inputPlayer, const int SPACING);
    void tradeIn();
    card cardStolen();
    int getCardAmount();
    int getPoints();
    bool hasDevelopmentCard();
    bool hasCards(card recipie[], int amountOfItems);
    bool hasCardsRemaining();
    string getColor();
    string getName();
    card getCard(int selection);
};

class hexTile{
  private:
    string landscapeHighlightColor;
    string landscapeColor;
    string landscapeColorCache;
    string landscapeHighlightColorCache;
    int    tileDigit;
    int secondaryTileDigit;
    int originX;
    int originY;
    int identifier;
    card material;
    bool robbed;
    hexTile* neighboringTiles[6];
    structure topLeftCorner, topRightCorner, leftCorner, bottomLeftCorner, bottomRightCorner, rightCorner;
    structure topEdge, topLeftEdge, bottomLeftEdge, bottomEdge, bottomRightEdge, topRightEdge;

  public:

    hexTile();

    void assignOrigin(int x, int y);
    void print();
    void showSelection();
    void resetBackground();
    void assignLandscape(string color);
    void assignLandscape(string color, string highlight);
    void assignTileNum(int input, int input2);
    void assignTileNum(int input);
    void assignIdentifier(int input);
    void findNeighbors(hexTile board[]);
    void connectStructures();
    void correctRoadDirections();
    void assignNeighboringTiles(int input[]);
    void addRoad();
    void fillSettlements(char inputChar);
    void addStructure(structure &inputStructure, char vertical, char horisontal);
    void addIdenticleCorners(structure comparatorStructure);
    void addIdenticlEdges(structure comparatorStructure);
    void assignMaterial(string name, string color);
    void replenish();
    void rob();
    void showNearbySettlementLocations(hexTile board[], const int AMOUNT_OF_TILES, player currentPlayer, int &AmountOfCharactersUsed, char assigningCharacter[]);
    void showPossibleSettlmentAreas(player currentPlayer, int &AmountOfCharactersUsed, char assigningCharacter[]);
    void selectSetttlments(player currentPlayer, int &AmountOfCharactersUsed, char assigningCharacter[]);
    structure findRoadLocation(char searchChar);
    structure findSettlementLocation(char searchChar);
    card getMaterial();
    bool isDesert();
    bool validRoadSourceLocation(structure inputStructure);
    bool hasPlayerStructure(player inputPlayer);
    bool hasStructure(structure inputStructure);
    bool valid();
    bool validStructureLocation(structure inputStructure, char vertical, char horisontal);
    char getLeftCornerChar();
    string getColor();
    int doesGetMaterial(player inputPlayer, int roll);
};

player::player(){
  name = "blank";
  color = "white";
  points = 0;
  LongestRoad = false;
  LargestArmy = false;
  amountOfCards = 0;
  amountOfDevelopmentCards = 0;
  MAX_AMOUNT_OF_CARDS = 95;
  MAX_AMOUNT_OF_DEVELOPMENT_CARDS = 25;
  for(int i = 0; i < MAX_AMOUNT_OF_CARDS; i++){
    cards[i].name = " ";
    cards[i].color = "grey";
  }
}

player::player(string nm, string clr){
  name = nm;
  color = clr;
  points = 0;
  LongestRoad = false;
  LargestArmy = false;
  amountOfCards = 0;
  amountOfDevelopmentCards = 0;
  MAX_AMOUNT_OF_CARDS = 95;
  MAX_AMOUNT_OF_DEVELOPMENT_CARDS = 25;
  for(int i = 0; i < MAX_AMOUNT_OF_CARDS; i++){
    cards[i].name = " ";
    cards[i].color = "grey";
  }
}

hexTile::hexTile(){
  landscapeHighlightColor = "true_black";
  landscapeColor = "true_black";
  landscapeHighlightColorCache = "true_black";
  landscapeColorCache = "true_black";
  tileDigit = 0;
  secondaryTileDigit = 0;
  originX = 0;
  originY = 0;
  identifier = 0;
  robbed = false;
  material.name = " ";
  material.color = "grey";
  topLeftCorner.color        = "grey";
  topLeftCorner.fillChar     = 'o';
  topLeftCorner.weight       = 0;
  topRightCorner.color       = "grey";
  topRightCorner.fillChar    = 'o';
  topRightCorner.weight      = 0;
  bottomLeftCorner.color     = "grey";
  bottomLeftCorner.fillChar  = 'o';
  bottomLeftCorner.weight    = 0;
  bottomRightCorner.color    = "grey";
  bottomRightCorner.fillChar = 'o';
  bottomRightCorner.weight   = 0;
  rightCorner.color          = "grey";
  rightCorner.fillChar       = 'o';
  rightCorner.weight         = 0;
  leftCorner.color           = "grey";
  leftCorner.fillChar        = 'o';
  leftCorner.weight          = 0;
  topEdge.color              = "grey";
  topEdge.fillChar           = '-';
  topEdge.weight             = 0;
  topLeftEdge.color          = "grey";
  topLeftEdge.fillChar       = '/';
  topLeftEdge.weight         = 0;
  bottomLeftEdge.color       = "grey";
  bottomLeftEdge.fillChar    = '\\';
  bottomLeftEdge.weight      = 0;
  bottomEdge.color           = "grey";
  bottomEdge.fillChar        = '-';
  bottomEdge.weight          = 0;
  bottomRightEdge.color      = "grey";
  bottomRightEdge.fillChar   = '/';
  bottomRightEdge.weight     = 0;
  topRightEdge.color         = "grey";
  topRightEdge.fillChar      = '\\';
  topRightEdge.weight        = 0;

  for(int i = 0; i < 6; i++){
    neighboringTiles[i] = 0;
  }
}

void player::populatePlayer(string nm, string clr){
  name = nm;
  color = clr;
}

void player::addCard(card newCard){
  cards[amountOfCards].name  = newCard.name;
  cards[amountOfCards].color = newCard.color;
  amountOfCards++;
}

void player::removeCards(card inCards[], int amountOfInCards){
  for(int i = 0; i < amountOfInCards; i++){
    for(int j = 0; j < amountOfCards; j++){
      if(inCards[i].name == cards[j].name){
        for(int k = j; k < amountOfCards; k++){
          cards[i] = cards[i + 1];
        }
        break;
      }
    }
  }
}

void player::removeCard(card removalCard){
  int position = 0;

  for(int i = 0; i < amountOfCards; i++){
    if(cards[i].name == removalCard.name){
      position = i;
    }
  }

  for(int i = position; i < amountOfCards; i++){
    if(position != MAX_AMOUNT_OF_CARDS){
      cards[i] = cards[i + 1];
    }
  }
  cards[MAX_AMOUNT_OF_CARDS - 1].name = " ";
  cards[MAX_AMOUNT_OF_CARDS - 1].color = "grey";

  amountOfCards--;
}

void player::stealCard(player &robbedPlayer){
  addCard(robbedPlayer.cardStolen());
}

card player::cardStolen(){
  int stolenCard = getRandomNum(amountOfCards);
  card retunCard = cards[stolenCard];

  for(int i = stolenCard - 1; i < amountOfCards; i++){
    cards[i] = cards[i + 1];
  }
  cards[MAX_AMOUNT_OF_CARDS - 1].name = " ";
  cards[MAX_AMOUNT_OF_CARDS - 1].color = "grey";

  amountOfCards--;

  return retunCard;
}

void player::halfCards(const int SPACING){

  int selection = 0;

  for(int i = 0; i < amountOfCards / 2; i++){

    setCursor(1, 4);
    for(int j = 0; j < 1; j++){
      for(int k = 0; k < SPACING + 25; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    for(int j = 0; j < 4; j++){
      for(int k = 0; k < SPACING + 18; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    for(int j = 0; j < SPACING - 9; j++){
      for(int k = 0; k < SPACING; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    setCursor(1, 5);

    cout << "Cards:\n\n";
    displayCards();

    cout << "Select the cards you \nwould like to get rid of: ";

    selection = getInt("cards");

    while(!inRange(selection, amountOfCards, 1)){
      changeColor("red");
      cout << "Err: out of range";
      changeColor("white");
      cout << "\nRe-enter selection: ";
      selection = getInt("selection");
    }

    for(int j = selection - 1; j < amountOfCards; j++){
      cards[j] = cards[j + 1];
    }
    cards[MAX_AMOUNT_OF_CARDS - 1].name = " ";
    cards[MAX_AMOUNT_OF_CARDS - 1].color = "grey";

    amountOfCards--;
  }
}

void player::displayCards(){
  for(int i = 0; i < amountOfCards; i++){
    changeColor(cards[i].color);
    cout << '[' << i + 1 << "]: " << cards[i].name << '\n';
  }
  changeColor("white");
}

void player::incrimentPoints(){
  points++;
}

void player::incrimentPoints(const int AMOUNT){
  points += AMOUNT;
}

void player::addDevelpomentCard(){
  card recipieOfCard[3] = {"sheep", "ore", "wheat"};
  removeCards(recipieOfCard, 3);

  amountOfDevelopmentCards++;
}

void player::offer(player currentPlayer, player &inputPlayer, const int SPACING){

  const int AMOUNT_OF_CHOICES = 5;

  string names[AMOUNT_OF_CHOICES] = {"wood", "wheat", "brick", "sheep", "ore"};
  string colors[AMOUNT_OF_CHOICES] = {"dark_green", "dark_yellow", "dark_red", "green", "black"};

  card cardChoices[AMOUNT_OF_CHOICES];
  card sendCards[95];
  card requestedCards[95];

  player cacheInputPlayer = inputPlayer;
  player cacheCurrentPlayer = currentPlayer;

  char accept = ' ';

  int amountOfSendingCards = 0;
  int amountOfRequestedCards = 0;
  int selection = 0;
  int requestSelection = 0;

  for(int i = 0; i < MAX_AMOUNT_OF_CARDS; i++){
    sendCards[i].name = " ";
    sendCards[i].color = "grey";
    requestedCards[i].name = " ";
    requestedCards[i].color = "grey";
  }

  for(int i = 0; i < AMOUNT_OF_CHOICES; i++){
    cardChoices[i].name = names[i];
    cardChoices[i].color = colors[i];
  }

  do{
    setCursor(1, 4);
    for(int j = 0; j < 1; j++){
      for(int k = 0; k < SPACING + 25; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    for(int j = 0; j < 4; j++){
      for(int k = 0; k < SPACING + 18; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    for(int j = 0; j < SPACING - 9; j++){
      for(int k = 0; k < SPACING; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    setCursor(1, 5);

    cout << name << ": what cards would you like\nto offer to " << inputPlayer.getName() << "?\n(enter 0 to continue)\n\nYour cards:\n\n";
    cacheCurrentPlayer.displayCards();
    cout << "\nCards Offering:\n\n";

    if(amountOfSendingCards > 0){

      changeColor(sendCards[0].color);
      cout << '[' << 1 << "]: " << sendCards[0].name << '\n';
      changeColor("white");

      for(int i = 1; i < amountOfSendingCards; i++){
        changeColor(sendCards[i].color);
        cout << '[' << i + 1 << "]: " << sendCards[i].name << '\n';
        changeColor("white");
      }
    }
    cout << "\nCards: ";
    selection = getInt("cards");

    while(!inRange(selection, cacheCurrentPlayer.getCardAmount(), 0)){
      changeColor("red");
      cout << "Err: out of range";
      changeColor("white");
      cout << "\nRe-enter selection: ";
      selection = getInt("selection");
    }

    if(selection != 0){

      sendCards[amountOfSendingCards].name  = cacheCurrentPlayer.getCard(selection - 1).name;
      sendCards[amountOfSendingCards].color = cacheCurrentPlayer.getCard(selection - 1).color;
      cacheCurrentPlayer.removeCard(cacheCurrentPlayer.getCard(selection - 1));
      amountOfSendingCards++;
    }
  }while(selection != 0 && cacheInputPlayer.hasCardsRemaining());

  do{
    setCursor(1, 4);
    for(int j = 0; j < 1; j++){
      for(int k = 0; k < SPACING + 25; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    for(int j = 0; j < 4; j++){
      for(int k = 0; k < SPACING + 18; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    for(int j = 0; j < SPACING - 9; j++){
      for(int k = 0; k < SPACING; k++){
        cout << ' ';
      }
      cout << '\n';
    }
    setCursor(1, 5);

    cout << name << ": what cards would you like\nto recive from " << currentPlayer.getName() << "?\n(enter 0 to continue)\n\nChoices:\n\n";
    for(int i = 0; i < 5; i++){
      changeColor(cardChoices[i].color);
      cout << '[' << i + 1 << "]: " << cardChoices[i].name << '\n';
    }

    changeColor("white");

    cout << "\nCards Requested:\n\n";

    if(amountOfRequestedCards > 0){

      changeColor(requestedCards[0].color);
      cout << '[' << 1 << "]: " << requestedCards[0].name << '\n';
      changeColor("white");

      for(int i = 1; i < amountOfRequestedCards; i++){
        changeColor(requestedCards[i].color);
        cout << '[' << i + 1 << "]: " << requestedCards[i].name << '\n';
      }
    }

    changeColor("white");
    cout << "\nCards: ";
    requestSelection = getInt("cards");

    while(!inRange(requestSelection, AMOUNT_OF_CHOICES, 0)){
      changeColor("red");
      cout << "Err: out of range";
      changeColor("white");
      cout << "\nRe-enter selection: ";
      requestSelection = getInt("selection");
    }
    if(requestSelection != 0){
      requestedCards[amountOfRequestedCards].color = cardChoices[requestSelection - 1].color;
      requestedCards[amountOfRequestedCards].name  = cardChoices[requestSelection - 1].name;
      amountOfRequestedCards++;
    }
  }while(requestSelection != 0);

  setCursor(1, 4);
  for(int j = 0; j < 1; j++){
    for(int k = 0; k < SPACING + 25; k++){
      cout << ' ';
    }
    cout << '\n';
  }
  for(int j = 0; j < 4; j++){
    for(int k = 0; k < SPACING + 18; k++){
      cout << ' ';
    }
    cout << '\n';
  }
  for(int j = 0; j < SPACING - 9; j++){
    for(int k = 0; k < SPACING; k++){
      cout << ' ';
    }
    cout << '\n';
  }
  setCursor(1, 5);

  cout << inputPlayer.getName() << ":\n" << currentPlayer.getName() << " is offering to give you\nthe following cards:\n\n";

  changeColor(sendCards[0].color);
  cout << sendCards[0].name;

  for(int i = 0; i < amountOfSendingCards; i++){
    changeColor(sendCards[i].color);
    cout << '[' << i + 1 << "]: " << sendCards[i].name << '\n';
    changeColor("white");
  }

  changeColor("white");

  cout << "\nin return\nfor the following cards:\n\n";

  changeColor(requestedCards[0].color);
  cout << requestedCards[0].name;

  for(int i = 0; i < amountOfRequestedCards; i++){
    changeColor(requestedCards[i].color);
    cout << '[' << i + 1 << "]: " << requestedCards[i].name << '\n';
    changeColor("white");
  }

  changeColor("white");

  cout << "\n\n" << inputPlayer.getName() << ": Aceept offer?\n(y/n): ";

  accept = getChar("(y/n):");

  while(!checkChar(accept, "yn")){
    changeColor("red");
    cout << "Err: invalid selection";
    changeColor("white");
    cout << "\nplease re-enter selection: ";
    accept = getChar("(y/n):");
  }

  setCursor(1, 4);
  for(int j = 0; j < 1; j++){
    for(int k = 0; k < SPACING + 25; k++){
      cout << ' ';
    }
    cout << '\n';
  }
  for(int j = 0; j < 4; j++){
    for(int k = 0; k < SPACING + 18; k++){
      cout << ' ';
    }
    cout << '\n';
  }
  for(int j = 0; j < SPACING - 9; j++){
    for(int k = 0; k < SPACING; k++){
      cout << ' ';
    }
    cout << '\n';
  }
  setCursor(1, 5);

  if(accept == 'y' && inputPlayer.hasCards(requestedCards, amountOfRequestedCards)){

    changeColor("green");
    cout << "Your offer has been accepted";
    changeColor("white");

    for(int i = 0; i < amountOfSendingCards; i++){
      removeCard(sendCards[i]);
      inputPlayer.addCard(sendCards[i]);
    }
    for(int i = 0; i < amountOfRequestedCards; i++){
      inputPlayer.removeCard(requestedCards[i]);
      addCard(requestedCards[i]);
    }
  }
  else{
    changeColor("red");
    cout << "Offer has been rejected";
    changeColor("white");
  }

  cout << "\n\nPress enter to return to menu...";
  enterKey();
}

void player::tradeIn(){
  const int AMOUNT_OF_CHOICES = 5;
  bool canTrade = false;
  int selection = 0;
  int materialCounter = 0;

  string names[AMOUNT_OF_CHOICES] = {"wood", "wheat", "brick", "sheep", "ore"};
  string colors[AMOUNT_OF_CHOICES] = {"dark_green", "dark_yellow", "dark_red", "green", "black"};

  card quadRecipies[AMOUNT_OF_CHOICES][4];
  card cacheCard;

  for(int i = 0; i < AMOUNT_OF_CHOICES; i++){
    for(int j = 0; j < 4; j++){
      quadRecipies[i][j].name  =  names[i];
      quadRecipies[i][j].color = colors[i];
    }
  }

  for(int i = 0; i < AMOUNT_OF_CHOICES; i++){
    if(hasCards(quadRecipies[i], AMOUNT_OF_CHOICES)){
      canTrade = true;
      break;
    }
  }

  if(canTrade){
    cout << "What material would you like to trade in?\n\n";

    for(int i = 0; i < AMOUNT_OF_CHOICES; i++){
      if(hasCards(quadRecipies[i], AMOUNT_OF_CHOICES)){
        materialCounter++;
        changeColor(quadRecipies[i][0].color);
        cout << '[' << materialCounter << "]: " << quadRecipies[i][0].name << '\n';
      }
    }

    cout << "\nMaterial: ";

    changeColor("white");
    selection = getInt("selection");
    selection = checkRangeShort(selection, materialCounter, 1, "selection");
    for(int i = 0; i < 4; i++){
      if(i == selection - 1 && hasCards(quadRecipies[i], AMOUNT_OF_CHOICES)){
        removeCard(quadRecipies[i][0]);
        break;
      }
      else{
        selection++;
      }
    }

    cout << "\n\nWhat card would you like to get for your trade?\n\n";

    for(int i = 0; i < AMOUNT_OF_CHOICES; i++){
      cout << '[' << i + 1 << "]: " << names[i] << '\n';
    }

    cout << "\nCard: ";
    selection = getInt("selection");
    selection = checkRangeShort(selection, AMOUNT_OF_CHOICES, 1, "selection");


    cacheCard.name  =  names[selection];
    cacheCard.color = colors[selection];

    addCard(cacheCard);
  }
  else{
    changeColor("red");
    cout << "Not enough cards to trad ewith bank\n\n";
    changeColor("white");
    cout << "Press enter to return to menu...";
  }

  enterKey();
}

int player::getCardAmount(){
  return amountOfCards;
}

int player::getPoints(){
  return points;
}

bool player::hasDevelopmentCard(){
  return amountOfDevelopmentCards > 0;
}

bool player::hasCards(card recipie[], int amountOfItems){
  bool returnValue = true;
  string key[5] = {"wood", "wheat", "brick", "sheep", "ore"};
  int recipieCounter[5];
  int deckCounter[5];

  for(int i = 0; i < 5; i++){
    recipieCounter[i] = 0;
    deckCounter[i] = 0;
  }

  for(int i = 0; i < amountOfItems; i++){
    for(int j = 0; j < 5; j++){
      if(recipie[i].name == key[j]){
        recipieCounter[j]++;
      }
    }
  }

  for(int i = 0; i < amountOfCards; i++){
    for(int j = 0; j < 5; j++){
      if(cards[i].name == key[j]){
        deckCounter[j]++;
      }
    }
  }

  for(int i = 0; i < 5; i++){
    if(recipieCounter[i] > deckCounter[i]){
      returnValue = false;
    }
  }

  return returnValue;
}

bool player::hasCardsRemaining(){

  bool returnValue = false;

  if(amountOfCards > 0){
    returnValue = true;
  }

  return returnValue;
}

string player::getColor(){
  return color;
}

string player::getName(){
  return name;
}

card player::getCard(int selection){

  card returnCard;
  returnCard.color = "grey";
  returnCard.name = " ";

  if(selection  >= 0 && selection < amountOfCards){
    returnCard.name  = cards[selection].name;
    returnCard.color = cards[selection].color;
  }

  return returnCard;
}

void hexTile::assignOrigin(int x, int y){
  originX = x;
  originY = y;

  topLeftCorner.x     = x;
  topLeftCorner.y     = y;
  leftCorner.x        = x - 8;
  leftCorner.y        = y + 4;
  bottomLeftCorner.x  = x;
  bottomLeftCorner.y  = y + 8;
  bottomRightCorner.x = x + 10;
  bottomRightCorner.y = y + 8;
  rightCorner.x       = x + 18;
  rightCorner.y       = y + 4;
  topRightCorner.x    = x + 10;
  topRightCorner.y    = y;
  topEdge.x           = x + 1;
  topEdge.y           = y;
  topLeftEdge.x       = x - 4;
  topLeftEdge.y       = y + 2;
  bottomLeftEdge.x    = x - 4;
  bottomLeftEdge.y    = y + 6;
  bottomEdge.x        = x + 1;
  bottomEdge.y        = y + 8;
  bottomRightEdge.x   = x + 14;
  bottomRightEdge.y   = y + 6;
  topRightEdge.x      = x + 14;
  topRightEdge.y      = y + 2;
}

void hexTile::print(){
  setCursor(originX, originY);
  changeColor(topLeftCorner.color);
  for(int i = 0; i < 3; i++){
    cout << topLeftCorner.fillChar;
  }
  changeColor(topEdge.color);
  for(int i = 0; i < 5; i++){
    cout << topEdge.fillChar;
  }
  changeColor(topRightCorner.color);
  for(int i = 0; i < 3; i++){
    cout << topRightCorner.fillChar;
  }

  setCursor(originX - 2, originY + 1);
  changeColor(topLeftCorner.color);
  for(int i = 0; i < 4; i++){
    cout << topLeftCorner.fillChar;
  }
  changeColor(landscapeColor, landscapeHighlightColor);
  for(int i = 0; i < 7; i++){
    if(i % 2 == 0){
      cout << tileDigit;
    }
    else{
      cout << secondaryTileDigit;
    }
  }
  resetBackground();
  changeColor(topRightCorner.color);
  for(int i = 0; i < 4; i++){
    cout << topRightCorner.fillChar;
  }

  setCursor(originX - 4, originY + 2);
  changeColor(topLeftEdge.color);
  cout << topLeftEdge.fillChar;
  changeColor(landscapeColor, landscapeHighlightColor);
  for(int i = 0; i < 17; i++){
    if(i % 2 == 0){
      cout << tileDigit;
    }
    else{
      cout << secondaryTileDigit;
    }
  }
  resetBackground();
  changeColor(topRightEdge.color);
  cout << topRightEdge.fillChar;

  setCursor(originX - 6, originY + 3);
  changeColor(leftCorner.color);
  cout << leftCorner.fillChar;
  changeColor(landscapeColor, landscapeHighlightColor);
  for(int i = 0; i < 21; i++){
    if(i % 2 == 0){
      cout << tileDigit;
    }
    else{
      cout << secondaryTileDigit;
    }
  }
  resetBackground();
  changeColor(rightCorner.color);
  cout << rightCorner.fillChar;

  setCursor(originX - 8, originY + 4);
  changeColor(leftCorner.color);
  for(int i = 0; i < 4; i++){
    cout << leftCorner.fillChar;
  }
  changeColor(landscapeColor, landscapeHighlightColor);
  for(int i = 0; i < 19; i++){
    if(i % 2 == 0){
      cout << tileDigit;
    }
    else{
      cout << secondaryTileDigit;
    }
  }
  resetBackground();
  changeColor(rightCorner.color);
  for(int i = 0; i < 4; i++){
    cout << rightCorner.fillChar;
  }

  setCursor(originX - 6, originY + 5);
  changeColor(leftCorner.color);
  cout << leftCorner.fillChar;
  changeColor(landscapeColor, landscapeHighlightColor);
  for(int i = 0; i < 21; i++){
    if(i % 2 == 0){
      cout << tileDigit;
    }
    else{
      cout << secondaryTileDigit;
    }
  }
  resetBackground();
  changeColor(rightCorner.color);
  cout << rightCorner.fillChar;

  setCursor(originX - 4, originY + 6);
  changeColor(bottomLeftEdge.color);
  cout << bottomLeftEdge.fillChar;
  changeColor(landscapeColor, landscapeHighlightColor);
  for(int i = 0; i < 17; i++){
    if(i % 2 == 0){
      cout << tileDigit;
    }
    else{
      cout << secondaryTileDigit;
    }
  }
  resetBackground();
  changeColor(bottomRightEdge.color);
  cout << bottomRightEdge.fillChar;

  setCursor(originX - 2, originY + 7);
  changeColor(bottomLeftCorner.color);
  for(int i = 0; i < 4; i++){
    cout << bottomLeftCorner.fillChar;
  }
  changeColor(landscapeColor, landscapeHighlightColor);
  for(int i = 0; i < 7; i++){
    if(i % 2 == 0){
      cout << tileDigit;
    }
    else{
      cout << secondaryTileDigit;
    }
  }
  resetBackground();
  changeColor(bottomRightCorner.color);
  for(int i = 0; i < 4; i++){
    cout << bottomRightCorner.fillChar;
  }

  setCursor(originX, originY + 8);
  changeColor(bottomLeftCorner.color);
  for(int i = 0; i < 3; i++){
    cout << bottomLeftCorner.fillChar;
  }
  changeColor(bottomEdge.color);
  for(int i = 0; i < 5; i++){
    cout << bottomEdge.fillChar;
  }
  changeColor(bottomRightCorner.color);
  for(int i = 0; i < 3; i++){
    cout << bottomRightCorner.fillChar;
  }
}

void hexTile::showSelection(){
  topLeftCorner.fillChar = 'a';
  leftCorner.fillChar = 'b';
  bottomLeftCorner.fillChar = 'c';
  bottomRightCorner.fillChar = 'd';
  rightCorner.fillChar = 'e';
  topRightCorner.fillChar = 'f';
  print();
}

void hexTile::resetBackground(){
  changeColor("true_black", "true_black");
}

void hexTile::assignLandscape(string color){
  landscapeColor = color;
  landscapeColorCache = color;
}

void hexTile::assignLandscape(string color, string highlight){
  landscapeColor = color;
  landscapeColorCache = color;
  landscapeHighlightColor = highlight;
  landscapeHighlightColorCache = highlight;
}

void hexTile::assignTileNum(int input){
  tileDigit = input;
  secondaryTileDigit = input;
}

void hexTile::assignTileNum(int input, int input2){
  tileDigit = input;
  secondaryTileDigit = input2;
}

void hexTile::assignIdentifier(int input){
  identifier = input;
}

void hexTile::findNeighbors(hexTile board[]){
  const int AMOUNT_OF_ROWS = 5;
  const int HALF = 2;
  int ROWS[AMOUNT_OF_ROWS] = {0, 3, 7, 12, 16};
  int AMOUNT_IN_ROW[AMOUNT_OF_ROWS] = {3, 4, 5, 4, 3};
  int row = 0;

  for(int i = 0; i < AMOUNT_OF_ROWS - 1; i++){
    if(identifier >= ROWS[i + 1]){
      row++;
    }
    else{
      break;
    }
  }

  if(identifier - 1 < ROWS[row]){
    neighboringTiles[0] = nullptr;
  }
  else{
    neighboringTiles[0] = &board[identifier - 1];
  }

  if(row != 0){
    if(row <= HALF && identifier - 1  >= ROWS[row]){
      neighboringTiles[1] = &board[identifier - AMOUNT_IN_ROW[row]];
    }
    else if(row > HALF){
      neighboringTiles[1] = &board[identifier - AMOUNT_IN_ROW[row] - 1];
    }
    else{
      neighboringTiles[1] = nullptr;
    }
  }
  else{
    neighboringTiles[1] = nullptr;
  }

  if(row != 0){
    if(row > HALF || identifier != ROWS[row] + AMOUNT_IN_ROW[row] - 1){
      neighboringTiles[2] =  &board[identifier - AMOUNT_IN_ROW[row]];
    }
    else{
      neighboringTiles[2] = nullptr;
    }
  }
  else{
    neighboringTiles[2] = nullptr;
  }

  if(identifier == AMOUNT_IN_ROW[row] + ROWS[row] - 1){
    neighboringTiles[3] = nullptr;
  }
  else{
    neighboringTiles[3] = &board[identifier + 1];
  }

  if(row != 4){
    if(row < HALF){
      neighboringTiles[4] =  &board[identifier + AMOUNT_IN_ROW[row]+ 1];
    }
    else if(identifier != AMOUNT_IN_ROW[row] + ROWS[row] - 1){
      neighboringTiles[4] =  &board[identifier + AMOUNT_IN_ROW[row]];
    }
    else{
      neighboringTiles[4] = nullptr;
    }
  }
  else{
    neighboringTiles[4] = nullptr;
  }

  if(row != 4){
    if(row < HALF){
      neighboringTiles[5] =  &board[identifier + AMOUNT_IN_ROW[row]];
    }
    else if(identifier != ROWS[row]){
      neighboringTiles[5] =  &board[identifier + AMOUNT_IN_ROW[row] - 1];
    }
    else{
      neighboringTiles[5] = nullptr;
    }
  }
  else{
    neighboringTiles[5] = nullptr;
  }
}

void hexTile::connectStructures(){

  if(identifier == 0 || identifier == 3 || identifier == 7){
    topLeftCorner.connectingStructures[0] = nullptr;
  }
  else if(identifier == 12 || identifier == 16){
    topLeftCorner.connectingStructures[0] = &neighboringTiles[1] -> topRightEdge;
    //reverse road direction
  }
  else{
    topLeftCorner.connectingStructures[0] = &neighboringTiles[0] -> bottomLeftEdge;
  }
  topLeftCorner.connectingStructures[1] = &topLeftEdge;
  topLeftCorner.connectingStructures[2] = &topEdge;

  if(identifier < 3){
    leftCorner.connectingStructures[0] = nullptr;
  }
  else if(identifier == 3 || identifier == 7){
    leftCorner.connectingStructures[0] = &neighboringTiles[2] -> topEdge;
  }
  else{
    leftCorner.connectingStructures[0] = &neighboringTiles[1] -> bottomEdge;
  }
  leftCorner.connectingStructures[1] = &bottomLeftEdge;
  leftCorner.connectingStructures[2] = &topLeftEdge;

  if(identifier == 2 || identifier == 6 || identifier == 11){
    bottomLeftCorner.connectingStructures[1] = nullptr;
  }
  else if(identifier == 15 || identifier == 18){
    bottomLeftCorner.connectingStructures[1] = &neighboringTiles[2] -> bottomRightEdge;
  }
  else{
    bottomLeftCorner.connectingStructures[1] = &neighboringTiles[3] -> topLeftEdge;
  }
  bottomLeftCorner.connectingStructures[0] = &bottomLeftEdge;
  bottomLeftCorner.connectingStructures[2] = &bottomEdge;

  if(identifier == 11 || identifier == 15 || identifier == 18){
    bottomRightCorner.connectingStructures[1] = nullptr;
  }
  else if(identifier == 2 || identifier == 6){
    bottomRightCorner.connectingStructures[1] = &neighboringTiles[4] -> bottomLeftEdge;
  }
  else{
    bottomRightCorner.connectingStructures[1] = &neighboringTiles[3] -> topRightEdge;
  }
  bottomRightCorner.connectingStructures[0] = &bottomEdge;
  bottomRightCorner.connectingStructures[2] = &bottomRightEdge;

  if(identifier == 16 || identifier == 17 || identifier == 18){
    rightCorner.connectingStructures[2] = nullptr;
  }
  else if(identifier == 11 || identifier == 15){
    rightCorner.connectingStructures[2] = &neighboringTiles[5] -> bottomEdge;
  }
  else{
    rightCorner.connectingStructures[2] = &neighboringTiles[4] -> topEdge;
  }
  rightCorner.connectingStructures[0] = &topRightEdge;
  rightCorner.connectingStructures[1] = &bottomRightEdge;

  if(identifier == 7 || identifier == 12 || identifier == 16){
    topRightCorner.connectingStructures[2] = nullptr;
  }
  else if(identifier == 17 || identifier == 18){
    topRightCorner.connectingStructures[2] = &neighboringTiles[0] -> bottomRightEdge;
  }
  else{
    topRightCorner.connectingStructures[2] = &neighboringTiles[5] -> topLeftEdge;
  }
  topRightCorner.connectingStructures[0] = &topEdge;
  topRightCorner.connectingStructures[1] = &topRightEdge;

  topEdge.connectingStructures[0] = &topLeftCorner;
  topEdge.connectingStructures[1] = &topRightCorner;
  topEdge.connectingStructures[2] = nullptr;

  topLeftEdge.connectingStructures[0] = &leftCorner;
  topLeftEdge.connectingStructures[1] = &topLeftCorner;
  topLeftEdge.connectingStructures[2] = nullptr;

  bottomLeftEdge.connectingStructures[0] = &bottomLeftCorner;
  bottomLeftEdge.connectingStructures[1] = &leftCorner;
  bottomLeftEdge.connectingStructures[2] = nullptr;

  bottomEdge.connectingStructures[0] = &bottomRightCorner;
  bottomEdge.connectingStructures[1] = &bottomLeftCorner;
  bottomEdge.connectingStructures[2] = nullptr;

  bottomRightEdge.connectingStructures[0] = &rightCorner;
  bottomRightEdge.connectingStructures[1] = &bottomRightCorner;
  bottomRightEdge.connectingStructures[2] = nullptr;

  topRightEdge.connectingStructures[0] = &topRightCorner;
  topRightEdge.connectingStructures[1] = &rightCorner;
  topRightEdge.connectingStructures[2] = nullptr;
}

void hexTile::correctRoadDirections(){
  structure *cache;

  if(identifier == 12 || identifier == 16){
    cache = topLeftCorner.connectingStructures[0] -> connectingStructures[0];
    topLeftCorner.connectingStructures[0] -> connectingStructures[0] = topLeftCorner.connectingStructures[0] -> connectingStructures[1];
    topLeftCorner.connectingStructures[0] -> connectingStructures[1] = cache;
  }
  if(identifier == 3 || identifier == 7){
    cache = leftCorner.connectingStructures[0] -> connectingStructures[0];
    leftCorner.connectingStructures[0] -> connectingStructures[0] = leftCorner.connectingStructures[0] -> connectingStructures[1];
    leftCorner.connectingStructures[0] -> connectingStructures[1] = cache;
  }
  if(identifier == 15 || identifier == 18){
    cache = bottomLeftCorner.connectingStructures[0] -> connectingStructures[0];
    bottomLeftCorner.connectingStructures[0] -> connectingStructures[0] = bottomLeftCorner.connectingStructures[0] -> connectingStructures[1];
    bottomLeftCorner.connectingStructures[0] -> connectingStructures[1] = cache;
  }
  if(identifier == 2 || identifier == 6){
    cache = bottomRightCorner.connectingStructures[0] -> connectingStructures[0];
    bottomRightCorner.connectingStructures[0] -> connectingStructures[0] = bottomRightCorner.connectingStructures[0] -> connectingStructures[1];
    bottomRightCorner.connectingStructures[0] -> connectingStructures[1] = cache;
  }
  if(identifier == 11 || identifier == 15){
    cache = rightCorner.connectingStructures[0] -> connectingStructures[0];
    rightCorner.connectingStructures[0] -> connectingStructures[0] = rightCorner.connectingStructures[0] -> connectingStructures[1];
    rightCorner.connectingStructures[0] -> connectingStructures[1] = cache;
  }
  if(identifier == 17 || identifier == 18){
    cache = topRightCorner.connectingStructures[0] -> connectingStructures[0];
    topRightCorner.connectingStructures[0] -> connectingStructures[0] = topRightCorner.connectingStructures[0] -> connectingStructures[1];
    topRightCorner.connectingStructures[0] -> connectingStructures[1] = cache;
  }
}

void hexTile::fillSettlements(char inputChar){
  topLeftCorner.fillChar = inputChar;
  topRightCorner.fillChar = inputChar;
  bottomLeftCorner.fillChar = inputChar;
  bottomRightCorner.fillChar = inputChar;
  leftCorner.fillChar = inputChar;
  rightCorner.fillChar = inputChar;
}

void hexTile::addStructure(structure &inputStructure, char vertical, char horisontal){
  switch(vertical){
    case NULL:
      switch(horisontal){
        case 'l':
          leftCorner.fillChar = inputStructure.fillChar;
          leftCorner.color    = inputStructure.color;
          leftCorner.weight   = inputStructure.weight;
          inputStructure = leftCorner;
        break;
        case 'r':
          rightCorner.fillChar = inputStructure.fillChar;
          rightCorner.color    = inputStructure.color;
          rightCorner.weight   = inputStructure.weight;
          inputStructure = rightCorner;
        break;
      }
    break;
    case 't':
      switch(horisontal){
        case 'l':
          topLeftCorner.fillChar = inputStructure.fillChar;
          topLeftCorner.color    = inputStructure.color;
          topLeftCorner.weight   = inputStructure.weight;
          inputStructure = topLeftCorner;
        break;
        case 'r':
          topRightCorner.fillChar = inputStructure.fillChar;
          topRightCorner.color    = inputStructure.color;
          topRightCorner.weight   = inputStructure.weight;
          inputStructure = topRightCorner;
        break;
      }
    break;
    case 'b':
    switch(horisontal){
      case 'l':
        bottomLeftCorner.fillChar = inputStructure.fillChar;
        bottomLeftCorner.color    = inputStructure.color;
        bottomLeftCorner.weight   = inputStructure.weight;
        inputStructure = bottomLeftCorner;
      break;
      case 'r':
        bottomRightCorner.fillChar = inputStructure.fillChar;
        bottomRightCorner.color    = inputStructure.color;
        bottomRightCorner.weight   = inputStructure.weight;
        inputStructure = bottomRightCorner;
      break;
    }
    break;
  }
}

void hexTile::addIdenticleCorners(structure comparatorStructure){
  if(comparatorStructure.x == topLeftCorner.x && comparatorStructure.y == topLeftCorner.y){
    topLeftCorner.color = comparatorStructure.color;
    topLeftCorner.fillChar = comparatorStructure.fillChar;
    topLeftCorner.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == leftCorner.x && comparatorStructure.y == leftCorner.y){
    leftCorner.color = comparatorStructure.color;
    leftCorner.fillChar = comparatorStructure.fillChar;
    leftCorner.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == bottomLeftCorner.x && comparatorStructure.y == bottomLeftCorner.y){
    bottomLeftCorner.color = comparatorStructure.color;
    bottomLeftCorner.fillChar = comparatorStructure.fillChar;
    bottomLeftCorner.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == bottomRightCorner.x && comparatorStructure.y == bottomRightCorner.y){
    bottomRightCorner.color = comparatorStructure.color;
    bottomRightCorner.fillChar = comparatorStructure.fillChar;
    bottomRightCorner.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == rightCorner.x && comparatorStructure.y == rightCorner.y){
    rightCorner.color = comparatorStructure.color;
    rightCorner.fillChar = comparatorStructure.fillChar;
    rightCorner.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == topRightCorner.x && comparatorStructure.y == topRightCorner.y){
    topRightCorner.color = comparatorStructure.color;
    topRightCorner.fillChar = comparatorStructure.fillChar;
    topRightCorner.weight = comparatorStructure.weight;
  }
}

void hexTile::addIdenticlEdges(structure comparatorStructure){
  if(comparatorStructure.x == topEdge.x && comparatorStructure.y == topEdge.y){
    topEdge.color = comparatorStructure.color;
    topEdge.fillChar = comparatorStructure.fillChar;
    topEdge.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == topRightEdge.x && comparatorStructure.y == topRightEdge.y){
    topRightEdge.color = comparatorStructure.color;
    topRightEdge.fillChar = comparatorStructure.fillChar;
    topRightEdge.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == bottomRightEdge.x && comparatorStructure.y == bottomRightEdge.y){
    bottomRightEdge.color = comparatorStructure.color;
    bottomRightEdge.fillChar = comparatorStructure.fillChar;
    bottomRightEdge.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == bottomEdge.x && comparatorStructure.y == bottomEdge.y){
    bottomEdge.color = comparatorStructure.color;
    bottomEdge.fillChar = comparatorStructure.fillChar;
    bottomEdge.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == bottomLeftEdge.x && comparatorStructure.y == bottomLeftEdge.y){
    bottomLeftEdge.color = comparatorStructure.color;
    bottomLeftEdge.fillChar = comparatorStructure.fillChar;
    bottomLeftEdge.weight = comparatorStructure.weight;
  }
  else if(comparatorStructure.x == topLeftEdge.x && comparatorStructure.y == topLeftEdge.y){
    topLeftEdge.color = comparatorStructure.color;
    topLeftEdge.fillChar = comparatorStructure.fillChar;
    topLeftEdge.weight = comparatorStructure.weight;
  }
}

void hexTile::assignMaterial(string name, string color){
  material.name  = name;
  material.color = color;
}

void hexTile::replenish(){
  landscapeColor = landscapeColorCache;
  landscapeHighlightColor = landscapeHighlightColorCache;
  robbed = false;
}

void hexTile::rob(){
  landscapeColorCache = landscapeColor;
  landscapeHighlightColorCache = landscapeHighlightColor;
  landscapeColor = "true_black";
  landscapeHighlightColor = "true_black";
  robbed = true;
}

void hexTile::showNearbySettlementLocations(hexTile board[], const int AMOUNT_OF_TILES, player currentPlayer, int &AmountOfCharactersUsed, char assigningCharacter[]){

  structure cacheStructure;

  if(currentPlayer.getColor() == topLeftCorner.color && topLeftCorner.fillChar == '*'){
    topLeftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticleCorners(topLeftCorner);
    }
    AmountOfCharactersUsed++;
  }
  if(currentPlayer.getColor() == leftCorner.color && leftCorner.fillChar == '*'){
    leftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticleCorners(leftCorner);
    }
    AmountOfCharactersUsed++;
  }
  if(currentPlayer.getColor() == bottomLeftCorner.color && bottomLeftCorner.fillChar == '*'){
    bottomLeftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticleCorners(bottomLeftCorner);
    }
    AmountOfCharactersUsed++;
  }
  if(currentPlayer.getColor() == bottomRightCorner.color && bottomRightCorner.fillChar == '*'){
    bottomRightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticleCorners(bottomRightCorner);
    }
    AmountOfCharactersUsed++;
  }
  if(currentPlayer.getColor() == rightCorner.color && rightCorner.fillChar == '*'){
    rightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticleCorners(rightCorner);
    }
    AmountOfCharactersUsed++;
  }
  if(currentPlayer.getColor() == topRightCorner.color && topRightCorner.fillChar == '*'){
    topRightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    for(int i = 0; i < AMOUNT_OF_TILES; i++){
      board[i].addIdenticleCorners(topRightCorner);
    }
    AmountOfCharactersUsed++;
  }
  if(currentPlayer.getColor() == topEdge.color){
    if(topEdge.connectingStructures[0] -> fillChar == 'o' && validRoadSourceLocation(topEdge) && topEdge.connectingStructures[0] -> color == "grey"){

      cacheStructure = *topEdge.connectingStructures[0];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
    else if(topEdge.connectingStructures[1] -> fillChar == 'o' && validRoadSourceLocation(topEdge) && topEdge.connectingStructures[1] -> color == "grey"){

      cacheStructure = *topEdge.connectingStructures[1];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
  }
  if(currentPlayer.getColor() == topRightEdge.color){
    if(topRightEdge.connectingStructures[0] -> fillChar == 'o' && validRoadSourceLocation(topRightEdge) && topRightEdge.connectingStructures[0] -> color == "grey"){

      cacheStructure = *topRightEdge.connectingStructures[0];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
    else if(topRightEdge.connectingStructures[1] -> fillChar == 'o' && validRoadSourceLocation(topRightEdge) && topRightEdge.connectingStructures[1] -> color == "grey"){

      cacheStructure = *topRightEdge.connectingStructures[1];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
  }
  if(currentPlayer.getColor() == bottomRightEdge.color){
    if(bottomRightEdge.connectingStructures[0] -> fillChar == 'o' && validRoadSourceLocation(bottomRightEdge) && bottomRightEdge.connectingStructures[0] -> color == "grey"){

      cacheStructure = *bottomRightEdge.connectingStructures[0];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
    else if(bottomRightEdge.connectingStructures[1] -> fillChar == 'o' && validRoadSourceLocation(bottomRightEdge) && bottomRightEdge.connectingStructures[1] -> color == "grey"){

      cacheStructure = *bottomRightEdge.connectingStructures[1];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
  }
  if(currentPlayer.getColor() == bottomEdge.color){
    if(bottomEdge.connectingStructures[0] -> fillChar == 'o' && validRoadSourceLocation(bottomEdge) && bottomEdge.connectingStructures[0] -> color == "grey"){

      cacheStructure = *bottomEdge.connectingStructures[0];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
    else if(bottomEdge.connectingStructures[1] -> fillChar == 'o' && validRoadSourceLocation(bottomEdge) && bottomEdge.connectingStructures[1] -> color == "grey"){

      cacheStructure = *bottomEdge.connectingStructures[1];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
  }
  if(currentPlayer.getColor() == bottomLeftEdge.color){
    if(bottomLeftEdge.connectingStructures[0] -> fillChar == 'o' && validRoadSourceLocation(bottomLeftEdge) && bottomLeftEdge.connectingStructures[0] -> color == "grey"){

      cacheStructure = *bottomLeftEdge.connectingStructures[0];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
    else if(bottomLeftEdge.connectingStructures[1] -> fillChar == 'o' && validRoadSourceLocation(bottomLeftEdge) && bottomLeftEdge.connectingStructures[1] -> color == "grey"){

      cacheStructure = *bottomLeftEdge.connectingStructures[1];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
  }
  if(currentPlayer.getColor() == topLeftEdge.color){
    if(topLeftEdge.connectingStructures[0] -> fillChar == 'o' && validRoadSourceLocation(topLeftEdge) && topLeftEdge.connectingStructures[0] -> color == "grey"){

      cacheStructure = *topLeftEdge.connectingStructures[0];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
    else if(topLeftEdge.connectingStructures[1] -> fillChar == 'o' && validRoadSourceLocation(topLeftEdge) && topLeftEdge.connectingStructures[1] -> color == "grey"){

      cacheStructure = *topLeftEdge.connectingStructures[1];

      cacheStructure.fillChar = assigningCharacter[AmountOfCharactersUsed];

      for(int i = 0; i < AMOUNT_OF_TILES; i++){
        board[i].addIdenticleCorners(cacheStructure);
      }
      AmountOfCharactersUsed++;
    }
  }
}

void hexTile::showPossibleSettlmentAreas(player currentPlayer, int &AmountOfCharactersUsed, char assigningCharacter[]){
  if(rightCorner.color == "grey" && validStructureLocation(rightCorner, '\0', 'r')){
    for(int i = 0; i < 3; i++){
      if(rightCorner.connectingStructures[i] -> color == currentPlayer.getColor() && rightCorner.fillChar == '*'){
        rightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
        addIdenticleCorners(rightCorner);
        AmountOfCharactersUsed++;
      }
    }
  }
  else if(leftCorner.color == "grey" && validStructureLocation(rightCorner, '\0', 'l') && leftCorner.fillChar == '*'){
    for(int i = 0; i < 3; i++){
      if(leftCorner.connectingStructures[i] -> color == currentPlayer.getColor()){
        leftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
        addIdenticleCorners(leftCorner);
        AmountOfCharactersUsed++;
      }
    }
  }
  else if(topRightCorner.color == "grey" && validStructureLocation(topRightCorner, 't', 'r') && topRightCorner.fillChar == '*'){
    for(int i = 0; i < 3; i++){
      if(topRightCorner.connectingStructures[i] -> color == currentPlayer.getColor()){
        topRightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
        addIdenticleCorners(topRightCorner);
        AmountOfCharactersUsed++;
      }
    }
  }
  else if(topLeftCorner.color == "grey" && validStructureLocation(topLeftCorner, 't', 'l') && topLeftCorner.fillChar == '*'){
    for(int i = 0; i < 3; i++){
      if(topLeftCorner.connectingStructures[i] -> color == currentPlayer.getColor()){
        topLeftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
        addIdenticleCorners(topLeftCorner);
        AmountOfCharactersUsed++;
      }
    }
  }
  else if(bottomRightCorner.color == "grey" && validStructureLocation(bottomRightCorner, 'b', 'r') && bottomRightCorner.fillChar == '*'){
    for(int i = 0; i < 3; i++){
      if(bottomRightCorner.connectingStructures[i] -> color == currentPlayer.getColor()){
        bottomRightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
        addIdenticleCorners(bottomRightCorner);
        AmountOfCharactersUsed++;
      }
    }
  }
  else if(bottomLeftCorner.color == "grey" && validStructureLocation(bottomLeftCorner, 'b', 'l') && bottomLeftCorner.fillChar == '*'){
    for(int i = 0; i < 3; i++){
      if(bottomLeftCorner.connectingStructures[i] -> color == currentPlayer.getColor()){
        bottomLeftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
        addIdenticleCorners(bottomLeftCorner);
        AmountOfCharactersUsed++;
      }
    }
  }
}

void hexTile::selectSetttlments(player currentPlayer, int &AmountOfCharactersUsed, char assigningCharacter[]){
  if(rightCorner.color == currentPlayer.getColor() && rightCorner.fillChar == 'S'){
    rightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    addIdenticleCorners(rightCorner);
    AmountOfCharactersUsed++;
  }
  if(leftCorner.color == currentPlayer.getColor() && leftCorner.fillChar == 'S'){
    leftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    addIdenticleCorners(leftCorner);
    AmountOfCharactersUsed++;
  }
  if(topRightCorner.color == currentPlayer.getColor() && topRightCorner.fillChar == 'S'){
    topRightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    addIdenticleCorners(topRightCorner);
    AmountOfCharactersUsed++;
  }
  if(topLeftCorner.color == currentPlayer.getColor() && topLeftCorner.fillChar == 'S'){
    topLeftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    addIdenticleCorners(topLeftCorner);
    AmountOfCharactersUsed++;
  }
  if(bottomRightCorner.color == currentPlayer.getColor() && bottomRightCorner.fillChar == 'S'){
    bottomRightCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    addIdenticleCorners(bottomRightCorner);
    AmountOfCharactersUsed++;
  }
  if(bottomLeftCorner.color == currentPlayer.getColor() && bottomLeftCorner.fillChar == 'S'){
    bottomLeftCorner.fillChar = assigningCharacter[AmountOfCharactersUsed];
    addIdenticleCorners(bottomLeftCorner);
    AmountOfCharactersUsed++;
  }
}

structure hexTile::findSettlementLocation(char searchChar){
  structure returnValue;

  if(topLeftCorner.fillChar == searchChar){
    returnValue = topLeftCorner;
  }
  else if(topRightCorner.fillChar == searchChar){
    returnValue = topRightCorner;
  }
  else if(leftCorner.fillChar == searchChar){
    returnValue = leftCorner;
  }
  else if(rightCorner.fillChar == searchChar){
    returnValue = rightCorner;
  }
  else if(bottomLeftCorner.fillChar == searchChar){
    returnValue = bottomLeftCorner;
  }
  else if(bottomRightCorner.fillChar == searchChar){
    returnValue = bottomRightCorner;
  }

  return returnValue;
}

structure hexTile::findRoadLocation(char searchChar){
  structure returnValue;

  if(topEdge.fillChar == searchChar){
    returnValue = topEdge;
  }
  else if(topRightEdge.fillChar == searchChar){
    returnValue = topRightEdge;
  }
  else if(bottomRightEdge.fillChar == searchChar){
    returnValue = bottomRightEdge;
  }
  else if(bottomEdge.fillChar == searchChar){
    returnValue = bottomEdge;
  }
  else if(bottomLeftEdge.fillChar == searchChar){
    returnValue = bottomLeftEdge;
  }
  else if(topLeftEdge.fillChar == searchChar){
    returnValue = topLeftEdge;
  }

  return returnValue;
}

card hexTile::getMaterial(){
  return material;
}

bool hexTile::isDesert(){
  return tileDigit == 7;
}

bool hexTile::hasStructure(structure inputStructure){
  bool returnValue = false;

  if(inputStructure.x == topLeftCorner.x && inputStructure.y == topLeftCorner.y){
    returnValue = true;
  }
  else if(inputStructure.x == topRightCorner.x && inputStructure.y == topRightCorner.y){
    returnValue = true;
  }
  else if(inputStructure.x == leftCorner.x && inputStructure.y == leftCorner.y){
    returnValue = true;
  }
  else if(inputStructure.x == rightCorner.x && inputStructure.y == rightCorner.y){
    returnValue = true;
  }
  else if(inputStructure.x == bottomLeftCorner.x && inputStructure.y == bottomLeftCorner.y){
    returnValue = true;
  }
  else if(inputStructure.x == bottomRightCorner.x && inputStructure.y == bottomRightCorner.y){
    returnValue = true;
  }

  return returnValue;
}

bool hexTile::hasPlayerStructure(player inputPlayer){
  bool returnValue = false;

  if(inputPlayer.getColor() == topLeftCorner.color){
    returnValue = true;
  }
  else if(inputPlayer.getColor() == topRightCorner.color){
    returnValue = true;
  }
  else if(inputPlayer.getColor() == leftCorner.color){
    returnValue = true;
  }
  else if(inputPlayer.getColor() == rightCorner.color){
    returnValue = true;
  }
  else if(inputPlayer.getColor() == bottomLeftCorner.color){
    returnValue = true;
  }
  else if(inputPlayer.getColor() == bottomRightCorner.color){
    returnValue = true;
  }

  return returnValue;
}

bool hexTile::validRoadSourceLocation(structure inputStructure){
  bool returnValue = false;

  for(int i = 0; i < 2; i++){
    if(inputStructure.connectingStructures[i] -> color == "grey"){
      returnValue = true;
      break;
    }
  }

  return returnValue;
}

bool hexTile::valid(){

  bool returnValue = true;

  if((topRightCorner.fillChar == 'S' || topRightCorner.fillChar == 'C') && (bottomRightCorner.fillChar == 'S' || bottomRightCorner.fillChar == 'C') && (leftCorner.fillChar == 'S' || leftCorner.fillChar == 'C')){
    returnValue = false;
  }
  else if((topLeftCorner.fillChar == 'S' || topLeftCorner.fillChar == 'C') && (bottomLeftCorner.fillChar == 'S' || bottomLeftCorner.fillChar == 'C') && (rightCorner.fillChar == 'S' || rightCorner.fillChar == 'C')){
    returnValue = false;
  }
  else if((rightCorner.fillChar == 'S' || rightCorner.fillChar == 'C') && (leftCorner.fillChar == 'S' || leftCorner.fillChar == 'C')){
    returnValue = false;
  }
  else if((topRightCorner.fillChar == 'S' || topRightCorner.fillChar == 'C') && (bottomLeftCorner.fillChar == 'S' || bottomLeftCorner.fillChar == 'C')){
    returnValue = false;
  }
  else if((topLeftCorner.fillChar == 'S' || topLeftCorner.fillChar == 'C') && (bottomRightCorner.fillChar == 'S' || bottomRightCorner.fillChar == 'C')){
    returnValue = false;
  }

  return returnValue;
}

bool hexTile::validStructureLocation(structure inputStructure, char vertical, char horisontal){
  bool returnValue = true;

  switch(vertical){
    case NULL:
      switch(horisontal){
        case 'l':
          if(leftCorner.fillChar == 'S' || leftCorner.fillChar == 'C'){
            returnValue = false;
          }
          if(leftCorner.connectingStructures[0] != nullptr){
            if(leftCorner.connectingStructures[0] -> connectingStructures[1] -> fillChar == 'S' || leftCorner.connectingStructures[0] -> connectingStructures[1] -> fillChar == 'C'){
              returnValue = false;
            }
          }
          if(leftCorner.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'S' || leftCorner.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
          if(leftCorner.connectingStructures[2] -> connectingStructures[1] -> fillChar == 'S' || leftCorner.connectingStructures[2] -> connectingStructures[1] -> fillChar == 'C'){
            returnValue = false;
          }
        break;
        case 'r':
          if(rightCorner.fillChar == 'S' || rightCorner.fillChar == 'C'){
            returnValue = false;
          }
          if(rightCorner.connectingStructures[2] != nullptr){
            if(rightCorner.connectingStructures[2] -> connectingStructures[1] -> fillChar == 'S' || rightCorner.connectingStructures[2] -> connectingStructures[0] -> fillChar == 'C'){
              returnValue = false;
            }
          }
          if(rightCorner.connectingStructures[0] -> connectingStructures[0] -> fillChar == 'S' || rightCorner.connectingStructures[0] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
          if(rightCorner.connectingStructures[1] -> connectingStructures[1] -> fillChar == 'S' || rightCorner.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
        break;
      }
    break;
    case 't':
      switch(horisontal){
        case 'l':
          if(topLeftCorner.fillChar == 'S' || topLeftCorner.fillChar == 'C'){
            returnValue = false;
          }
          if(topLeftCorner.connectingStructures[0] != nullptr){
            if(topLeftCorner.connectingStructures[0] -> connectingStructures[1] -> fillChar == 'S' || topLeftCorner.connectingStructures[0] -> connectingStructures[1] -> fillChar == 'C'){
              returnValue = false;
            }
          }
          if(topLeftCorner.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'S' || topLeftCorner.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
          if(topLeftCorner.connectingStructures[2] -> connectingStructures[1] -> fillChar == 'S' || topLeftCorner.connectingStructures[2] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
        break;
        case 'r':
          if(topRightCorner.fillChar == 'S' || topRightCorner.fillChar == 'C'){
            returnValue = false;
          }
          if(topRightCorner.connectingStructures[2] != nullptr){
            if(topRightCorner.connectingStructures[2] -> connectingStructures[1] -> fillChar == 'S' || topRightCorner.connectingStructures[2] -> connectingStructures[1] -> fillChar == 'C'){
              returnValue = false;
            }
          }
          if(topRightCorner.connectingStructures[0] -> connectingStructures[0] -> fillChar == 'S' || topRightEdge.connectingStructures[0] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
          if(topRightCorner.connectingStructures[1] -> connectingStructures[1] -> fillChar == 'S' || topRightEdge.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
        break;
      }
    break;
    case 'b':
    switch(horisontal){
      case 'l':
        if(bottomLeftCorner.fillChar == 'S' || bottomLeftCorner.fillChar == 'C'){
          returnValue = false;
        }
        if(bottomLeftCorner.connectingStructures[1] != nullptr){
          if(bottomLeftCorner.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'S' || bottomLeftCorner.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
        }
        if(bottomLeftCorner.connectingStructures[0] -> connectingStructures[1] -> fillChar == 'S' || bottomLeftCorner.connectingStructures[0] -> connectingStructures[1] -> fillChar == 'C'){
          returnValue = false;
        }
        if(bottomLeftCorner.connectingStructures[2] -> connectingStructures[0] -> fillChar == 'S' || bottomLeftCorner.connectingStructures[2] -> connectingStructures[0] -> fillChar == 'C'){
          returnValue = false;
        }
      break;
      case 'r':
        if(bottomRightCorner.fillChar == 'S' || bottomRightCorner.fillChar == 'C'){
          returnValue = false;
        }
        if(bottomRightCorner.connectingStructures[1] != nullptr){
          if(bottomRightCorner.connectingStructures[1] -> connectingStructures[1] -> fillChar == 'S' || bottomRightCorner.connectingStructures[1] -> connectingStructures[0] -> fillChar == 'C'){
            returnValue = false;
          }
        }
        if(bottomRightCorner.connectingStructures[0] -> connectingStructures[1] -> fillChar == 'S' || bottomRightCorner.connectingStructures[0] -> connectingStructures[0] -> fillChar == 'C'){
          returnValue = false;
        }
        if(bottomRightCorner.connectingStructures[2] -> connectingStructures[0] -> fillChar == 'S' || bottomRightCorner.connectingStructures[2] -> connectingStructures[1] -> fillChar == 'C'){
          returnValue = false;
        }
      break;
    }
    break;
  }
  return returnValue;
}

char hexTile::getLeftCornerChar(){
  return topLeftCorner.fillChar;
}

string hexTile::getColor(){
  return landscapeColor;
}

int hexTile::doesGetMaterial(player inputPlayer, int roll){
  int returnValue = 0;
  int trueDigit = 0;

  if(secondaryTileDigit == 1){
    trueDigit  = 11;
  }
  else if(tileDigit == secondaryTileDigit){
    trueDigit = tileDigit;
  }
  else{
      trueDigit = tileDigit * 10 + secondaryTileDigit;
  }

  if(!robbed && roll == trueDigit){
    if(inputPlayer.getColor() == topLeftCorner.color){
      if(topLeftCorner.fillChar == 'C'){
        returnValue++;
      }
      returnValue++;
    }
    else if(inputPlayer.getColor() == topRightCorner.color){
      if(topRightCorner.fillChar == 'C'){
        returnValue++;
      }
      returnValue++;
    }
    else if(inputPlayer.getColor() == leftCorner.color){
      if(leftCorner.fillChar == 'C'){
        returnValue++;
      }
      returnValue++;
    }
    else if(inputPlayer.getColor() == rightCorner.color){
      if(rightCorner.fillChar == 'C'){
        returnValue++;
      }
      returnValue++;
    }
    else if(inputPlayer.getColor() == bottomLeftCorner.color){
      if(bottomLeftCorner.fillChar == 'C'){
        returnValue++;
      }
      returnValue++;
    }
    else if(inputPlayer.getColor() == bottomRightCorner.color){
      if(bottomRightCorner.fillChar == 'C'){
        returnValue++;
      }
      returnValue++;
    }
  }

  return returnValue;
}
