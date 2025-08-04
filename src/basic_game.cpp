

#include <iostream>
#include <string>
#include "rawterm.h"
#include "rawterm_utils.h"


int main() {

    enable_raw_mode();

    std::string model = "User should type this out!";
    
    char input;

    std::string ENDL = "\r\n";
    std::cout << "Welcome to type test!" << ENDL << std::flush;
    std::cout << model << ENDL << ENDL << std::flush;

    int mistake_cnt = 0;
    // int test_cnt = 0;

    auto it = model.begin();

    while ( true ) {

        if ( read( STDIN_FILENO, &input, 1 ) == -1 && errno != EAGAIN )
            die("read");

        if ( input == 127 ) {
            write(STDOUT_FILENO, "\b\x1b[1P", 5);
            
            if ( it == model.begin() ) {
                --it;
            }
            else {
                it -= 2;
            }

            if (mistake_cnt > 0) {
                mistake_cnt--;
            }
            
            continue;
        }

        if ( input != *it || mistake_cnt > 0 ) { // set text to red
            write(STDOUT_FILENO, "\x1b[1;31m", 7);
            mistake_cnt++;
        }
        else {
            write(STDOUT_FILENO, "\x1b[0m", 4);
        }

        write(STDOUT_FILENO, &input, 1);

        if ( input == 'q' ) {
            break;
        }

        // print out some debug stuff

        char c = *it;
        std::string one_char_str(1, c);       // C++ string with one character
        const char* cstr = one_char_str.c_str(); // const char* of that string
        move_cursor_down(1);
        // std::string strr = std::to_string(mistake_cnt);
        // const char* strr2 = strr.c_str();
        clear_char();
        // out(strr2);
        
        out(cstr);
        // move_cursor_left(1);
        move_cursor_up(1);

        // test_cnt++;
        // if ( test_cnt > 4 ) {
        //     // clear_terminal();
        //     clear_terminal();
        //     move_cursor_home();
        //     test_cnt = 0;
        // }
        
        if ( it == model.end() && mistake_cnt > 0 ) {

            it--;
            // move_cursor_down(2);
            // std::string strr = std::to_string(mistake_cnt);
            // const char* strr2 = strr.c_str();
            // clear_char();
            // // const char* 
            // out(&(*it));
            // // move_cursor_left(1);
            // move_cursor_up(2);
            // // mistake_cnt--;

        }
        else if ( it == model.end() ) {
            break;
        }
        else {
            it++;
        }
    }

    printf("\r\n");
    

    return mistake_cnt;
}