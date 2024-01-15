/*
Name: windows and mac formatting

Version: 1.1.2

Improvements: added in 1.1.2 from 1.1.1 is the inclusion of the print menu functuin

Discription: This header file is desined to make my programs run seamlessly on a mac or a PC
*/

// if the computer is a windows system the program will include the library windows.h
#ifdef _WIN64
  #include <windows.h>
#elif  _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

#include <string>
#include <iostream>
#include <ctype.h>
#include <random>

using namespace std;

/*
name: print menu
inputs: an array of menu options, the amount of menu options
outputs: a nicley formatted menu
Discription: Creates a nice menu for a console interface
*/
void printMenu(const string MENU[], const int AMOUNT_OF_MENUS){
  for(int i = 0; i < AMOUNT_OF_MENUS; i++){
    cout << '[' << i + 1 << "]: " << MENU[i] << '\n';
  }

  cout << "\nSelection: ";
}

/*
name: clear
inputs: none
outputs: either system(clear) for windows or an escape sequence for everyother OS
Discription: Determines the OS that the user is using and clears the terminal window with the corisponding cammand for the terminal for that OS
*/
void clear(){

// compiler finds if the program is running on windows
#ifdef _WIN32

// outputs a windows command to clear terminal
system("CLS");
#elif _WIN64

// outputs a windows command to clear terminal
system("CLS");
#else

//outputs a escape sequnce telling the terminal to clear and to move the cursor to home position
std::cout << "\033[2J\033[1;1H";
#endif
}

void changeColor(string color){

  const int AMOUNT_OF_COLORS = 16;
  const int WINDOWS_COLOR_CODES[AMOUNT_OF_COLORS] = {0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 7, 13, 11, 15};
  const int UNIX_COLOR_CODES[AMOUNT_OF_COLORS] = {30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};

  const string COLOR_NAMES[AMOUNT_OF_COLORS] = {"true_black", "dark_red", "dark_green", "dark_yellow", "dark_blue", "dark_magenta", "dark_cyan", "grey", "black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};

  for(int i = 0; i < AMOUNT_OF_COLORS; i++){
    if(COLOR_NAMES[i] == color){

      // compiler finds if the program is running on windows
      #ifdef _WIN32

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, WINDOWS_COLOR_CODES[i]);

      #elif _WIN64

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, WINDOWS_COLOR_CODES[i]);

      // if program is not running on windows it ouputs an escape sequence to change the consoles text color
      #else
          cout << "\e[" << UNIX_COLOR_CODES[i] << 'm';
      #endif

    }
  }
}

void changeColor(string color, string highlight){

  const int AMOUNT_OF_COLORS = 16;
  const int WINDOWS_COLOR_CODES[AMOUNT_OF_COLORS]     = {0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 9, 13, 11, 15};
  const int WINDOWS_HIGHLIGHT_CODES[AMOUNT_OF_COLORS] = {64, 32, 96, 16, 80, 48, 112, 128, 192, 160, 224, 144, 208, 176, 240};
  const int UNIX_COLOR_CODES[AMOUNT_OF_COLORS]        = {30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};
  const int UNIX_HIGHLIGHT_CODES[AMOUNT_OF_COLORS]    = {40, 41, 42, 43, 44, 45, 46, 100, 101, 102, 103, 104, 105, 106, 107};
  const string COLOR_NAMES[AMOUNT_OF_COLORS]          = {"true_black", "dark_red", "dark_green", "dark_yellow", "dark_blue", "dark_magenta", "dark_cyan", "grey", "black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};

  int colorCode = 0;
  int highlightCode = 0;

  for(int i = 0; i < AMOUNT_OF_COLORS; i++){
    if(COLOR_NAMES[i] == color){
      colorCode = i;
    }
    if(COLOR_NAMES[i] == highlight){
      highlightCode = i;
    }
  }
  // compiler finds if the program is running on windows
  #ifdef _WIN32

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, WINDOWS_COLOR_CODES[colorCode] + WINDOWS_COLOR_CODES[highlightCode]);

  #elif _WIN64

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, WINDOWS_COLOR_CODES[colorCode] + WINDOWS_COLOR_CODES[highlightCode]);

  // if program is not running on windows it ouputs an escape sequence to change the consoles text color
  #else
      cout << "\e[" << UNIX_COLOR_CODES[colorCode] << ';' << UNIX_HIGHLIGHT_CODES[highlightCode] << 'm';
  #endif
}

/*
name: wait
inputs: the number of milliseconds that the computer will wait before moving on to the next task
outputs: None
Discription: Determines the OS that the user is using and tells the corisponding OS to wait in its native format
*/
void wait(int time){
  #ifdef _WIN32
  // tells windows to wait
  Sleep(time);

  #elif _WIN64
  // tells windows to wait
  Sleep(time);

  #else
  // converts time to milliseconds and tells Unix type OS's to wait
  time *= 1000;
  usleep(time);

  #endif
}

/*
name: beep
inputs: nothing
outputs: outputs a systemn beep
Discription: Determines the OS that the user is using and tells the corisponding OS to beep in its native format
*/
void beep(){
  #ifdef _WIN32
  // tells windows to beep
  cout << '\a';

  #elif _WIN64
  // tells windows to beep
  cout << '\a';

  #else
  //outputs a escape sequnce telling the OS to make a system beep
  cout << "\007";

  #endif
}

void setCursor(int x, int y){

  // compiler finds if the program is running on windows
  #ifdef _WIN32

  x--;

  // outputs a windows command to move the cursor to inputted position
  COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);

  #elif _WIN64

    x--;

  // outputs a windows command to move the cursor to inputted position
  COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
  #else

  //outputs a escape sequnce telling the terminal to move the cursor to inputted position
  std::cout << "\033[%" << y << ";%" << x << 'H';
  #endif
}

int getRandomNum(int max){
  //--------------NOT-MY-CODE------------------------------ --------------------------
  random_device rd;     // only used once to initialise (seed) engine
  mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
  uniform_int_distribution<int> uni(0,max); // guaranteed unbiased

  int random_integer;

  return random_integer = uni(rng);
  //----------------------------------------------------------------------------------
}
