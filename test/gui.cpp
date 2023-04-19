#include <ncurses.h>
#include <string>
#include "gui.hpp"

std::ostream& operator<<(std::ostream& os, const Pages& page) {
    static const char* const pages_strings[] = { "Supplier", "Retailer", "Courier", "Landing", "EXIT" };
    return os << pages_strings[static_cast<int>(page)];
}

void GUI::start(){
    //Ncurses Initailization and Settings
    initscr(); // initialize ncurses
    cbreak(); // turn off line buffering
    noecho(); // don't echo input to the screen
    curs_set(0); // hide the curso
    keypad(stdscr, true); // enable function keys, arrow keys, etc.

    //Create Design
    box(stdscr,0,0);
    printWord(0, (COLS - strlen("XSCM"))/2, "XSCM");

    // clear();

    //Start 
    getch(); // wait for user input

    endwin(); //TODO when exit restore terminal settings
}

void printWord(int x, int y, std::string word){
    mvprintw(x, y, "%s", word);
}

void GUI::screenMain(int cursorIndex){
//     // clear(); // clear the screen
//     // printMainHeader();
//     // cursorIndex = printOptions(cursorIndex); //TODO pass by reference
//     // screenMain(cursorIndex);
}

int GUI::printOptions(int cursorIndex) {
//     for (int i = 0; i <= static_cast<int>(Pages::LANDING); i++) {
//         if (i == cursorIndex){
//             attron(A_REVERSE); // highlight the selected option
//         }
//         printw("%s\n", static_cast<Pages>(i)); // print the option
//         attroff(A_REVERSE); // turn off highlighting
//     }

//     int input = getch();
//     if (input == KEY_UP) { // Up arrow
//         cursorIndex--;
//         if (cursorIndex < 0) {
//             cursorIndex = static_cast<int>(Pages::LANDING);
//         }
//     } else if (input == KEY_DOWN) { // Down arrow
//         cursorIndex++;
//         if (cursorIndex > static_cast<int>(Pages::LANDING)) {
//             cursorIndex = 0;
//         }
//     }
//     return cursorIndex;
}