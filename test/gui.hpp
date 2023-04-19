#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <ncurses.h>
#include <string>

enum class Pages {
    SUPPLIER,
    RETAILER,
    COURIER,
    LANDING,
    EXIT
};

class GUI {
public:
    void start();
    void screenMain(int cursorIndex);
    int printOptions(int cursorIndex);
    void printMainHeader();
    void printSmallHeader(std::string page_title);
    void clearScreen();
    void printWord(int x, int y, string word);
};

#endif // GUI_HPP