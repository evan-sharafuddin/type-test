// Implementation of typing test menu

#include "terminal.hpp"
#include "rawterm.h"
#include "rawterm_utils.h"
#include "rawterm_widgets.h"

#include <fstream>
#include <sstream>

Terminal::Terminal() 
    : type_test(NULL)
{

    // terminal view boilerplate
    enable_raw_mode();
    clear_terminal();
    move_cursor_home();

    // load title text as a c string
    std::ifstream ifs( "../../data/type_test_ascii.txt");
    std::ostringstream iss;
    iss << ifs.rdbuf();
    std::string tmp = iss.str();
    const char* ascii_art = tmp.c_str();

    // display title text
    out(ascii_art);



    

    

}