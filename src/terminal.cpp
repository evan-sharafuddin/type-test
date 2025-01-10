// Implementation of typing test menu

#include "terminal.hpp"
#include "rawterm.h"
#include "rawterm_utils.h"

Terminal::Terminal() 
    : type_test(NULL)
{

    // terminal view boilerplate
    enable_raw_mode();
    clear_terminal();
    move_cursor_home();

    
}