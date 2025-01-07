// Implementation of typing test menu

#include "menu.hpp"
#include "rawterm.h"

Menu::Menu()
    : welcome_message("Welcome to Typing Test!")
{

    // set terminal to raw
    enable_raw_mode();

    

}