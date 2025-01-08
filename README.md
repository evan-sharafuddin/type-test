

# Helpful notes and links

## code structure
* currently under construction... only used files are `rawterm.h`, `rawterm.c`, and `main.cpp`
* hoping to develop the `RawTerm` library enough so that it can be used for general terminal apps

### brainstorming
* will need two terminal "views"
    * main menu
    * game/test interface
* should have one "terminal" class that has both of these views (also implemented as classes)


## Compilation
* cmake now created for compilation
## Terminal control

### Raw mode
https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html

## Termios
https://pubs.opengroup.org/onlinepubs/7908799/xbd/termios.html
https://www.man7.org/linux/man-pages/man3/termios.3.html

# Code Structure
## Brainstorming
* Typing game should be its own class
* Might want to make C header for terminal raw mode and ANSI escape sequences
