/*
Name: typesafe

Version: 1.3

Improovements: added in 1.3 from 1.2.2 a new version of the check char function is now availble with the added functionality of being able to
compare multiple characters in the same call. Also new in 1.3 is a patch for a bug in the get char function which could cause the program to
crash if nothing is entered

Discription: This header file is desined to run error checks and prevent errors for a variety of different sinarios that arise in my programs
*/
bool isNum(string input){
  const int NUM_OF_DIGITS = 12;
  const char SINGLE_DIG_NUMS[NUM_OF_DIGITS] = {'0','1','2','3','4','5','6','7','8','9','.','-'};
  bool returnValue = false;
  bool isNegative = false;
  bool isNum = false;

  int decimalCount = 0;

  isNum = true;

  for(int i = 0; i < input.length(); i++){
    if(input.at(i) == '.'){
      decimalCount ++;
      if(decimalCount > 1){
        isNum = false;
      }
    }
    if(input.at(i) == '-' && i != 0){
       isNum = false;
    }
    if(isNum){
      isNum = false;
      for(int j = 0; j < NUM_OF_DIGITS; j++){
        if(input.at(i) == SINGLE_DIG_NUMS[j]){
          isNum = true;
          returnValue = true;
        }
      }
    }
  }
  if(!isNum){
    returnValue = false;
  }
  return returnValue;
}

bool isNum(char input){
  const int NUM_OF_DIGITS = 12;
  const char SINGLE_DIG_NUMS[NUM_OF_DIGITS] = {'0','1','2','3','4','5','6','7','8','9','.','-'};
  bool returnValue = false;

  for(int i = 0; i < NUM_OF_DIGITS; i++){
    if(input == SINGLE_DIG_NUMS[i]){
      returnValue = true;
      break;
    }
  }
  return returnValue;
}

bool checkChar(char input, char compare){

  input = tolower(input);
  compare = tolower(compare);

  bool returnValue = false;

  if(input == compare){
    returnValue = true;
  }
  else{
    returnValue = false;
  }
  return returnValue;
}

bool checkChar(char input, string compare){
  bool returnValue = false;
  for(int i = 0; i < compare.length(); i++){
    if(input == compare.at(i)){
      returnValue = true;
      break;
    }
  }
  return returnValue;
}

bool inIntRange(string input){
  const int MAX_INT[10] = {4, 2, 9, 4, 9, 6, 7, 2, 9, 6};

  bool returnValue = false;

  if(input.length() > 9){
    if(input.length() == 10){
      for(int i = 0; i < 10; i++){
        int numCache = input.at(i) - '0';
        cout << numCache;
        if(numCache > MAX_INT[i]){
          returnValue = false;
          break;
        }
      }
    }
    else{
      returnValue = false;
    }
  }
  else{
    returnValue = true;
  }
  return returnValue;
}

int getInt(istream &input, string err){
  string num   = " ";
  bool inRange = false;
  bool isInt   = false;

  input >> num;

  isInt = isNum(num);

  if(!isInt){
    changeColor("red");
      cout << "Err importing number:";
    changeColor("white");
  }
  else{
    inRange = inIntRange(num);
    if(!inRange){
      changeColor("red");
        cout << "Err imported number is out of range:";
      changeColor("white");
    }
  }

  inIntRange(num);
  if(!inRange){
  cout << "Err number entered out of Int range";
}

  return stoi(num);
}

int getInt(string err){
  string num   = " ";
  bool inRange = false;
  bool isInt   = false;

  do {
    getline(cin, num);

    isInt = isNum(num);

    if(!isInt){
      changeColor("red");
        cout << "Err number entered incorectly:";
      changeColor("white");
      cout << "\nPlease Re-enter " << err << ": ";
    }
    else{
      inRange = inIntRange(num);
      if(!inRange){
        changeColor("red");
          cout << "Err number entered out of Int range:";
        changeColor("white");
        cout << "\nPlease Re-enter " << err << ": ";
      }
    }
  }while(!isInt || !inRange);

  inIntRange(num);
  if(!inRange){
  cout << "Err number entered out of Int range";
}

  return stoi(num);
}

double getDouble(string err){
  string num = " ";

  getline(cin, num);

  while(!isNum(num)){
    changeColor("red");
    cout << "Err number entered incorectly:";
    changeColor("white");
    cout << "\nRe-enter " << err << ": ";
    getline(cin, num);
  }
  return stod(num);
}

int checkRange(int num, int max, int min, string err){

  bool inRange = false;

  while(!inRange){
    if(num > max){
      changeColor("red");
      cout << "Err out of range: Value was above the maximum amount allowed\n";
      changeColor("white");
      cout << "Please re-enter " << err << ": ";
      num = getInt("the number");
    }
    else if (num < min){


      changeColor("red");
      cout << "Err out of range: Value was below the minimum amount allowed\n";
      changeColor("white");
      cout << "Please re-enter " << err << ": ";
      num = getInt("the number");
    }
    else{
      inRange = true;
    }
  }

  return num;
}

int checkRangeShort(int num, int max, int min, string err){
  bool inRange = false;

  while(!inRange){
    if(num > max){
      changeColor("red");
      cout << "Err out of range\n";
      changeColor("white");
      cout << "Please re-enter " << err << ": ";
      num = getInt("the number");
    }
    else if (num < min){
      changeColor("red");
      cout << "Err out of range";
      changeColor("white");
      cout << "Please re-enter " << err << ": ";
      num = getInt("the number");
    }
    else{
      inRange = true;
    }
  }

  return num;
}

double checkRange(double num, double max, double min, string err){

  bool inRange = false;

  while(!inRange){
    if(num > max){
      changeColor("red");
      cout << "Err out of range: Value was above the maximum amount allowed\n";
      changeColor("white");
      cout << "Please re-enter " << err << ": ";
      getDouble("the number");
    }
    else if (num < min){
      changeColor("red");
      cout << "Err out of range: Value was below the minimum amount allowed\n";
      changeColor("white");
      cout << "Please re-enter " << err << ": ";
      getDouble("the number");
    }
    else{
      inRange = true;
    }
  }

  return num;
}

bool inRange(double num, double max, double min){
  bool returnValue;

  if(num > max || num < min){
    returnValue = false;
  }
  else{
    returnValue = true;
  }

  return returnValue;
}

bool inRange(int num, int max, int min){
  bool returnValue;

  if(num > max || num < min){
    returnValue = false;
  }
  else{
    returnValue = true;
  }

  return returnValue;
}

bool contains(int num, int arr[], const int arrSize){
  bool returnValue = false;

  for(int i = 0; i < arrSize; i++){
    if(num == arr[i]){
      returnValue = true;
      break;
    }
  }
  return returnValue;
}

char getChar(string err){

  string input = " ";
  char returnValue = ' ';

  getline(cin, input);

  if(input == "\0"){
    changeColor("red");
    cout << "Err: incorrect format\n";
    changeColor("white");
    cout << "Please re-enter " << err << ": ";
    getline(cin, input);
  }

  return input.at(0);
}

/*
name: pick color
inputs: a number
outputs: user prompts, a color
Discription: displays color options to the user. They pick one and a color is returned
*/
string pickColor(){

  const int AMOUNT_OF_COLORS = 8;
  const string COLOR_NAMES[AMOUNT_OF_COLORS] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};

  int selection = 0;

  cout << "Color options:\n\n";

  for(int i = 0; i < AMOUNT_OF_COLORS; i++){
    changeColor(COLOR_NAMES[i]);
    cout << '[' << i + 1 << "]: " << COLOR_NAMES[i] << '\n';
  }

  changeColor("white");

  cout << "\nColor: ";
  selection = getInt("color");
  selection = checkRange(selection, AMOUNT_OF_COLORS, 0, "color");

  return COLOR_NAMES[selection - 1];
}

void enterKey(){
  string junk = " ";

  getline(cin, junk);
}
